/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/app_main.c 
  * @author  MCD Application Team
  * @version V1.8.1
  * @date    27-January-2022
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include <stdio.h>

/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
uint32_t TEMP_U32 = 0;
#define DEBUG_U32(var_addr) 	do {						\
														memset(&TEMP_U32, 0, sizeof(uint32_t));		\
														memcpy(&TEMP_U32, var_addr, sizeof(uint32_t));	\
														for(uint8_t db_count = 0; db_count < 1; db_count++);	\
												} 																						\
												while(0);
												
#define VIEW_DEGUB 			for(uint8_t db_count = 0; db_count < 1; db_count++);
																							

/* Private variables ---------------------------------------------------------*/								
static __IO uint64_t TickCount;
												
																							
uint8_t aTxBuffer[] = "\n\rUSART Hercules Interrupts Example: USART-Hercules communication using Interrupt\n\r";
uint8_t aRxBuffer[RXBUFFERSIZE] = {0};
uint8_t ubNbrOfDataToTransfer = TXBUFFERSIZE;
uint8_t ubNbrOfDataToRead = RXBUFFERSIZE;
__IO uint8_t ubTxCounter = 0; 
__IO uint16_t uhRxCounter = 0;

/* Private function prototypes -----------------------------------------------*/
												
static uint64_t get_TickCount(void);										

static void NVIC_Config(void);
static void TIM_Config(void);
static void GPIO_Config(void);
static void USART_Config(void);

static void Delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int app_main(void)
{
  
 
 /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files before to branch to application main.
       To reconfigure the default setting of SystemInit() function, 
       refer to system_stm32f4xx.c file */\
	
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files (startup_stm32f40_41xxx.s/startup_stm32f427_437xx.s/startup_stm32f429_439xx.s)
       before to branch to application main. 
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */ 
	
	
	/* NVIC config: TIM7, USART6 */
	NVIC_Config();
	
  /* TM7 end of count event each 1ms */
	TIM_Config();
	
	/* Init Button and LED */
	GPIO_Config();
	GPIO_SetBits(GPIOD, LED2_PIN);			// ORANGE LED ON
	
	/* USART6 Config */
	USART_Config();
	
	/* Insert 5000 ms delay */
  Delay(5000);
	
  /* Output a message on Hercules using printf function - Cause SERIOUS TROUBLE */
//  printf("\n\rUSART Printf Example: retarget the C library printf function to the USART\n\r");
  
  /* Add your application code here */
	do
	{
		/* Enable the USART6 Transmit interrupt: this interrupt is generated when the 
			 USART6 transmit data register is empty */
		/* @arg USART_IT_TXE:  Transmit Data Register empty interrupt */
		USART_ITConfig(USART6, USART_IT_TXE, ENABLE);
		
		/* Wait until USART6 send the TxBuffer */
		while(ubTxCounter < ubNbrOfDataToTransfer)
		{}
		
		/* The software must wait until TC=1. The TC flag remains cleared during all data
			 transfers and it is set by hardware at the last frame?s end of transmission*/
		while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET)
		{}
	 
		/* Enable the USART6 Receive interrupt: this interrupt is generated when the 
			 USART6 receive data register is not empty */
		/* @arg USART_IT_RXNE: Receive Data register not empty interrupt */
		USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
		
		/* Wait until USART6 receive the RxBuffer */
		while(uhRxCounter < ubNbrOfDataToRead)
		{}
			
	} while (0);

  /* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory. 
     You can monitor PG6 or PG8 on the scope to measure the output signal. 
     If you need to fine tune this frequency, you can add more GPIO set/reset 
     cycles to minimize more the infinite loop timing.
     This code needs to be compiled with high speed optimization option.  */  
     
  /* Infinite loop */
	while (0)
	{
		// GPIO_ToggleBits(GPIOD, LED2_PIN);
		GPIO_SetBits(GPIOD, LED2_PIN);			// ORANGE LED ON
		Delay(1000);
	}
	
	while (0)
	{
		GPIO_ResetBits(GPIOD, LED2_PIN);		// ORANGE LED OFF
		Delay(1000);
	}
	
	while (1)
	{
		
		GPIO_ToggleBits(GPIOD, LED2_PIN);		// ORANGE LED OFF
		Delay(1000);
	}
	
  while (1)
  {
		if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8)) {
			GPIOD->BSRR = (uint32_t)(LED1_PIN);		// LED ON
			Delay(1);
		} else {
			GPIOD->BSRR = (uint32_t)((LED1_PIN) << 16);	// LED OFF
			Delay(1);
		}
		
		if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_9)) {
			GPIOD->BSRR = (uint32_t)(LED2_PIN );
			Delay(1);
		} else {
			GPIOD->BSRR = (uint32_t)((LED2_PIN) << 16);
			Delay(1);
		}
		
		if (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10)) {
			GPIOD->BSRR = (uint32_t)(LED3_PIN);
			Delay(1);
		} else {
			GPIOD->BSRR = (uint32_t)((LED3_PIN) << 16);
			Delay(1);
		}
  }
}


/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
static void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Configure the Priority Group to 2 bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	 /* Enable the TIM7 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
}

/**
  * @brief  Configures the TIM IRQ Handler.
  * @param  None
  * @retval None
  */
void TIM_Config(void)
{

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_ClocksTypeDef RCC_Clocks;
	uint16_t TIM_PrescalerValue = 0;
	uint32_t APB1_presc_res = 0;
	uint32_t TIM7_CLK = 0;
	
  /* TIM7 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

	/* */
	RCC_GetClocksFreq(&RCC_Clocks);
	APB1_presc_res = RCC->CFGR & RCC_CFGR_PPRE1;
	if( (APB1_presc_res >> 2) & 0x01)
	{
		TIM7_CLK = RCC_Clocks.PCLK1_Frequency * 2;
	}
	else
	{
		TIM7_CLK = RCC_Clocks.PCLK1_Frequency;
	}
	
  /* Compute the prescaler value */
  TIM_PrescalerValue = (uint16_t)(TIM7_CLK/1000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 1;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	
  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM7, TIM_PrescalerValue, TIM_PSCReloadMode_Immediate);
	
	/* TIM Interrupts enable */
  TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	
	/* TIM7 enable counter */
  TIM_Cmd(TIM7, ENABLE);

  while (0);
}

/**
  * @brief  Configures the GPIO Peripheral.
  * @param  None
  * @retval None
  */
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  /* GPIOD Peripheral clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PG6 and PG8 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	memset(&GPIO_InitStructure, 0, sizeof(GPIO_InitStructure));
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	/* 														INPUT_HS16 		INPUT_HS15 	INPUT_HS14 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	while (0);
}


/**
  * @brief  Configures the USART Peripheral.
  * @param  None
  * @retval None
  */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  
	/* Enable UART clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	
	/* Enable GPIO clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	/* Connect PXx to USARTx_Tx*/
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
	
	/* Connect PXx to USARTx_Rx*/
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
	
	/* Configure USART Tx as alternate function  */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	/* Configure USART Rx as alternate function  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	 /* Enable the USART OverSampling by 8 */
  USART_OverSampling8Cmd(USART6, ENABLE);
	
	/* USARTx configuration ------------------------------------------------------*/
		/* USARTx configured as follows:
					- BaudRate = 5250000 baud
				 - Maximum BaudRate that can be achieved when using the Oversampling by 8
					 is: (USART APB Clock / 8) 
				 Example: 
						- (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
						- (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
				 - Maximum BaudRate that can be achieved when using the Oversampling by 16
					 is: (USART APB Clock / 16) 
				 Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
				 Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
					- Word Length = 8 Bits
					- one Stop Bit
					- No parity
					- Hardware flow control disabled (RTS and CTS signals)
					- Receive and transmit enabled
		*/ 
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	/* USART configuration */
  USART_Init(USART6, &USART_InitStructure);
	
	/* Enable USART */
  USART_Cmd(USART6, ENABLE);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
	uint64_t ulStopDelay = get_TickCount()+ nTime;

  while(get_TickCount() < ulStopDelay);
}


/**
  * @brief  Increments the Timingcount variable.
  * @param  None
  * @retval None
  */
void TickCount_Increment(void)
{
		TickCount++;
}

/**
  * @brief  .
  * @param  None
  * @retval None
  */
uint64_t get_TickCount(void)
{
		return TickCount;
}

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}


/**
  * @}
  */


