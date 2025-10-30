# Comunicação UART
A porta UART funciona por interrupção, a cada novo botão pressionado é gerado uma interrupção.
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
Função de envio, ela aparece na função Handler, é realizado o envio caractere 1 a 1.
```cpp
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count){
    // Loop while there are more characters to send.
    while(ui32Count--){
        // Write the next character to the UART.
        MAP_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}
```
