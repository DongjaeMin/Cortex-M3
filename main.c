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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TxBufferSize (countof(TxBuffer)-1)
#define RxBufferSize 0xFF
#define countof(a)	(sizeof(a) / sizeof(*(a)))
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
 int flag_SW1=0;
 int flag_SW2=0;
 int count=0;
 int Mentos =0;

 uint32_t IC1, IC2;
 int CaptureFlag;
 float flag_distance;
 int inventory;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void delay_us(uint16_t delay)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while(__HAL_TIM_GET_COUNTER(&htim1) < delay);
}

void Trig()
{
	HAL_GPIO_WritePin(GPIOA, Trig_Pin, GPIO_PIN_SET);
	delay_us(10);
	HAL_GPIO_WritePin(GPIOA, Trig_Pin, GPIO_PIN_RESET);
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
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_Base_Start(&htim1);
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	Trig();
	printf("%d\r\n", inventory);
	HAL_Delay(250);

	while(flag_SW1==1) //??????????????????
	{
		//1
		HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_RESET);
		//count = 1;
		if(flag_SW2==1) //?????????
		{
			//2
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//3
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//4
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin , GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//1
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_RESET);

			//2
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);
			flag_SW1=0;
			flag_SW2=0;
			Mentos = 2;
			//printf("Mentos = %ld\r\n", Mentos);
			//buzzer
			for(int i=0; i<Mentos; i++)
			{
				__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 500);
				HAL_Delay(1000);
				__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 2500);
				HAL_Delay(1000);

			}
			break;
		}


		//2 ????????????????????
		HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);
		count = 2;
		if(flag_SW2==1)
		{
			//3
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//4
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin , GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//1
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_RESET);

			//2
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//3
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);
			Mentos = 3;
			//printf("Mentos = %ld\r\n", Mentos);
			//buzzer
			for(int i=0; i<Mentos; i++)
			{
				__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 500);
				HAL_Delay(1000);
				__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 2500);
				HAL_Delay(1000);
			}
			flag_SW1=0;
			flag_SW2=0;
			break;
		}

		//3 ????????????????????
		HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);
		count = 3;
		if(flag_SW2==1)
		{
			//4
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin , GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//1
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_RESET);

			//2
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//3
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//4
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin , GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);
			Mentos = 4;
			//printf("Mentos = %ld\r\n", Mentos);
			//buzzer

			for(int i=0; i<Mentos; i++)
			{
				__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 500);
				HAL_Delay(1000);
				__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 2500);
				HAL_Delay(1000);
			}
			flag_SW1=0;
			flag_SW2=0;
			break;
		}

		//4 ????????????????????
		HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin , GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);
		count = 4;
		if(flag_SW2==1)
		{
			//1
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_RESET);

			//2
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, A_Pin | E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//3
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | D_Pin | C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//4
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin , GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_GPIO_WritePin(GPIOC, B_Pin | C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, G_Pin, GPIO_PIN_RESET);

			//1
			HAL_GPIO_WritePin(GPIOC, COM1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, COM2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, COM4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, C_Pin, GPIO_PIN_RESET);
			Mentos = 1;
			flag_SW1=0;
			flag_SW2=0;
			//printf("Mentos = %ld\r\n", Mentos);
			//buzzer
			for(int i=0; i<Mentos; i++)
			{
				__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 500);
				HAL_Delay(1000);
				__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 2500);
				HAL_Delay(1000);
			}
			break;
		}

	}
    /* USER CODE END WHILE */

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
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

  /** Initializes the CPU, AHB and APB buses clocks
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
  htim1.Init.Prescaler = 64-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 64-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 64-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 20000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 2500;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

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
  huart1.Init.BaudRate = 9600;
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  HAL_GPIO_WritePin(GPIOC, A_Pin|B_Pin|C_Pin|D_Pin
                          |E_Pin|F_Pin|G_Pin|COM1_Pin
                          |COM2_Pin|COM3_Pin|COM4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Trig_GPIO_Port, Trig_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : B1_Pin SW1_Pin SW2_Pin */
  GPIO_InitStruct.Pin = B1_Pin|SW1_Pin|SW2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : A_Pin B_Pin C_Pin D_Pin
                           E_Pin F_Pin G_Pin COM1_Pin
                           COM2_Pin COM3_Pin COM4_Pin */
  GPIO_InitStruct.Pin = A_Pin|B_Pin|C_Pin|D_Pin
                          |E_Pin|F_Pin|G_Pin|COM1_Pin
                          |COM2_Pin|COM3_Pin|COM4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : Trig_Pin */
  GPIO_InitStruct.Pin = Trig_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Trig_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==SW1_Pin)
	{
		flag_SW1 = 1;
	}
	if(GPIO_Pin==SW2_Pin)
	{
		flag_SW2 = 1;
	}
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if (CaptureFlag == 0)
		{
			IC1 = TIM2->CCR1;
			CaptureFlag = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (CaptureFlag == 1)
		{
			IC2 = TIM2->CCR1;
			flag_distance = 340 * (IC2 - IC1) * 0.000001 / 2 * 100;
			if(flag_distance >= 15)
			{
				inventory = 1;
			}
			if(flag_distance < 15)
			{
				inventory = 0;
			}
			__HAL_TIM_SET_COUNTER(&htim2, 0);
			CaptureFlag = 0;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
		}
	}
}
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
