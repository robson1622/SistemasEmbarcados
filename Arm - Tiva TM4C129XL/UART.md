```cpp
void UARTIntHandler(void)
{
    uint32_t ui32Status;

    //Pega o status da interrupção
    ui32Status = MAP_UARTIntStatus(UART0_BASE, true);

    //É preciso sempre desativar/limpar a interrupção
    MAP_UARTIntClear(UART0_BASE, ui32Status);

    // Loop para tratar de todos os caracteres recebidos na fila FIFO
    while(MAP_UARTCharsAvail(UART0_BASE))
    {
        // pega o caractere novo
        char c = MAP_UARTCharGetNonBlocking(UART0_BASE);
        // escreve de volta no UART
        MAP_UARTCharPutNonBlocking(UART0_BASE, c);

        // Pisca a cada entrada recebida
        // Blink the LED to show a character transfer is occuring
        MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
        SysCtlDelay(g_ui32SysClock / (1000 * 3));
        // Turn off the LED
        MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);

    }
}
```
