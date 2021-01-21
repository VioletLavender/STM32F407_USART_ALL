/**
  ******************************************************************************
  * @file    usart.h
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
#ifndef __USART_H
#define __USART_H


#ifdef __cplusplus
extern "C" {
#endif


#undef EXTERN


#ifdef  __USART_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes ------------------------------------------------------------------*/
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 


/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define USART2_REC_LEN              200                                         //定义最大接收字节数 200
#define USART3_REC_LEN              200                                         //定义最大接收字节数 200

EXTERN u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
EXTERN u16 USART_RX_STA;         		//接收状态标记

EXTERN void uart1_init(u32 bound);
EXTERN void uart2_init(u32 bound);
EXTERN void uart3_init(u32 bound);
EXTERN void USART3_Send_Group(u8 *buf, u16 len);


#ifdef __cplusplus
}
#endif


#endif



/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/
