/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart_ring.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef DateToUpdate = {0};
char trans_str[64] = {0,};
///char trans[64] = "t-TIME \n";
//uint8_t b = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
        if(htim->Instance == TIM1) //check if the interrupt comes from TIM1
        {
       snprintf(trans_str, 63, "t-TIME \n");
       HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
       snprintf(trans_str, 63, "?-HELP \n");
       HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
       HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
       snprintf(trans_str, 63, "Time %d:%d:%d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
       HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
       HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
       snprintf(trans_str, 63, "Date %d-%d-20%d\n", DateToUpdate.Date, DateToUpdate.Month, DateToUpdate.Year);
       HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);

        }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  __HAL_UART_ENABLE_IT(&MYUART, UART_IT_RXNE); // включить прерывания usart'
  HAL_TIM_Base_Start_IT(&htim1);
  snprintf(trans_str, 63, "t-TIME \n");
  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
  snprintf(trans_str, 63, "?-HELP \n");
  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */


	     /* USER CODE END WHILE */

	 	          if(uart_available()) // есть ли что-то в приёмном буфере, тогда читаем
	 	                   {
	 	                           char str[SIZE_BF] = {0,};
	 	                       //    char str1[SIZE_BF] = {0,};
	 	                           uint8_t i = 0;
	                                uint8_t b = 0;
	                             //   uint8_t temp;
	 	                           while(uart_available())
	 	                           {
	 	                                   str[i++] = uart_read(); // читаем байт

	 	                                   if(i == SIZE_BF - 1)
	 	                                   {
	 	                                         //  str[i] = '\0';
	 	                                           break;
	 	                                   }

	 	                                   HAL_Delay(1);
	 	                           }

	 	                          // str[i] = '\0';

	 	                        ///  HAL_UART_Transmit(&MYUART, (uint8_t*)str, strlen(str), 100); // отправляем обратно что получили
	 	                        /// memcpy(str1, str, 32);

	                      b = str[0];
	 ////temp = str[1];
	              if(b=='?')
	              {
	             	  snprintf(trans_str, 63, "Set hour - hxx \n");
	             	  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	             	  snprintf(trans_str, 63, "Set min - mxx \n");
	             	  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	             	  snprintf(trans_str, 63, "Set sec - sxx \n");
	             	  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	             	  snprintf(trans_str, 63, "Set date - dxx \n");
	             	  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	                   snprintf(trans_str, 63, "Set month - mxx \n");
	             	  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	             	  snprintf(trans_str, 63, "Set year - yxx \n");
	             	  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	             	  snprintf(trans_str, 63, "Vmesto xx chisla 00, 01, ....  \n");
	             	  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);

	              }
	              if(b=='t')
	              {
	             	  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
	                   snprintf(trans_str, 63, "Time %d:%d:%d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
	                   HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);

	                   HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
	                   snprintf(trans_str, 63, "Date %d-%d-20%d\n", DateToUpdate.Date, DateToUpdate.Month, DateToUpdate.Year);
	                   HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	              }

	             if(b=='h')
	             {
	             	 sTime.Hours =   10*(str[1] & 0x0F) + (str[2] & 0x0F);
	                  HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	                  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
	                  snprintf(trans_str, 63, "Time %d:%d:%d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
	                  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	                  HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
	                  snprintf(trans_str, 63, "Date %d-%d-20%d\n", DateToUpdate.Date, DateToUpdate.Month, DateToUpdate.Year);
	                  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);

	              }
	             if(b=='m')
	              {
	              sTime.Minutes =   10*(str[1] & 0x0F) + (str[2] & 0x0F);
	              HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	              HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
	              snprintf(trans_str, 63, "Time %d:%d:%d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
	              HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	              HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
	              snprintf(trans_str, 63, "Date %d-%d-20%d\n", DateToUpdate.Date, DateToUpdate.Month, DateToUpdate.Year);
	              HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	               }
	             if(b=='s')
	               {
	              sTime.Seconds =   10*(str[1] & 0x0F) + (str[2] & 0x0F);
	              HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	              HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
	              snprintf(trans_str, 63, "Time %d:%d:%d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
	              HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	              HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
	              snprintf(trans_str, 63, "Date %d-%d-20%d\n", DateToUpdate.Date, DateToUpdate.Month, DateToUpdate.Year);
	              HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	                                    }
	             if(b=='d')
	                {
	              DateToUpdate.Date =   10*(str[1] & 0x0F) + (str[2] & 0x0F);
	              HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
	              HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
	              snprintf(trans_str, 63, "Time %d:%d:%d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
	              HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	              HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
	              snprintf(trans_str, 63, "Date %d-%d-20%d\n", DateToUpdate.Date, DateToUpdate.Month, DateToUpdate.Year);
	              HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	                                   }
	             if(b=='f')
	                {
	              DateToUpdate.Month =   10*(str[1] & 0x0F) + (str[2] & 0x0F);
	              HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
	              HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
	              snprintf(trans_str, 63, "Time %d:%d:%d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
	              HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	              HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
	              snprintf(trans_str, 63, "Date %d-%d-20%d\n", DateToUpdate.Date, DateToUpdate.Month, DateToUpdate.Year);
	              HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	                                                           }
	             if(b=='y')
	                 {
	              DateToUpdate.Year =   10*(str[1] & 0x0F) + (str[2] & 0x0F);
	              HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
	              HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
	              snprintf(trans_str, 63, "Time %d:%d:%d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
	              HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	              HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
	              snprintf(trans_str, 63, "Date %d-%d-20%d\n", DateToUpdate.Date, DateToUpdate.Month, DateToUpdate.Year);
	              HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
	 	                   }

	     /* USER CODE BEGIN 3 */
	   }
	   /* USER CODE END 3 */
	 }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 10;
  sTime.Minutes = 10;
  sTime.Seconds = 0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_MAY;
  DateToUpdate.Date = 8;
  DateToUpdate.Year = 22;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 39999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 50000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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

