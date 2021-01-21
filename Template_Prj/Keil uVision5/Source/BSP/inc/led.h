/**
  ******************************************************************************
  * @file    led.h
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
#ifndef __LED_H
#define __LED_H	 


#ifdef __cplusplus
extern "C" {
#endif


#undef EXTERN


#ifdef  __LED_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes ------------------------------------------------------------------*/
#include "sys.h"


/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 

EXTERN void LED_Init(void);//≥ı ºªØ		 				    


#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/
