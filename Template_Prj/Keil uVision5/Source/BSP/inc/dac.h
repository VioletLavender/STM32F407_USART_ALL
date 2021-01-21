/**
  ******************************************************************************
  * @file    dac.h
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
#ifndef __DAC_H
#define __DAC_H	 


#ifdef __cplusplus
extern "C" {
#endif


#undef EXTERN


#ifdef  __DAC_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes ------------------------------------------------------------------*/
#include "sys.h"

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define Wave_Sin         1 // ÕýÏÒ²¨
#define Wave_Triangular  2 // Èý½Ç²¨ 
#define Wave_Sawtooth    3 // ¾â³Ý²¨


EXTERN void DAC_Ch1_NoiseConfig(void);
EXTERN void DAC_Ch2_TriangleConfig(void);
EXTERN void DAC_Ch1_EscalatorConfig(void);
EXTERN void DAC_Ch2_SineWaveConfig(void);
EXTERN void DAC_GPIO_Config(void);
EXTERN void MX_CLK_Init(void);
EXTERN void Generate_Wave(uint8_t Wave_Mode,short Votage_Max,uint16_t Wave[]);
EXTERN void Dac1_Init(void);
EXTERN void Dac1_Set_Vol(uint16_t vol);
#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/
