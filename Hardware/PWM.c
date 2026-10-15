#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1| GPIO_Pin_0|  GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;	
	TIM_TimBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimBaseInitStructure.TIM_Period=20000-1;//ARR
    TIM_TimBaseInitStructure.TIM_Prescaler=72-1;//PSC
	TIM_TimBaseInitStructure.TIM_RepetitionCounter=0;//50Hz，20ms,舵机的工作周期
	TIM_TimeBaseInit(TIM2,&TIM_TimBaseInitStructure);
	
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);//有些参数是高级定时器(N)用的，普通的用不到，赋初值，避免BUG
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//PWM模式1，Counter<CCR为有效电平，否则为无效电平
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//高电平为有效电平
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;//CCR
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);//通道二初始化，PA1
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);//通道一初始化，PA0
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);//通道三初始化，PA2
	TIM_OC4Init(TIM2,&TIM_OCInitStructure);//通道三初始化，PA2
	TIM_Cmd(TIM2,ENABLE);
	
	
}

void PWM_SetCompare2(uint16_t Compare)//通道二的CCR设置
{
	TIM_SetCompare2(TIM2,Compare);		
}


void PWM_SetCompare1(uint16_t Compare)//通道一的CCR设置
{
	TIM_SetCompare1(TIM2,Compare);		
}


void PWM_SetCompare3(uint16_t Compare)//通道三的CCR设置
{
	TIM_SetCompare3(TIM2,Compare);		
}


void PWM_SetCompare4(uint16_t Compare)//通道四的CCR设置
{
	TIM_SetCompare4(TIM2,Compare);		
}


