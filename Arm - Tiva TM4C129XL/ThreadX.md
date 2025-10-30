# Paralelismo com ThreadX

É preciso configurar algum sistema de timer para que as interrupções periódicas funcionem no ThreadX, no caso da tiva é o SysTick,
que deve ser configurado no arquivo tx_initialize_low_level (informação disponível em [Chapter2](https://github.com/eclipse-threadx/rtos-docs/blob/main/rtos-docs/threadx/chapter2.md)
```cpp
// Antes de começar, precisamos inicializar o sistema

int main(){
    // configuramos o clock da placa
    SystemCoreClock = SysCtlClockFreqSet(... /* olhar no SysTick*/);

    // Inicializar Kernel do ThreadX
    tx_kernel_enter();

}
```
```cpp
// Alocando recursos do sistema

tx_byte_pool_create(&byte_pool_0, "nome",memory_area, TAMANHO);
tx_byte_allocate(&byte_pool_0, &pointer, TAMANHO, TX_NO_WAIT);

// Criando as Threads

tx_thread_create(&thread, "nome",função_entry,parametro,
                 stack_prt, stack_size,
                 prioridade, prioridade_preempção, time_slice, auto_start );
```
