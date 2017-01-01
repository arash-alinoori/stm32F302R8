#include "ini.h"

void ini_timer() 	/////////// Timer Config
{
	TIM_TimeBaseInitTypeDef time_init_struct;
	time_init_struct.TIM_ClockDivision =  TIM_CKD_DIV1;
	time_init_struct.TIM_CounterMode = TIM_CounterMode_Up;
	time_init_struct.TIM_Period =  400;
	time_init_struct.TIM_Prescaler =  0xFFFF;
	time_init_struct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &time_init_struct);
	TIM_Cmd(TIM1, ENABLE);
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

	NVIC_InitTypeDef nvic_init_struct;
	nvic_init_struct.NVIC_IRQChannel = TIM1_UP_TIM16_IRQn;
	nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 1;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_init_struct);
}

void ini_USART()
{
	GPIO_InitTypeDef GPIO_init_struct;

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);
	GPIO_init_struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_init_struct.GPIO_OType = GPIO_OType_PP;
	GPIO_init_struct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_init_struct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(GPIOA, &GPIO_init_struct);
	
	USART_InitTypeDef usart_struct;
	usart_struct.USART_BaudRate = 115200;
	usart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart_struct.USART_Parity = USART_Parity_No;
	usart_struct.USART_StopBits = USART_StopBits_1;
	usart_struct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &usart_struct);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_TC, ENABLE);
	USART_Cmd(USART2, ENABLE);
	
	NVIC_InitTypeDef nvic_init_struct;
	nvic_init_struct.NVIC_IRQChannel = USART2_IRQn;
	nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_init_struct);
}

void ini_LEDpushbutton()
{
	GPIO_InitTypeDef GPIO_init_struct;

	GPIO_init_struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_init_struct.GPIO_OType = GPIO_OType_PP;
	GPIO_init_struct.GPIO_Pin = GPIO_Pin_13;
	GPIO_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_init_struct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(GPIOC, &GPIO_init_struct);

	GPIO_init_struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_init_struct.GPIO_OType = GPIO_OType_PP;
	GPIO_init_struct.GPIO_Pin = GPIO_Pin_5;
	GPIO_init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_init_struct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(GPIOA, &GPIO_init_struct);
}

void ini_all()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); //clock on port A
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE); //clock on port C
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //clock on timer
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //clock on usart

	ini_timer();
	ini_LEDpushbutton();
	ini_USART();
}	
	
	
