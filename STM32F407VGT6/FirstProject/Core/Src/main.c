
/*
 * Código criando a partir de um novo projeto, a ideia aqui é aprender GPIO
 * Auuuu
 */
#include "main.h"
#define SOLI1_Pin_Positivo GPIO_PIN_11 // Dentro das 16 posições de memória dos GPIOs do por D, esta é a 10
#define SOLI1_Pin_Negativo GPIO_PIN_10 // Dentro das 16 posições de memória dos GPIOs do por D, esta é a 10
#define SOLI1_GPIO_Port GPIOD // Posição de memória de 32 bits onde este bit em questão ativa os GPIOs da porta D

void SystemClock_Config(void);



int main(void)
{

  HAL_Init();
  SystemClock_Config();


  // ---------------------------------------------------------

  	  HAL_GPIO_WritePin(SOLI1_GPIO_Port,SOLI1_Pin,GPIO_PIN_RESET); // CONFIGURA COMO SAÍDA

	  GPIO_InitTypeDef GPIO_InitStruct;
	  GPIO_InitStruct.Pin 	= SOLI1_Pin_Positivo | SOLI1_Pin_Negativo;
	  GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull 	= GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(SOLI1_GPIO_Port,&GPIO_InitStruct);

  // ---------------------------------------------------------

  while (1)
  {

  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
