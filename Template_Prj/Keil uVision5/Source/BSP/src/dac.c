/**
  ******************************************************************************
  * @file    dac.c
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
#define __DAC_C__


/* Includes ------------------------------------------------------------------*/
#include "dac.h"
#include "sys.h"
#include "math.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
DAC_InitTypeDef  DAC_InitStructure;
#define Dot_X 100                                                               //  这个参数决定生成数组的大小，程序运行过程中不可以改变


/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
#define DAC_DHR12R2_ADDRESS    0x40007414
#define DAC_DHR8R1_ADDRESS     0x40007410
uint16_t aSine12bit[Dot_X] =
{
0
};
const uint8_t aEscalator8bit[6] = {0x0, 0x33, 0x66, 0x99, 0xCC, 0xFF};

/**
  * @brief
  * @param  None
  * @retval None
  */
void MX_CLK_Init()
{

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
}


/**
  * @brief
  * @param  None
  * @retval None
  */
void DAC_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/**
  * @brief
  * @param  None
  * @retval None
  */
void DAC_Ch2_SineWaveConfig(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    /* DAC channel2 Configuration */
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_2, &DAC_InitStructure);

    /* DMA1_Stream6 channel7 configuration **************************************/
    DMA_DeInit(DMA1_Stream6);
    DMA_InitStructure.DMA_Channel = DMA_Channel_7;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)DAC_DHR12R2_ADDRESS;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&aSine12bit;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_BufferSize = Dot_X;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA1_Stream6, &DMA_InitStructure);

    /* Enable DMA1_Stream6 */
    DMA_Cmd(DMA1_Stream6, ENABLE);

    /* Enable DAC Channel2 */
    DAC_Cmd(DAC_Channel_2, ENABLE);

    /* Enable DMA for DAC Channel2 */
    DAC_DMACmd(DAC_Channel_2, ENABLE);
}


/**
  * @brief  梯形波
  * @param  None
  * @retval None
  */
void DAC_Ch1_EscalatorConfig(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    /* DAC channel1 Configuration */
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);

    /* DMA1_Stream5 channel7 configuration **************************************/
    DMA_DeInit(DMA1_Stream5);
    DMA_InitStructure.DMA_Channel = DMA_Channel_7;
    DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR8R1_ADDRESS;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&aEscalator8bit;
    DMA_InitStructure.DMA_BufferSize = 6;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA1_Stream5, &DMA_InitStructure);

    /* Enable DMA1_Stream5 */
    DMA_Cmd(DMA1_Stream5, ENABLE);

    /* Enable DAC Channel1 */
    DAC_Cmd(DAC_Channel_1, ENABLE);

    /* Enable DMA for DAC Channel1 */
    DAC_DMACmd(DAC_Channel_1, ENABLE);
}


/**
  * @brief  三角波
  * @param  None
  * @retval None
  */
void DAC_Ch2_TriangleConfig(void)
{
    /* DAC channel2 Configuration */
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1023;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_2, &DAC_InitStructure);

    /* Enable DAC Channel2 */
    DAC_Cmd(DAC_Channel_2, ENABLE);

    /* Set DAC channel2 DHR12RD register */
    DAC_SetChannel2Data(DAC_Align_12b_R, 0x100);
}


/**
  * @brief
  * @param  None
  * @retval None
  */
void DAC_Ch1_NoiseConfig(void)
{
    /* DAC channel1 Configuration */
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Noise;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits10_0;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);

    /* Enable DAC Channel1 */
    DAC_Cmd(DAC_Channel_1, ENABLE);

    /* Set DAC Channel1 DHR12L register */
    DAC_SetChannel1Data(DAC_Align_12b_L, 0x7FF0);
}

/**
  * @brief
  * @param  None
  * @retval None
  */
void Generate_Wave(uint8_t Wave_Mode,short Votage_Max,uint16_t Wave[])                    // 第一个参数是波形种类，第二个是波形的电压峰值  第三个是波形参数的保存位置
{                                                                               // 这里的Voltage_Max 一般是4095  也就是DAC转换的最大电压  Vref
		short i = 0;
		float temp;
		short temp2;
		switch(Wave_Mode)
		{
			case Wave_Sin: //  Sin 的 波形	
			{// 对下列算法进行了优化  注释掉的是未优化的
				temp = 2*3.14159/Dot_X;//  周期是2*Pi
				for(i = 0 ; i< Dot_X;i++)
				{
					//Wave[i] = 2048*(sin(2*3.14159*i/Dot_X)+1);
					Wave[i] = 0.5*Votage_Max*(sin(temp * i) + 1 );//直流信号需要向上一个的偏置
				}
				break;
			}
			case Wave_Triangular://  三角波
			{
				if(Dot_X%2) // 奇数
					temp2 = Dot_X/2 + 1;
				else        // 偶数
					temp2 = Dot_X/2;
				for(i = 0 ; i< temp2;i++)
				{
					Wave[i] = i*Votage_Max/temp2; 
				}
				for(i = temp2 ; i< Dot_X;i++)
				{
					Wave[i] =Votage_Max - Votage_Max*(i -temp2) /temp2; 
				}
				break;
			}
			case Wave_Sawtooth://   锯齿波
			{
				for(i = 0 ; i< Dot_X;i++)
				{
					Wave[i] = Votage_Max*i/Dot_X; 
				}
				break;
			}
		}
}


//DAC通道1输出初始化
void Dac1_Init(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;
 DAC_InitTypeDef DAC_InitType;

 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//使能GPIOA时钟
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);//使能DAC时钟

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
 GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AN;//模拟输入
 GPIO_InitStructure.GPIO_PuPd =GPIO_PuPd_DOWN;//下拉
 GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化

DAC_InitType.DAC_Trigger=DAC_Trigger_None;//不使用触发功能 TEN1=0
DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable; //DAC1输出缓存关闭BOFF1=1
DAC_Init(DAC_Channel_1,&DAC_InitType); //初始化DAC通道1

 DAC_Cmd(DAC_Channel_1, ENABLE); //使能DAC通道1
 DAC_SetChannel1Data(DAC_Align_12b_R, 0);//12位右对齐数据格式设置DAC值
}
//设置通道1输出电压
//vol:0~3300,代表0~3.3V
void Dac1_Set_Vol(uint16_t vol)
{
 double temp=vol;
 temp/=1000;
 temp=temp*4096/3.3;
DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12位右对齐数据格式设置DAC值
}
/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/
