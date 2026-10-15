#include "stm32f10x.h"
#include "Delay.h"

void Key_Init(void)
{
	// 释放调试引脚（必须加）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	
	// 初始化GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13 | GPIO_Pin_1 | GPIO_Pin_15 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}	

// 🔥 🔥 🔥 修复后的按键扫描（按一个直接返回，不会覆盖）
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum=0;
	
	// 先查 PB13
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0);
		Delay_ms(20);
		return 13;   // 直接返回！
	}
	
	// 再查 PB1
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
		Delay_ms(20);
		return 1;
	}
	
	// 再查 PB15
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0);
		Delay_ms(20);
		return 15;
	}
	
	// 再查 PB11
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
		Delay_ms(20);
		return 11;
	}
	
	// 再查 PB12
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0);
		Delay_ms(20);
		return 12;
	}
	
	// 最后查 PB14
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0);
		Delay_ms(20);
		return 14;
	}
	
	return KeyNum;
}

