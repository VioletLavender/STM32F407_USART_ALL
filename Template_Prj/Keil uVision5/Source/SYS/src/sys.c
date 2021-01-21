/**
  ******************************************************************************
  * @file    sys.c
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
#define __SYS_C__


/* Includes ------------------------------------------------------------------*/
#include "sys.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/


/**
  * @brief
  * @param  None
  * @retval None
  */
__asm void WFI_SET(void)
{
    WFI;
}


/**
  * @brief
  * @param  None
  * @retval None
  */
__asm void INTX_DISABLE(void)
{
    CPSID   I
    BX      LR
}


/**
  * @brief
  * @param  None
  * @retval None
  */
__asm void INTX_ENABLE(void)
{
    CPSIE   I
    BX      LR
}


/**
  * @brief
  * @param  None
  * @retval None
  */
__asm void MSR_MSP(u32 addr)
{
    MSR MSP, r0             //set Main Stack value
    BX r14
}



/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/
