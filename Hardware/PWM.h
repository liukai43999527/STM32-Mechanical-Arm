#ifndef __PWM_H
#define __PWM_H
void PWM_Init(void);
void PWM_SetCompare2(uint16_t Compare);
void PWM_SetCompare1(uint16_t Compare);
void PWM_SetCompare3(uint16_t Compare);//通道三的CCR设置
void PWM_SetCompare4(uint16_t Compare);//通道四的CCR设置
#endif

