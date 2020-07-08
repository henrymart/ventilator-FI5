/**
  ******************************************************************************
  * @file    Templates/stm32f7xx_it.c 
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
// IIT-ICUB-TECH-CUSTOMIZATION
#if defined(USE_STM32HAL)
// marco.accame@iit.it: forcing the use of the include we need 
#include "stm32hal.h"
#else
#include "stm32f7xx_hal.h"
#endif

/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M7 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
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
//void SVC_Handler(void)
//{
//}

///**
//  * @brief  This function handles Debug Monitor exception.
//  * @param  None
//  * @retval None
//  */
//void DebugMon_Handler(void)
//{
//}

///**
//  * @brief  This function handles PendSVC exception.
//  * @param  None
//  * @retval None
//  */
//void PendSV_Handler(void)
//{
//}

///**
//  * @brief  This function handles SysTick Handler.
//  * @param  None
//  * @retval None
//  */
//void SysTick_Handler(void)
//{
//  HAL_IncTick();
//}
  

/******************************************************************************/
/*                 STM32F7xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f7xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */ 

/**
  * @}
  */
  
  
//#if defined(APP_HMI_disable)
//#else
//#include "stm32746g_discovery.h"
//#include "ewrte.h"
//#include "ew_bsp_clock.h"
//#include "ew_bsp_inout.h"
//void EXTI15_10_IRQHandler( void )
//{
//    // from edl:
//    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
//    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);  
//
//    // from ew
//    HAL_GPIO_EXTI_IRQHandler( KEY_BUTTON_PIN );
//    EwBspInOutEventHandler( KEY_BUTTON_PIN );
//}
//#endif

// - EDL_DRIVER_CODE 
// - the irqhandlers for i2c1 I2C1_EV_IRQHandler() and I2C1_ER_IRQHandler() are in the .lib
// - the EXTI15_10_IRQHandler(0 is in the .lib i have removed teh call to manage KEY_BUTTON_PIN but that is not important for us
// - the HAL_I2C_MasterRxCpltCallback() and HAL_I2C_MasterTxCpltCallback() and HAL_I2C_ErrorCallback() are in int_handlers.c

// - EDL_DRIVER_CODE 
// - other irqhandlers xxxxxxxxxx are in the .lib
// - the HAL_GPIO_EXTI_Callback() is in int_handlers.c


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
