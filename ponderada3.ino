//classe semaforo
class Semaforo {
private:
  //ponteiros para os pinos
  const int* _pinos[3]; 
  
  //ponteiros para variáveis de tempo
  const long* _tempoVermelho;
  const long* _tempoAmarelo;
  const long* _tempoVerde;

  // ponteiros para a lógica do botão
  const int* _pinoBotao;
  const long* _tempoAmareloRapido;
  const long* _tempoVerdeMinimo; //o verde tem um tempo mínimo para ficar ligado

  //método auxiliar para ligar e desligar um pino (Encapsulamento)
  void setLuz(int indiceLuz, bool estado) {
    digitalWrite(*_pinos[indiceLuz], estado ? HIGH : LOW);
  }

public:
  //constructor da classe
  Semaforo(const int* pV, const int* pA, const int* pG, const int* pB, 
           const long* tV, const long* tA, const long* tG, const long* tAR, const long* tVM)
    : _pinos{pV, pA, pG}, 
      _pinoBotao(pB),
      _tempoVermelho(tV), 
      _tempoAmarelo(tA), 
      _tempoVerde(tG),
      _tempoAmareloRapido(tAR),
      _tempoVerdeMinimo(tVM)
  {
    Serial.begin(115200);

    //iteração para colocar os pinos no modo OUTPUT
    for (int i = 0; i < 3; i++) {
      pinMode(*_pinos[i], OUTPUT);
      Serial.print("Configurado LED GPIO: ");
      Serial.println(*_pinos[i]);
    }
    
    //botão como INPUT_PULLUP
    pinMode(*_pinoBotao, INPUT_PULLUP);
    Serial.print("Configurado Botão GPIO: ");
    Serial.println(*_pinoBotao);
  }

  //método principal
  void run() {
    
    // Variável para determinar se o ciclo foi acelerado
    bool cicloAcelerado = false;

    //set 1: vermelho
    setLuz(0, HIGH); // Vermelho ON
    setLuz(1, LOW);  // Amarelo OFF
    setLuz(2, LOW);  // Verde OFF
    Serial.println("Estado: VERMELHO (Veículos Parados)");
    delay(*_tempoVermelho);

    //set 2: vermelho e amarelo
    setLuz(0, HIGH); // Vermelho ON
    setLuz(1, HIGH); // Amarelo ON
    setLuz(2, LOW);  // Verde OFF
    Serial.println("Estado: VERMELHO + AMARELO");
    delay(*_tempoAmarelo);

    //set 3: verde 
    setLuz(0, LOW);  // Vermelho OFF
    setLuz(1, LOW);  // Amarelo OFF
    setLuz(2, HIGH); // Verde ON
    Serial.println("Estado: VERDE (Veículos em Andamento)");
    
    //o verde fica ligado em um loop que checa o botão a cada 100ms
    long tempoInicioVerde = millis();
    long tempoRestante = *_tempoVerde;

    while (tempoRestante > 0) {
      //checa se o botão foi apertado (LOW com INPUT_PULLUP)
      if (digitalRead(*_pinoBotao) == LOW) {
        
        //só permite a aceleração se o tempo mínimo de verde passou
        if (millis() - tempoInicioVerde > *_tempoVerdeMinimo) {
          cicloAcelerado = true;
          Serial.println("BOTÃO DE PEDESTRE ATIVADO! ACELERANDO CICLO");
          break; //sai do loop do verde
        }
      }
      
      //atualiza o tempo restante e espera um pouco
      delay(100);
      tempoRestante = *_tempoVerde - (millis() - tempoInicioVerde);
    }
    
    //set 4: amarelo
    
    //escolhe a duração do Amarelo com base no botão
    long duracaoAmarelo = cicloAcelerado ? *_tempoAmareloRapido : *_tempoAmarelo;
    
    setLuz(0, LOW);  // Vermelho OFF
    setLuz(1, HIGH); // Amarelo ON
    setLuz(2, LOW);  // Verde OFF
    
    Serial.print("Estado: AMARELO (Duração: ");
    Serial.print(duracaoAmarelo);
    Serial.println("ms)");
    
    delay(duracaoAmarelo);

    //o loop volta para o set 1 (Vermelho), completando o ciclo.
  }
};

// Pinos definidos
const int PINO_VERMELHO = 18;
const int PINO_AMARELO = 17;
const int PINO_VERDE = 16;
const int PINO_BOTAO = 25; // Pino para o botão de pedestre

// Tempos normais (em milissegundos)
const long TEMPO_VERMELHO = 6000;
const long TEMPO_AMARELO = 2000;
const long TEMPO_VERDE = 4000;

// Tempos de aceleração
const long TEMPO_AMARELO_RAPIDO = 1800;   // Amarelo de 1 segundo (acelerado)
const long TEMPO_VERDE_MINIMO = 1800;     // Verde fica no mínimo 1 segundo, mesmo com botão

// Objeto da classe Semaforo (agora passando ponteiros)
Semaforo meuSemaforo(
  &PINO_VERMELHO, 
  &PINO_AMARELO, 
  &PINO_VERDE, 
  &PINO_BOTAO,
  &TEMPO_VERMELHO, 
  &TEMPO_AMARELO, 
  &TEMPO_VERDE,
  &TEMPO_AMARELO_RAPIDO,
  &TEMPO_VERDE_MINIMO
);

void setup() {
  // O construtor do objeto 'meuSemaforo' já configurou tudo o que é necessário.
  Serial.println("Semaforo Inicializado.");
}

void loop() {
  // Executa o ciclo completo do semáforo
  meuSemaforo.run();
}
