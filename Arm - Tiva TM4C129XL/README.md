# Estudo de Sistemas Embarcados

## Sumário
- [UART](UART.md)
- [ThreadX](ThreadX.md)
- [SysTick](SysTick.md)
- [GPIO](GPIO.md)

## Introdução
Este é um compilado de explicações breves sobre os recursos da Tiva TM4C1294XL, como configura-los e como os usar.

## UART
Periférico de comunicação. Com o USB do computador conectado a placa é possível, assim como no arduino, permitir enviar mensagens para a placa e receber mensagens dela no terminal.

## ThreadX
Biblioteca que implementa o kernel de threads na placa. Ela implementa não só threads como comunicação entre elas,
mecanismos de escalonamento e mecanismos de explusão mútua.

## SysTick
Principal periférico responsável por tratar de tempo, pode-se usar ele para diversos fins relativos ao tempo.

## GPIO
Ligar ou desligar um LED ou ligar ou desligar algo conectado a um GPIO.
