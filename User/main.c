#include "stm32f10x.h"
#include "Delay.h"
#include "Servo.h"
#include "Key.h"
#include "OLED.h"

#define DelayTime 30  //机械臂速度，值越小，运动越快

uint8_t KeyNum;
float Angle1=90,Angle2=90,Angle3=90,Angle4=90;
void f_auto1(void);

int main(void)
{
	OLED_Init();
	Key_Init();
	Servo_Init();
	OLED_ShowString(1,1,"Servo1:");
	OLED_ShowString(2,1,"Servo2:");
	OLED_ShowString(3,1,"Servo3:");
	OLED_ShowString(4,1,"Servo4:");
	
	while(1)
	{
		f_auto1();//机械臂自动运行
		
		
		//以下为手动调试，需进行手动调试请注释25行代码，调试时，注意限位
		KeyNum=Key_GetNum();
		//前后,右侧舵机
		if(KeyNum==1)
		{
			Angle1+=15;		
			if(Angle1>165)//最大角度，不同机械臂最大角度不同
			{
				Angle1=165;
			}
			Servo_SetAngle1(Angle1);
		}
		if(KeyNum==11)
		{
			Angle1-=15;
			if(Angle1<30)
			{
				Angle1=30;
			}
			Servo_SetAngle1(Angle1);
		}
		
		//高低，左侧舵机
		if(KeyNum==12)
		{
			Angle2+=15;
			if(Angle2>180)
			{
				Angle2=180;
			}
			Servo_SetAngle2(Angle2);
		}
		if(KeyNum==14)
		{
			Angle2-=15;
			if(Angle2<105)
			{
				Angle2=105;
			}
			Servo_SetAngle2(Angle2);
		}
		//爪子
		if(KeyNum==13)
		{
			Angle3+=5;
			if(Angle3>115)
			{
				Angle3=115;
			}
			Servo_SetAngle3(Angle3);
		}
		if(KeyNum==15)
		{
			Angle3-=5;
			if(Angle3<105)
			{
				Angle3=105;
			}
			Servo_SetAngle3(Angle3);
		}
		OLED_ShowNum(1,8,Angle1,3);
		OLED_ShowNum(2,8,Angle2,3);
		OLED_ShowNum(3,8,Angle3,3);
		OLED_ShowNum(4,8,Angle4,3);
	}

}
void f_auto1(void)
{
//初始化
	Servo_SetAngle4(90);///旋转
	Servo_SetAngle3(115);//爪子
	Servo_SetAngle1(75);//前后
	Servo_SetAngle2(150);//高低
	
//抓取
	//旋转，底层舵机
	for(int i=90;i<170;i++)
	{
		Servo_SetAngle4(i);
		Delay_ms(DelayTime);
	}
	
	
	//爪子，前方舵机
	for(int i=115;i>=105;i--)
	{
		Servo_SetAngle3(i);
		Delay_ms(DelayTime);
	}	
	
	//高低，左侧舵机
	for(int i=150;i<180;i++)
	{
		Servo_SetAngle2(i);
		Delay_ms(DelayTime);
	}	
	
	//前后，右侧舵机
	
	for(int i=75;i<135;i++)
	{
		Servo_SetAngle1(i);
		Delay_ms(DelayTime);
	}
	
	
	
	
//移动
	
	//爪子，前方舵机
	for(int i=105;i<115;i++)
	{
		Servo_SetAngle3(i);
		Delay_ms(DelayTime);
	}	
	
	//前后，右侧舵机
	
	for(int i=135;i>75;i--)
	{
		Servo_SetAngle1(i);
		Delay_ms(DelayTime);
	}
	
	
	//高低，左侧舵机
	for(int i=180;i>150;i--)
	{
		Servo_SetAngle2(i);
		Delay_ms(DelayTime);
	}	
	//旋转，底层舵机
	for(int i=170;i>10;i--)
	{
		Servo_SetAngle4(i);
		Delay_ms(DelayTime);
	}
	
	
//安放
	
	
	//高低，左侧舵机
	for(int i=150;i<180;i++)
	{
		Servo_SetAngle2(i);
		Delay_ms(DelayTime);
	}	
	
	//前后，右侧舵机
	
	for(int i=75;i<135;i++)
	{
		Servo_SetAngle1(i);
		Delay_ms(DelayTime);
	}
	//爪子，前方舵机
	for(int i=115;i>=105;i--)
	{
		Servo_SetAngle3(i);
		Delay_ms(DelayTime);
	}	
	
	
//归位	
	//前后，右侧舵机
	
	for(int i=135;i>75;i--)
	{
		Servo_SetAngle1(i);
		Delay_ms(DelayTime);
	}
	
	
	//高低，左侧舵机
	for(int i=180;i>150;i--)
	{
		Servo_SetAngle2(i);
		Delay_ms(DelayTime);
	}	
	//爪子，前方舵机
	for(int i=105;i<115;i++)
	{
		Servo_SetAngle3(i);
		Delay_ms(DelayTime);
	}
	//旋转，底层舵机
	for(int i=10;i<90;i++)
	{
		Servo_SetAngle4(i);
		Delay_ms(DelayTime);
	}
}
