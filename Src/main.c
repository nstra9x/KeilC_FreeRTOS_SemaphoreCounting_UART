#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include "string.h"
#include "stdio.h"

UART_HandleTypeDef huart3;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);

TaskHandle_t HPTHandler;
void HPT_TASK(void *pvParameter);

TaskHandle_t MPTHandler;
void MPT_TASK(void *pvParameter);

TaskHandle_t LPTHandler;
void LPT_TASK(void *pvParameter);

TaskHandle_t VLPTHandler;
void VLPT_TASK(void *pvParameter);

SemaphoreHandle_t CountingSem;

int resource[3] = {111,222,333};
int indx = 0;

uint8_t rx_data = 0;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART3_UART_Init();
	
	HAL_UART_Receive_IT(&huart3, &rx_data, 1);
	
	CountingSem = xSemaphoreCreateCounting(3,0);
	if(CountingSem == NULL)
		HAL_UART_Transmit(&huart3, (uint8_t *) "Khong the tao Semaphore\r\r", 25, 100);
	else
		HAL_UART_Transmit(&huart3, (uint8_t *) "Tao Semaphore thanh cong\r\r", 26, 100);
	
	xTaskCreate(HPT_TASK, "HPT", 128, NULL, 3, &HPTHandler);
	xTaskCreate(MPT_TASK, "MPT", 128, NULL, 2, &MPTHandler);
	xTaskCreate(LPT_TASK, "LPT", 128, NULL, 1, &LPTHandler);
	xTaskCreate(VLPT_TASK, "VLPT", 128, NULL, 0, &VLPTHandler);
	
	vTaskStartScheduler();
}

void HPT_TASK(void *pvParameter)
{
	char sresource[3];
	int semcount = 0;
	char ssemcount[2];
	
	xSemaphoreGive(CountingSem);
	xSemaphoreGive(CountingSem);
	xSemaphoreGive(CountingSem);
	
	while(1)
	{
		char str[150];
		strcpy(str, "Chay task HPT\rYeu cau semaphore\r");
		semcount = uxSemaphoreGetCount(CountingSem);
		sprintf(ssemcount, "%d\r\r", semcount);
		strcat(str, "So semaphore san co: ");
		strcat(str, ssemcount);
		HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
		
		xSemaphoreTake(CountingSem, portMAX_DELAY);
		
		sprintf(sresource, " %d\r", resource[indx]);
		strcpy(str, "Thoat task HPT\rDu lieu co duoc la:: ");
		strcat(str, sresource);
		strcat(str, "Khong tra lai Semaphore\r\r");
		HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
		
		indx++;
		if(indx>2)
			indx = 0;
		vTaskDelay(1000);
	}
}

void MPT_TASK(void *pvParameter)
{
	char sresource[3];
	int semcount = 0;
	char ssemcount[2];
	
	while(1)
	{
		char str[150];
		strcpy(str, "Chay task MPT\rYeu cau semaphore\r");
		semcount = uxSemaphoreGetCount(CountingSem);
		sprintf(ssemcount, "%d\r\r", semcount);
		strcat(str, "So semaphore san co: ");
		strcat(str, ssemcount);
		HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
		
		xSemaphoreTake(CountingSem, portMAX_DELAY);
		
		sprintf(sresource, " %d\r", resource[indx]);
		strcpy(str, "Thoat task MPT\rDu lieu co duoc la:: ");
		strcat(str, sresource);
		strcat(str, "Khong tra lai Semaphore\r\r");
		HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
		
		indx++;
		if(indx>2)
			indx = 0;
		vTaskDelay(1000);
	}
}

void LPT_TASK(void *pvParameter)
{
	char sresource[3];
	int semcount = 0;
	char ssemcount[2];
	
	while(1)
	{
		char str[150];
		strcpy(str, "Chay task LPT\rYeu cau semaphore\r");
		semcount = uxSemaphoreGetCount(CountingSem);
		sprintf(ssemcount, "%d\r\r", semcount);
		strcat(str, "So semaphore san co: ");
		strcat(str, ssemcount);
		HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
		
		xSemaphoreTake(CountingSem, portMAX_DELAY);
		
		sprintf(sresource, " %d\r", resource[indx]);
		strcpy(str, "Thoat task LPT\rDu lieu co duoc la:: ");
		strcat(str, sresource);
		strcat(str, "Khong tra lai Semaphore\r\r");
		HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
		
		indx++;
		if(indx>2)
			indx = 0;
		vTaskDelay(1000);
	}
}

void VLPT_TASK(void *pvParameter)
{
	char sresource[3];
	int semcount = 0;
	char ssemcount[2];
	
	while(1)
	{
		char str[150];
		strcpy(str, "Chay task VLPT\rYeu cau semaphore\r");
		semcount = uxSemaphoreGetCount(CountingSem);
		sprintf(ssemcount, "%d\r\r", semcount);
		strcat(str, "So semaphore san co: ");
		strcat(str, ssemcount);
		HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
		
		xSemaphoreTake(CountingSem, portMAX_DELAY);
		
		sprintf(sresource, " %d\r", resource[indx]);
		strcpy(str, "Thoat task VLPT\rDu lieu co duoc la:: ");
		strcat(str, sresource);
		strcat(str, "Khong tra lai Semaphore\r\r");
		HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
		
		indx++;
		if(indx>2)
			indx = 0;
		vTaskDelay(1000);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(&huart3, &rx_data, 1);
	if(rx_data == 'r')
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		
		xSemaphoreGiveFromISR(CountingSem, &xHigherPriorityTaskWoken);
		xSemaphoreGiveFromISR(CountingSem, &xHigherPriorityTaskWoken);
		xSemaphoreGiveFromISR(CountingSem, &xHigherPriorityTaskWoken);
		
		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
	}
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
	}

}

static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

void Error_Handler(void)
{
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
