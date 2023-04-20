/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "lib_lcd_16x02_i2c.h"
#include "lib_dht11.h"
#include "stdio.h"
//#include "lib_lcd_20x04_i2c.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


void delay (uint16_t time)
{
	/* change your code here for the delay in microseconds */
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	while ((__HAL_TIM_GET_COUNTER(&htim6))<time);
}

void Display_Temp (float Temp)
{
	char str[20] = {0};
	lcd_16x02_gotoxy(1, 1);

	sprintf (str, "TEMP:- %.2f ", Temp);
	lcd_16x02_send_string(str);
	lcd_16x02_send_data('C');
}

void Display_Rh (float Rh)
{
	char str[20] = {0};
	lcd_16x02_gotoxy(1, 0);

	sprintf (str, "HUM:- %.2f ", Rh);
	lcd_16x02_send_string(str);
	lcd_16x02_send_data('%');
}

uint8_t rh_byte1, rh_byte2, temp_byte1, temp_byte2;
uint16_t SUM, RH, TEMP;

float temperatura = 0;
float humedad = 0;
uint8_t presencia = 0;

/*
void set_pin_output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void set_pin_input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
*/
/*
void DHT11_Start (void)
{
	Set_Pin_Output (GPIO_DHT11_GPIO_Port, GPIO_DHT11_Pin);  // set the pin as output
	HAL_GPIO_WritePin (GPIO_DHT11_GPIO_Port, GPIO_DHT11_Pin, GPIO_PIN_RESET);   // pull the pin low
	delay (18000);   // wait for 18ms
    HAL_GPIO_WritePin (GPIO_DHT11_GPIO_Port, GPIO_DHT11_Pin, GPIO_PIN_SET);   // pull the pin high
	delay (20);   // wait for 20us
	Set_Pin_Input(GPIO_DHT11_GPIO_Port, GPIO_DHT11_Pin);    // set as input
}

uint8_t DHT11_Check_Response (void)
{
	uint8_t Response = 0;
	delay (40);
	if (! (HAL_GPIO_ReadPin (GPIO_DHT11_GPIO_Port, GPIO_DHT11_Pin)))
	{
		delay (80);
		if ((HAL_GPIO_ReadPin (GPIO_DHT11_GPIO_Port, GPIO_DHT11_Pin))) Response = 1;
		else Response = -1; // 255
	}
	while ((HAL_GPIO_ReadPin (GPIO_DHT11_GPIO_Port, GPIO_DHT11_Pin)));   // wait for the pin to go low

	return Response;
}

uint8_t DHT11_Read (void)
{
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin (GPIO_DHT11_GPIO_Port, GPIO_DHT11_Pin)));   // wait for the pin to go high
		delay (40);   // wait for 40 us
		if (!(HAL_GPIO_ReadPin (GPIO_DHT11_GPIO_Port, GPIO_DHT11_Pin)))   // if the pin is low
		{
			i&= ~(1<<(7-j));   // write 0
		}
		else i|= (1<<(7-j));  // if the pin is high, write 1
		while ((HAL_GPIO_ReadPin (GPIO_DHT11_GPIO_Port, GPIO_DHT11_Pin)));  // wait for the pin to go low
	}
	return i;
}
*/

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int row=1;
int col=1;
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
  MX_I2C1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start(&htim6);

  /*
  lcd_16x02_init ();

  lcd_16x02_put_cur(1, 1);
  lcd_16x02_send_string ("Hola Mundo");
  HAL_Delay(1000);

  lcd_16x02_put_cur(1, 2);
  lcd_16x02_send_string("Ricardo Palma");

  HAL_Delay(4000);

  lcd_16x02_clear ();
   */


  // codigo de LCD
  /*
  lcd_16x02_init ();
  lcd_16x02_gotoxy(1, 1);
  lcd_16x02_send_string ("RICARDO ROBERTO PALMA VENTURA");

  HAL_Delay(1000);
  */

  lcd_16x02_init ();
  //dht11_init(GPIOA, GPIO_PIN_1);
  HAL_Delay(3000);
  lcd_16x02_gotoxy(1, 1);
  lcd_16x02_send_string ("TEMP:- 24.0C");
  lcd_16x02_send_string ("   HUM:- 30%");

  /*
  lcd_16x02_send_string ("       ");
  lcd_16x02_send_string ("TEMP:- 24.0C");
  lcd_16x02_send_string ("   HUM:- 30%");
  */
/*
  lcd_16x02_gotoxy(1, 1);
  lcd_16x02_send_string ("TEMP:- 24.0C");
  lcd_16x02_send_string ("   HUM:- 30%");

  HAL_Delay(3000);
*/
  //lcd_16x02_gotoxy(2, 1);
  //lcd_16x02_send_string ("HUM:- 35.0");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */
	  /*
	  	  presencia = dht11_check_response();
	  	  rh_byte1 = dht11_read_data ();
	  	  rh_byte2 = dht11_read_data ();
	  	  temp_byte1 = dht11_read_data ();
	  	  temp_byte2 = dht11_read_data ();
	  	  SUM = dht11_read_data();

	  	  TEMP = temp_byte1;
	  	  RH = rh_byte1;

	  	  temperatura = (float) TEMP;
	  	  humedad = (float) RH;
	  	  */
	  /*
	  lcd_16x02_gotoxy(1, 1);
	  lcd_16x02_send_string ("TEMP:- 24.0C");
	  lcd_16x02_send_string ("   HUM:- 30%");

	  HAL_Delay(3000);
	   */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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
