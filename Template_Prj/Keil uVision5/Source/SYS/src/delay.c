/**
  ******************************************************************************
  * @file    delay.c
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
#define __DELAY_C__


/* Includes ------------------------------------------------------------------*/
#include "delay.h"
#include "sys.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
static u8  fac_us = 0;                                      //us��ʱ������
static u16 fac_ms = 0;                                      //ms��ʱ������,��os��,����ÿ�����ĵ�ms��


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/


/**
  * @brief  //��ʼ���ӳٺ���,��ʹ��OS��ʱ��,�˺������ʼ��OS��ʱ�ӽ���,SYSTICK��ʱ�ӹ̶�ΪAHBʱ�ӵ�1/8,SYSCLK:ϵͳʱ��Ƶ��
  * @param  None
  * @retval None
  */
void delay_init(u8 SYSCLK)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SYSCLK / 8;
    fac_ms = (u16)fac_us * 1000;                            //ÿ��ms��Ҫ��systickʱ����
}


/**
  * @brief  nus��ֵ,��Ҫ����798915us(���ֵ��2^24/fac_us@fac_us=21)
  * @param  None
  * @retval None
  */
void delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us;                           //ʱ�����
    SysTick->VAL = 0x00;                                    //��ռ�����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;              //��ʼ����

    do
    {
        temp = SysTick->CTRL;
    }
    while ((temp & 0x01) && !(temp & (1 << 16)));           //�ȴ�ʱ�䵽��

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;              //�رռ�����
    SysTick->VAL = 0X00;                                    //��ռ�����
}


/**
  * @brief  ��168M������,nms<=798ms
  * @param  None
  * @retval None
  */
void delay_xms(u16 nms)
{
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms;                      //ʱ�����(SysTick->LOADΪ24bit)
    SysTick->VAL = 0x00;                                    //��ռ�����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;              //��ʼ����

    do
    {
        temp = SysTick->CTRL;
    }
    while ((temp & 0x01) && !(temp & (1 << 16)));           //�ȴ�ʱ�䵽��

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;              //�رռ�����
    SysTick->VAL = 0X00;                                    //��ռ�����
}


/**
  * @brief
  * @param  None
  * @retval None
  */
void delay_ms(u16 nms)
{
    u8 repeat = nms / 540;                                  //������540,�ǿ��ǵ�ĳЩ�ͻ����ܳ�Ƶʹ��,
    //���糬Ƶ��248M��ʱ��,delay_xms���ֻ����ʱ541ms������
    u16 remain = nms % 540;

    while (repeat)
    {
        delay_xms(540);
        repeat--;
    }

    if (remain)delay_xms(remain);
}


/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/
