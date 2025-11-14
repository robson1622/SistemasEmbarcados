# GPIO

Assim como nas outras plataformas, é necessário configurar :
1. Habilitar o clock da porta (GPIOx).
2. Configurar o modo de direção (Entrada, Saída, AF, Analógico).
3. Definir as características elétricas (Tipo de saída, Velocidade, Pull-up/Pull-down).
4. Controlar os dados (para uso como Entrada ou Saída).

## Conceitos importantes
### Resistores
|Nomeclatura| Imagem do circuito | Explicação |
|-----------|--------------------|------------|
| Pull up (puxar para cima) |[pull up](./images/pull_up.JPG)|Uma entrada do microcontrolador é ligada por uma resistência ao VCC, nesta mesmo nó é ligado um botão por uma ponta e na outra ponta do botão ele é ligado ao GND.|
| Pull down (puxar para baixo) | [pull down](./images/pull_down.JPG)| Funciona da mesma forma do anterior, porém com o sinal invertido entre a entrada do botão e do resistor.|

### Modos do GPIO
#### Input Floating
A entrada não fica ligada a nenhum resistor nem a transistores, o seu valor é definido somente pelo circuito de entrada.
```cpp
  GPIO_InitStructure.Mode = 
```
#### 











### GPIOs de solenoides do projeto I2Horti
```cpp
#define SOLI1_Pin GPIO_PIN_10 // Bit específico dentro do registrador
#define SOLI1_GPIO_Port GPIOD // Mesmo registrador
#define SOLI2_Pin GPIO_PIN_11
#define SOLI2_GPIO_Port GPIOD
#define SOLI3_Pin GPIO_PIN_12
#define SOLI3_GPIO_Port GPIOD
#define SOLI4_Pin GPIO_PIN_13
#define SOLI4_GPIO_Port GPIOD
#define SOLI5_Pin GPIO_PIN_14
#define SOLI5_GPIO_Port GPIOD
#define SOLI6_Pin GPIO_PIN_15
#define SOLI6_GPIO_Port GPIOD
#define SOLCOMI_Pin GPIO_PIN_6
#define SOLCOMI_GPIO_Port GPIOC
#define SOLI7_Pin GPIO_PIN_7
#define SOLI7_GPIO_Port GPIOC
#define SOLI8_Pin GPIO_PIN_8
#define SOLI8_GPIO_Port GPIOC
```
