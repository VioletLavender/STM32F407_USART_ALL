/**
  ******************************************************************************
  * @file    usart.c
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
#define __USART_C__


/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "usart.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
u8 USART_RX_BUF[USART_REC_LEN];                                                 //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART_RX_STA = 0;                                                           //����״̬���
u8 USART2_RX_BUF[USART2_REC_LEN];                                               //���ջ��壬���USART_REC_LEN���ֽڣ�ĩ�ֽ�Ϊ���з�
u16 USART2_RX_STA = 0;                                                          //����״̬���
u8 USART3_RX_BUF[USART3_REC_LEN];                                               //���ջ��壬���USART_REC_LEN���ֽڣ�ĩ�ֽ�Ϊ���з�
u16 USART3_RX_STA = 0;                                                          //����״̬���
/**
  * @brief
  * @param  None
  * @retval None
  */
//int fputc(int ch, FILE *f)
//{
//    while((USART1->SR & 0X40) == 0);                                            //ѭ������,ֱ���������

//    USART1->DR = (u8) ch;
//    return ch;
//}

//int fputc(int ch, FILE *f)
//{
//    while((USART2->SR & 0X40) == 0);                                            //ѭ������,ֱ���������

//    USART2->DR = (u8) ch;
//    return ch;
//}
int fputc(int ch, FILE *f)
{
    while((USART3->SR & 0X40) == 0);                                            //ѭ������,ֱ���������

    USART3->DR = (u8) ch;
    return ch;
}


/**
  * @brief
  * @param  None
  * @retval None
  */
void uart1_init(u32 bound)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);

}
/**
  * @brief
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)                                                    //����2�жϷ������
{
    u8 Res;

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)                       //�����жϣ����յ������ݱ�����0x0d  0x0a��β��
    {
        Res = USART_ReceiveData(USART1); //(USART1->DR);                        //��ȡ���յ�������

        if((USART_RX_STA & 0x8000) == 0)                                       //����δ���
        {
            if(USART_RX_STA & 0x4000)                                          //���յ���0x0d
            {
                if(Res != 0x0a)USART_RX_STA = 0;                               //���մ������¿�ʼ
                else USART_RX_STA |= 0x8000;                                   //���������
            }
            else                                                                //û�յ�0X0D
            {
                if(Res == 0x0d)USART_RX_STA |= 0x4000;
                else
                {
                    USART_RX_BUF[USART_RX_STA & 0X3FFF] = Res ;
                    USART_RX_STA++;

                    if(USART_RX_STA > (USART_REC_LEN - 1))USART_RX_STA = 0;  //�������ݴ������¿�ʼ����
                }
            }
        }
    }
}


/**
  * @brief
  * @param  None
  * @retval None
  */
void uart2_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);                       //ʹ��GPIOAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);                      //ʹ�ܴ���2ʱ�ӣ�����1ΪAPB2

    //����2��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;                      //PA2��PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                //���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                           //�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                              //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                                //����
    GPIO_Init(GPIOD, &GPIO_InitStructure);                                      //��ʼ��

    //����2��ʼ������
    USART_InitStructure.USART_BaudRate = bound;                                 //����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                 //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                      //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;                         //����żЧ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;             //�շ�ģʽ
    USART_Init(USART2, &USART_InitStructure);                                   //��ʼ������2

    //����2 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;                           //����2�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;                   //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;                          //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);                                             //����ָ���Ĳ�����ʼ��VIC�Ĵ���

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                              //��������ж�
    USART_Cmd(USART2, ENABLE);                                                  //ʹ�ܴ���1
}


/**
  * @brief
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)                                                    //����2�жϷ������
{
    u8 Res;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)                       //�����жϣ����յ������ݱ�����0x0d  0x0a��β��
    {
        Res = USART_ReceiveData(USART2); //(USART1->DR);                        //��ȡ���յ�������

        if((USART2_RX_STA & 0x8000) == 0)                                       //����δ���
        {
            if(USART2_RX_STA & 0x4000)                                          //���յ���0x0d
            {
                if(Res != 0x0a)USART2_RX_STA = 0;                               //���մ������¿�ʼ
                else USART2_RX_STA |= 0x8000;                                   //���������
            }
            else                                                                //û�յ�0X0D
            {
                if(Res == 0x0d)USART2_RX_STA |= 0x4000;
                else
                {
                    USART2_RX_BUF[USART2_RX_STA & 0X3FFF] = Res ;
                    USART2_RX_STA++;

                    if(USART2_RX_STA > (USART2_REC_LEN - 1))USART2_RX_STA = 0;  //�������ݴ������¿�ʼ����
                }
            }
        }
    }
}


/**
  * @brief
  * @param  None
  * @retval None
  */
void uart3_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);                       //ʹ��GPIOAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);                      //ʹ�ܴ���2ʱ�ӣ�����1ΪAPB2

    //����2��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;                    //PA2��PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                //���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                           //�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                              //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                                //����
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                      //��ʼ��

    //����2��ʼ������
    USART_InitStructure.USART_BaudRate = bound;                                 //����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                 //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                      //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;                         //����żЧ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;             //�շ�ģʽ
    USART_Init(USART3, &USART_InitStructure);                                   //��ʼ������2

    //����2 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;                           //����2�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;                   //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;                          //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);                                             //����ָ���Ĳ�����ʼ��VIC�Ĵ���

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);                              //��������ж�
    USART_Cmd(USART3, ENABLE);                                                  //ʹ�ܴ���1
}
/**
  * @brief
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)                                                    //����2�жϷ������
{
    u8 Res;

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)                       //�����жϣ����յ������ݱ�����0x0d  0x0a��β��
    {
        Res = USART_ReceiveData(USART3); //(USART1->DR);                        //��ȡ���յ�������

        if((USART3_RX_STA & 0x8000) == 0)                                       //����δ���
        {
            if(USART3_RX_STA & 0x4000)                                          //���յ���0x0d
            {
                if(Res != 0x0a)USART3_RX_STA = 0;                               //���մ������¿�ʼ
                else USART3_RX_STA |= 0x8000;                                   //���������
            }
            else                                                                //û�յ�0X0D
            {
                if(Res == 0x0d)USART3_RX_STA |= 0x4000;
                else
                {
                    USART3_RX_BUF[USART3_RX_STA & 0X3FFF] = Res ;
                    USART3_RX_STA++;

                    if(USART3_RX_STA > (USART3_REC_LEN - 1))USART3_RX_STA = 0;  //�������ݴ������¿�ʼ����
                }
            }
        }
    }
}



void USART3_Send_Byte(u8 dat)
{
    USART_SendData(USART3, dat);
    while(!USART_GetFlagStatus(USART3, USART_FLAG_TXE));
}


void USART3_Send_Group(u8 *buf, u16 len)
{
    while(len--)
    {
        USART3_Send_Byte(*buf++);
    }
}

/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/
