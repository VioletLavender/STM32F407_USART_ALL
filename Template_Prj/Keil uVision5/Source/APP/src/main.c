/**
  ******************************************************************************
  * @file    main.c
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
#define __MAIN_C__


/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/

u8 buf[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
uint8_t I = 0;
/**
  * @brief
  * @param  None
  * @retval None
  */
int main(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     //设置系统中断优先级分组2

    delay_init(168);                                    //延时初始化

    LED_Init();

    bsp_InitAdc();

    uart3_init(115200);

    USART3_Send_Group(buf,20);

    while(1)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_15);
        delay_ms(2);
        GPIO_ResetBits(GPIOA, GPIO_Pin_15);
        delay_ms(2);
        Get_Adc();
    }
}


/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/
