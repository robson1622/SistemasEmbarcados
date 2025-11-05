# SysTick
Este é a ferramenta/circuito pricipal de controle de tempo da Tiva. Com ele podemos agendar interrupções
a cada intervalo de tempo programado.

Segue um exemplo de declaração da inicialização do SysTick:
```cpp
static void systick_init_1ms(void)
{
    SysTickDisable();
    SysTickIntDisable();     

    g_ticks_ms = g_sysclk / 1000U;     // nº de clocks por milissegundo
    SysTickPeriodSet(g_ticks_ms);      // configura o período do SysTick

    IntPrioritySet(FAULT_SYSTICK, 0x80); // prioridade média para SysTick
    IntPrioritySet(INT_GPIOJ,  0x00);    // prioridade alta para botão

    SysTickIntEnable();  // habilita interrupção SysTick
    SysTickEnable();     // inicia o contador
}

```
Então, na sua função de tratamento de interrupção podemos implementar várias outras chamadas se necessário:
```cpp
void SysTick_Handler(void)
{
    if (g_ms < 3000U) {
        g_ms++;
    } else {
        g_timeout = true;
    }
}
```
