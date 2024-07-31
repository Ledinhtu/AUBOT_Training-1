/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
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

/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define EXAMPLE_CODE
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
RCC_ClocksTypeDef RCC_ClockFreq;

#ifdef EXAMPLE_CODE
static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;
#endif /* EXAMPLE_CODE */

/* Private function prototypes -----------------------------------------------*/
static void Delay(__IO uint32_t nTime);

void NVIC_Configuration(void);
void SetSysClock(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  
 
 /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files before to branch to application main.
       To reconfigure the default setting of SystemInit() function, 
       refer to system_stm32f4xx.c file */

#ifdef MODIFY_CODE
	/* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
  SetSysClock();
	
	 /* This function fills the RCC_ClockFreq structure with the current
  frequencies of different on chip clocks (for debug purpose) */
  RCC_GetClocksFreq(&RCC_ClockFreq);
	
	/* Enable Clock Security System(CSS): this will generate an NMI exception
	when HSE clock fails */
  RCC_ClockSecuritySystemCmd(ENABLE);
	
	/* NVIC configuration ------------------------------------------------------*/
  NVIC_Configuration();
	
	
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
	  Delay(1000);	// 1000 ms
  }
#endif /* RCC_CODE */ 

	/**************************************************************************/
	/**************************************************************************/
#ifdef EXAMPLE_CODE

  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
  
  /* Add your application code here */
  /* Insert 50 ms delay */
  Delay(5);
  
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files (startup_stm32f40_41xxx.s/startup_stm32f427_437xx.s/startup_stm32f429_439xx.s)
       before to branch to application main. 
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */  

  /* GPIOD Peripheral clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PG6 and PG8 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory. 
     You can monitor PG6 or PG8 on the scope to measure the output signal. 
     If you need to fine tune this frequency, you can add more GPIO set/reset 
     cycles to minimize more the infinite loop timing.
     This code needs to be compiled with high speed optimization option.  */  
     
  /* Infinite loop */
  while (1)
  {
    /* Set PD_3 */
    GPIOD->BSRR = (uint32_t)(LED1_PIN | LED2_PIN | LED3_PIN);
		
		Delay(50);
		
    /* Reset PD_3 */
    GPIOD->BSRR = (uint32_t)((LED1_PIN | LED2_PIN | LED3_PIN) << 16);
		
		Delay(50);
  }
#endif /* MODIFY_CODE */

}


#ifdef EXAMPLE_CODE
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  uwTimingDelay = nTime;

  while(uwTimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  { 
    uwTimingDelay--;
  }
}
#endif /* EXAMPLE_CODE */

#ifdef MODIFY_CODE
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

#endif /* MODIFY_CODE */

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


