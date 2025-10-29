# Projeto Semáforo Inteligente com Aceleração

Este projeto implementa um semáforo com um recurso adicional: um botão que acelera o tempo do sinal verde, proporcionando maior flexibilidade no controle do tráfego.

## Demonstração

Você pode ver o projeto em funcionamento neste [vídeo demonstrativo](https://youtube.com/shorts/Fo-B6A7Dgps?feature=share).

## Descrição do Projeto

O projeto consiste em um semáforo que funciona com três LEDs (vermelho, amarelo e verde) e inclui um botão que, quando pressionado, acelera o tempo de duração do sinal verde. Esta funcionalidade pode ser útil em situações de baixo fluxo de tráfego ou momentos específicos do dia onde é desejável um ciclo mais rápido do semáforo.

### Componentes Utilizados

- 1x LED Vermelho
- 1x LED Amarelo
- 1x LED Verde
- 1x Botão Push
- Resistores adequados para os LEDs
- Microcontrolador ESP32
- Jumpers
- Protoboard

### Funcionalidades

1. **Operação Normal**

   - Sinal Verde: 4 segundos
   - Sinal Amarelo: 2 segundos
   - Sinal Vermelho: 6 segundos

2. **Modo Acelerado**
   - Quando o botão é pressionado durante o sinal verde, o tempo é reduzido para 1.8 segundos
   - Permite uma transição mais rápida para o próximo estado do semáforo

## Como Reproduzir

1. Monte o circuito conforme o esquema de montagem
2. Carregue o código no Arduino IDE
3. O semáforo iniciará seu ciclo normal automaticamente
4. Para testar o modo acelerado, pressione o botão durante o sinal verde

## Código

O código está disponível no arquivo `ponderada3.ino` neste repositório.

## Autor

Ana Julia Rodrigues Ribeiro
