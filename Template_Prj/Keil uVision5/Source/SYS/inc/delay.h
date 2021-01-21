/**
  ******************************************************************************
  * @file    delay.h
  * @author  
  * @version V1.00
  * @date    22-Sep-2020
  * @brief   ......
  ******************************************************************************
  * @attention
  *
  * ......
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H 	

#ifdef __cplusplus
extern "C" {
#endif


#undef EXTERN


#ifdef  __DELAY_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes ------------------------------------------------------------------*/
#include <sys.h>	
#include "stm32f4xx.h"	


/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/ 	 
EXTERN void delay_init(u8 SYSCLK);
EXTERN void delay_ms(u16 nms);
EXTERN void delay_us(u32 nus);


#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/
