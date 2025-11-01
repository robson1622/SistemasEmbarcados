# Paralelismo com ThreadX
## Recursos
- [Thread](#Thread)
- [Fila](#Fila)
- [Flags de evento](#Flags_de_evento)
- [Mutex](#Mutex)
- [Semaforo](#Semáforo)
- [Pool](#Pool)
- [Block Pool](#Block_pool)

## Thread
Declaração. Toda a thread deve possuir os seguintes objetos declarados.
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

Inicialização :
```cpp
// Toda thread tem uma rotina definida
void    thread_entry(ULONG thread_input){
    // ....
}
// Inicialização de threads :
void    tx_application_define(void *first_unused_memory)
{
    /* Create the main thread.  */
    tx_thread_create(&thread,   // Endereço do objeto de controle da thread
            "thread",           // Nome da thread
            thread_entry,       // Função de rotina/entrada
            0,                  // 
            thread_stack,       // Endereço de incio do espaço de memória de trabalho
            DEMO_STACK_SIZE,    // Tamanho do espaço de memória de trabalho
            1,                  //
            1,                  //
            TX_NO_TIME_SLICE,   // Por quanto tempo esta thread pode ser executada
            TX_AUTO_START);     // Inicialização automática
}
// Para que todas as threads iniciem, precisa chamar a função do ThreadX
int main(){
    //... Dentro da main 
    tx_kernel_enter();
}
```
Utilização :
```cpp
/* A função passada na referência de tx_thread_create(...) é a thread que vai rodar*/
thread_entry(ULONG thread_input){
    while(1) {
        /*Então tudo aqui dentro vai continuar sendo executado*/
    }
}
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

Para enviar :
```cpp
        /*Enviando a mensagem dentro da threas A */
        UINT    status;
        status =  tx_queue_send(&queue, &thread_A_messages_sent, TX_WAIT_FOREVER);
        /*Aqui vem o tratamento de erros*/
        if (status != TX_SUCCESS)
            break;
        /*Incrementa as mesagens enviadas*/
        thread_A_messages_sent++;

```
Para receber :
```cpp
        /*Recebendo a mensagem dentro da thread B */
        ULONG   received_message;
        UINT    status;
        status = tx_queue_receive(&queue_0, &received_message, TX_WAIT_FOREVER);
        /* Verificamos o status e se a mensagem recebida é o que se esperava*/
        if ((status != TX_SUCCESS) || (received_message != thread_B_messages_received))
            break;
        /* Se tudo estiver correto, incrementa  */
        thread_B_messages_received++;
```
## Mutex
## Semáforo
## 
