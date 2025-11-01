# Paralelismo com ThreadX
## Recursos
- [Thread](#Thread)
- [Fila](#Fila)
- [Flags de evento](#Flags_de_evento)
- [Mutex](#Mutex)
- [Semaforo](#Semaforo)
- [Pool](#Pool)
- [Block Pool](#Block_pool)

## Thread
Inicialização. Toda a thread deve possuir os seguintes objetos iniciados.
```cpp
/* Define o objeto de controle da thread...  */
TX_THREAD               thread;
/* Define um contador para ser usado na thread  */
ULONG                   thread_counter;
/*Define a Stack que será usada pela thread (Espaço de memória e tamanho)  */
UCHAR                   thread_stack[STACK_SIZE];
```
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
## Fila
A fila é o principal meio de comunicação entre duas threads, ela é um espaço de memória onde uma ou mais threads escrevem para uma ou mais threads lerem.

Temos então a sua declaração:
```cpp
/* Definimos o seu objeto de controle */
TX_QUEUE                queue;
/* Definimos o seu tamaho e posição na memória  */
UCHAR                   queue_area[QUEUE_SIZE*sizeof(ULONG)];
/* Muito importante : AS MENSAGEMS PRECISAM DE UM CONTADOR PARA INDICA ALGUMA COISA??? */
ULONG                   thread_A_messages_sent;
ULONG                   thread_B_messages_received;
```
Sua inicialização :
```cpp
    /* Create the message queue shared by threads A and B.  */
    tx_queue_create(&queue, "queue", TX_1_ULONG, queue_area, QUEUE_SIZE*sizeof(ULONG));
```
E por fim a sua utilização :
```cpp
        /*Enviando a mensagem dentro da threas A */
        UINT    status;
        status =  tx_queue_send(&queue, &thread_A_messages_sent, TX_WAIT_FOREVER);
        /*Aqui vem o tratamento de erros*/
        if (status != TX_SUCCESS)
            break;
        /*Incrementa as mesagens enviadas*/
        thread_1_messages_sent++;


        /*Recebendo a mensagem dentro da thread B */
        ULONG   received_message;
        UINT    status;
        status = tx_queue_receive(&queue_0, &received_message, TX_WAIT_FOREVER);
        /* Verificamos o status e se a mensagem recebida é o que se esperava*/
        if ((status != TX_SUCCESS) || (received_message != thread_2_messages_received))
            break;
        /* Se tudo estiver correto, incrementa  */
        thread_2_messages_received++;
```
