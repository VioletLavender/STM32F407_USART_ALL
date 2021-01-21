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

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);                       //ʹ��GPIOAʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);                       //ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);                        //ʹ��ADCʱ��
    bsp_InitAdcDMA();

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;                              /*ģ������*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;                                 /*ͨ��3*/
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;                           /*����������*/
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                      /*��ʼ��*/

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;                              /*ģ������*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;                                 /*ͨ��3*/
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;                           /*����������*/
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                      /*��ʼ��*/

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;                              /*ģ������*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;                                 /*ͨ��3*/
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;                           /*����������*/
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                      /*��ʼ��*/

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;                              /*ģ������*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;                                 /*ͨ��3*/
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;                           /*����������*/
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                      /*��ʼ��*/

    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;     /*DMAʧ��*/
    ADC_CommonInitStructure.ADC_Mode          = ADC_Mode_Independent;           /*����ģʽ*/
    ADC_CommonInitStructure.ADC_Prescaler     = ADC_Prescaler_Div4;             /*APB2��4��Ƶ ��84/4=21M*/
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;/*���������׶ε���ʱ5��ʱ��*/
    ADC_CommonInit(&ADC_CommonInitStructure);                                   /*��ʼ��*/

    /*��ʼ��ADC1*/
    ADC_InitStructure.ADC_Resolution  = ADC_Resolution_12b;                     /*12λģʽ*/
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;                                /*ɨ��ģʽ*/
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                          /*����ת��*/
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; /*��ֹ������� ʹ���������*/
    ADC_InitStructure.ADC_DataAlign    = ADC_DataAlign_Right;                   /*�Ҷ���*/
    ADC_InitStructure.ADC_NbrOfConversion = 4;                                  /*4ͨ�� 1*/
    ADC_Init(ADC1, &ADC_InitStructure);                                         /*��ʼ��*/

    ADC_Cmd(ADC1, ENABLE);                                                      /*����ת��*/
    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 3, ADC_SampleTime_480Cycles); /*���ù���ͨ��4 1������ ����ʱ�� */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 4, ADC_SampleTime_480Cycles); /*���ù���ͨ��5 2������ ����ʱ�� */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_480Cycles); /*���ù���ͨ��6 3������ ����ʱ�� */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_480Cycles); /*���ù���ͨ��7 4������ ����ʱ�� */

    ADC_SoftwareStartConv(ADC1);                                                /*�������ת��*/
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);                           //Դ���ݱ仯ʱ����DMA����
    ADC_DMACmd(ADC1, ENABLE);                                                   //ʹ��ADC����
}


/**
  * @brief
  * @param  None
  * @retval None
  */
void bsp_InitAdcDMA(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);                        /*DMA2��ʱ��ʹ��*/
    while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE);                           /*�ȴ�DMA��������*/


    DMA_InitStructure.DMA_Channel = DMA_Channel_0;                              /*DMAͨ��0*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_BASE + 0x4C;      /*�����ַ*/
    DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)AdcValue;              /*��ȡ����ַ*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;                     /*��������赽�ڴ�*/
    DMA_InitStructure.DMA_BufferSize = 4;                                       /*���ݴ��������Ϊ1*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            /*��ַ������*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                     /*��ַ����*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; /*���ݳ��Ȱ���*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         /*���ݳ��Ȱ���*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                         /*�����ȼ�*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                             /*ѭ��ģʽ*/
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;                      /*��ֹFIFO*/
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;           /*FIFO��ֵ*/
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;                 /*���δ���*/
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;         /*���δ���*/
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);                                 /**/
    DMA_Cmd(DMA2_Stream0, ENABLE);                                              //����DMA����
}

void Get_Adc(void)
{
    if(DMA_GetFlagStatus(DMA2_Stream0, DMA_FLAG_TCIF0) != RESET)                /*�������*/
    {
//        printf("adc6=%d  ", AdcValue[0]);
//        printf("adc7=%d  ", AdcValue[1]);
//        printf("adc4=%d  ", AdcValue[2]);
//        printf("adc5=%d  ", AdcValue[3]);
//        printf("\r\n");
        DMA_ClearFlag(DMA2_Stream0, DMA_FLAG_TCIF0);                            /*����*/
    }
}


/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/
