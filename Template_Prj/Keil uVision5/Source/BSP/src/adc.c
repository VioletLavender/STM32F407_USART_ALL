/**
  ******************************************************************************
  * @file    adc.c
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
#define __ADC_C__


/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "delay.h"
#include "usart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/

__IO uint16_t AdcValue[4] = {0};
EXTERN void bsp_InitAdcDMA(void);

/**
  * @brief
  * @param  None
  * @retval None
  */
void bsp_InitAdc(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);                       //使能GPIOA时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);                       //使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);                        //使能ADC时钟
    bsp_InitAdcDMA();

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;                              /*模拟输入*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;                                 /*通道3*/
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;                           /*不带上下拉*/
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                      /*初始化*/

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;                              /*模拟输入*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;                                 /*通道3*/
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;                           /*不带上下拉*/
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                      /*初始化*/

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;                              /*模拟输入*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;                                 /*通道3*/
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;                           /*不带上下拉*/
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                      /*初始化*/

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;                              /*模拟输入*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;                                 /*通道3*/
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;                           /*不带上下拉*/
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                      /*初始化*/

    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;     /*DMA失能*/
    ADC_CommonInitStructure.ADC_Mode          = ADC_Mode_Independent;           /*独立模式*/
    ADC_CommonInitStructure.ADC_Prescaler     = ADC_Prescaler_Div4;             /*APB2的4分频 即84/4=21M*/
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;/*两个采样阶段的延时5个时钟*/
    ADC_CommonInit(&ADC_CommonInitStructure);                                   /*初始化*/

    /*初始化ADC1*/
    ADC_InitStructure.ADC_Resolution  = ADC_Resolution_12b;                     /*12位模式*/
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;                                /*扫描模式*/
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                          /*连续转换*/
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; /*禁止触发检测 使用软件触发*/
    ADC_InitStructure.ADC_DataAlign    = ADC_DataAlign_Right;                   /*右对齐*/
    ADC_InitStructure.ADC_NbrOfConversion = 4;                                  /*4通道 1*/
    ADC_Init(ADC1, &ADC_InitStructure);                                         /*初始化*/

    ADC_Cmd(ADC1, ENABLE);                                                      /*开启转换*/
    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 3, ADC_SampleTime_480Cycles); /*设置规则通道4 1个序列 采样时间 */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 4, ADC_SampleTime_480Cycles); /*设置规则通道5 2个序列 采样时间 */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_480Cycles); /*设置规则通道6 3个序列 采样时间 */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_480Cycles); /*设置规则通道7 4个序列 采样时间 */

    ADC_SoftwareStartConv(ADC1);                                                /*启动软件转换*/
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);                           //源数据变化时开启DMA传输
    ADC_DMACmd(ADC1, ENABLE);                                                   //使能ADC传输
}


/**
  * @brief
  * @param  None
  * @retval None
  */
void bsp_InitAdcDMA(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);                        /*DMA2的时钟使能*/
    while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE);                           /*等待DMA可以配置*/


    DMA_InitStructure.DMA_Channel = DMA_Channel_0;                              /*DMA通道0*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_BASE + 0x4C;      /*外设地址*/
    DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)AdcValue;              /*存取器地址*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;                     /*方向从外设到内存*/
    DMA_InitStructure.DMA_BufferSize = 4;                                       /*数据传输的数量为1*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            /*地址不增加*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                     /*地址增加*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; /*数据长度半字*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         /*数据长度半字*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                         /*高优先级*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                             /*循环模式*/
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;                      /*禁止FIFO*/
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;           /*FIFO的值*/
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;                 /*单次传输*/
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;         /*单次传输*/
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);                                 /**/
    DMA_Cmd(DMA2_Stream0, ENABLE);                                              //开启DMA传输
}

void Get_Adc(void)
{
    if(DMA_GetFlagStatus(DMA2_Stream0, DMA_FLAG_TCIF0) != RESET)                /*传输完成*/
    {
//        printf("adc6=%d  ", AdcValue[0]);
//        printf("adc7=%d  ", AdcValue[1]);
//        printf("adc4=%d  ", AdcValue[2]);
//        printf("adc5=%d  ", AdcValue[3]);
//        printf("\r\n");
        DMA_ClearFlag(DMA2_Stream0, DMA_FLAG_TCIF0);                            /*清零*/
    }
}


/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/
