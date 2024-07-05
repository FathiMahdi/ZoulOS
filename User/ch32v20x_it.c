/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v20x_it.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/12/29
 * Description        : Main Interrupt Service Routines.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "ch32v20x_it.h"
#include <stdint.h>
#include <stdio.h>
void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));



volatile uint8_t FatFsCnt = 0;
volatile uint16_t Timer1,Timer2;

void SDTimer_Handler(void)
{
  if(Timer1>0)
  {
    Timer1--;
  }

  if(Timer2>0)
  {
    Timer2--;
  }
}



/*********************************************************************
 * @fn      NMI_Handler
 *
 * @brief   This function handles NMI exception.
 *
 * @return  none
 */
void NMI_Handler(void)
{
  printf("Non maskable Interrupt Error!\r\n");
  NVIC_SystemReset();
  while (1)
  {
  }
}

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   This function handles Hard Fault exception.
 *
 * @return  none
 */
void HardFault_Handler(void)
{
  printf("Hardfault error!\r\n");
  NVIC_SystemReset();
  while (1)
  {
  }
}


//void SysTick_Handler(void)
//{
//
//  FatFsCnt++;
//  if (FatFsCnt>=10)
//  {
//    FatFsCnt = 0;
//    SDTimer_Handler();
//  }
//
//}
