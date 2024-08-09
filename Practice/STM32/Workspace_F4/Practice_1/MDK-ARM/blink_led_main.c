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

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static GPIO_InitTypeDef  GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
static void prvSetupHardware( void );
static void vTaskBlinkLED( void * pvParameters );
static void GPIO_Config(void);
static void vStartLEDTasks(void);

static void my_delay(uint32_t time);


/* Private functions ---------------------------------------------------------*/
void my_delay(uint32_t time) {
	uint64_t i = 0;
	while(time-- >0) {
		for(i = 0; i < 1000000; i++) {}
	}
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int blink_led_main(void)
{
 /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files before to branch to application main.
       To reconfigure the default setting of SystemInit() function, 
       refer to system_stm32f4xx.c file */

	
	/* Configure the hardware ready to run the test. */
	prvSetupHardware();
	
	/* Create the task, storing the handle. */
	vStartLEDTasks();
	
  /* Start the scheduler. */
  vTaskStartScheduler();
	
	while(1);
}


/**
  * @brief  Configures the GPIO Peripheral.
  * @param  None
  * @retval None
  */
void GPIO_Config(void)
{
	/* GPIOD Peripheral clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure LED1, LED2 and LED3 in output no pushpull mode */
  GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
}


/**
* @brief  Blink LED function.
  * @param  None
  * @retval None
  */
void vTaskBlinkLED( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
       pvParameters value in the call to xTaskCreate() below. */

    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

    for( ;; )
    {
       /* Task code goes here. */
			/* Toggle LED */
//			GPIOD->ODR ^= LED1_PIN | LED2_PIN | LED3_PIN;
			RED_LED_PORT->ODR ^= RED_LED_PIN;

			/* Insert a delay */
			// vTaskDelay(pdMS_TO_TICKS(10000));
			vTaskDelay( 10000 /  portTICK_PERIOD_MS );
    }
}

/**
  * @brief  Set up the hardware ready to run this demo.
  * @param  None
  * @retval None
  */
void prvSetupHardware( void )
{
	/* Setup the LED outputs. */
	GPIO_Config();
	
}

/**
  * @brief  Create Blink LED tasks.
  * @param  None
  * @retval None
  */
void vStartLEDTasks(void)
{
	xTaskCreate(	vTaskBlinkLED,		/* Function that implements the task. */
								"Blink_LED_Task",	/* Text name for the task. */
								configMINIMAL_STACK_SIZE,      			/* Stack size in words, not bytes. */
								( void * ) 1,    	/* Parameter passed into the task. */
								tskIDLE_PRIORITY,	/* Priority at which the task is created. */
								NULL );      	/* Used to pass out the created task's handle. */

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


