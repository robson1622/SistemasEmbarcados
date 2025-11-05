# GPIO
Os GPIOs da placa estão definidos em um arquivo dentro do TivaWare. Garanta que este está incluido dentro o Keil antes de começar.

Inclua onde está declarado o GPIO.
```cpp
#include "driverlib/gpio.h"
// indicado declarar nomes mais amigáveis/reconhecíveis
#define LED_PIN    GPIO_PIN_1
#define BTN_PIN    GPIO_PIN_0
```
Inicialização:
```cpp
/* PARA UM PINO DE SAÍDA COMO O DO LED*/
static void GPIO_PORTN_INIT(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION); // Ativa a porta GPION da plca
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {} // Verifica se o acesso ao periférico está ativo
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0); // seta a direção do pino (saída)
}

/* PARA UM PINO DE ENTRADA COMO UM BOTÃO */
static void GPIO_PORTJ_INIT(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)) {}
    // configurando a interrupção
    GPIOIntDisable(GPIO_PORTJ_BASE, GPIO_PIN_0); // Desabilita antes de configurar
    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_0); // Se sertifica de nenhuma flag ativa
    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE); // Seleciona o evento de disparo
    GPIOIntRegister(GPIO_PORTJ_BASE, GPIOJ_Handler); // Registra a função de tratamento/interrupção
    GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_PIN_0); // Habilita a interrupção no pino
    IntEnable(INT_GPIOJ);  // Habilita a interrupção no NVIC
}
```
Para o caso da entrada com o botão, podemos declarar a interupção:
```cpp
void GPIOJ_Handler(void)
{
    // Limpa a flag de interrupção
    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_0);

    // Ação desejada (exemplo: alternar LED)
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0,
        ~GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_0) & GPIO_PIN_0);
}

```
E para o caso de ligar/desligar um GPIO previamente declarado como saída:
```cpp
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0); // Ligar 1, desligar 0
```


