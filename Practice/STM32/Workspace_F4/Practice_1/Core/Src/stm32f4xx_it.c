/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.1
  * @date    27-January-2022
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32f4xx_it.h"
#include "main.h"
#include "port.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

extern uint8_t aTxBuffer[];
extern uint8_t aRxBuffer[];
extern uint8_t ubNbrOfDataToTransfer;
extern uint8_t ubNbrOfDataToRead;
extern __IO uint8_t ubTxCounter; 
extern __IO uint16_t uhRxCounter;

/* Private function prototypes -----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void TickCount_Increment(void);


/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
	vPortSVCHandler();
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
	xPortPendSVHandler();
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  xPortSysTickHandler();
}


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
void PPP_IRQHandler(void)
{
	
}


/**
  * @brief  This function handles TIM3 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM7_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

		TickCount_Increment();
		
		while(0);
  }
}


/**
  * @brief  This function handles USARTx global interrupt request.
  * @param  None
  * @retval None
  */
void USART6_IRQHandler(void)
{
	/* @arg USART_FLAG_RXNE: Receive data register not empty flag */
  if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)	
  {
    /* Read one byte from the receive data register */
    aRxBuffer[uhRxCounter++] = (uint8_t)(USART_ReceiveData(USART6) & 0xFF);
//		aRxBuffer[uhRxCounter++] = USART_ReceiveData(USART6);
		USART_SendData(USART6, aRxBuffer[uhRxCounter-1]);

    if(uhRxCounter == ubNbrOfDataToRead)
    {
      /* Disable the USART6 Receive interrupt */
      USART_ITConfig(USART6, USART_IT_RXNE, DISABLE);
    }
  }

	/* @arg USART_FLAG_TXE:  Transmit data register empty flag */
  if(USART_GetITStatus(USART6, USART_IT_TXE) != RESET)
  {   
    /* Write one byte to the transmit data register */
    USART_SendData(USART6, aTxBuffer[ubTxCounter++]);

    if(ubTxCounter == ubNbrOfDataToTransfer)
    {
      /* Disable the USART6 Transmit interrupt */
      USART_ITConfig(USART6, USART_IT_TXE, DISABLE);
    }
  }
}


/**
  * @}
  */ 



