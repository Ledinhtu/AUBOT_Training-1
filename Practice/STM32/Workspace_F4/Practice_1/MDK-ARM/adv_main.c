/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/adv_main.c 
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

/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

GPIO_InitTypeDef GPIO_InitStructure;
RCC_ClocksTypeDef RCC_ClockFreq;

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int adv_main(void)
{
  
 
 /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files before to branch to application main.
       To reconfigure the default setting of SystemInit() function, 
       refer to system_stm32f4xx.c file */

	/* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
//  SetSysClock();
	
	 /* This function fills the RCC_ClockFreq structure with the current
  frequencies of different on chip clocks (for debug purpose) */
  RCC_GetClocksFreq(&RCC_ClockFreq);
	
	/* Enable Clock Security System(CSS): this will generate an NMI exception
	when HSE clock fails */
  RCC_ClockSecuritySystemCmd(ENABLE);
	
	/* NVIC configuration ------------------------------------------------------*/
//  NVIC_Configuration();
	
	
	/* GPIOD Peripheral clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure LED1, LED2 and LED3 in output no pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	 while (1)
  {
	  /* Toggle LED */
	  GPIOC->ODR ^= LED1_PIN | LED2_PIN | LED3_PIN;

	  /* Insert a delay */
//	  Delay(1000);	// 1000 ms
  }



}


/**
  * @brief  Selects HSE as System clock source and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
void SetSysClockToHSE(void)
{
	ErrorStatus HSEStartUpStatus;
	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();
	
	/* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);
	
	/* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
	
	if (HSEStartUpStatus == SUCCESS)
  {
		/* Select regulator voltage output Scale 1 mode */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
		
		
		/* HCLK = SYSCLK / 1*/
		
		/* PCLK2 = HCLK / 2*/
		
		/* PCLK1 = HCLK / 4*/
		
		/* Configure the main PLL */
		
		/* Enable the main PLL */
		
		/* Wait till the main PLL is ready */
		
		/* Configure Flash prefetch, Instruction cache, Data cache and wait state */
		
		/* Select the main PLL as system clock source */
		
		/* Wait till the main PLL is used as system clock source */\
		
	}
	else
	{
		/* If HSE fails to start-up, the application will have wrong clock
		configuration. User can add here some code to deal with this error */
		
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


