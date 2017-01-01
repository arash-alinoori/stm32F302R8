#include "string.h"
#include "stm32f30x.h"
#include "ini.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

char send_buffer[50] = "";
uint8_t send_index = 0;

void print()
{
	if (send_buffer[send_index] != '\0')
	{
		USART_SendData(USART2, send_buffer[send_index++]);
	}
	else
	{
		send_buffer[0] = '\0';
		send_index = 0;
	}
}

void main()
{
	ini_all();
	RCC_ClocksTypeDef rcc_clock_struct;
	RCC_GetClocksFreq(&rcc_clock_struct);
	sprintf(send_buffer, "init done %u\r\n", rcc_clock_struct.SYSCLK_Frequency);
	print();
	while (1)
	{
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

void TIM1_UP_TIM16_IRQHandler()
{
	static uint8_t tmp = 0;
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		if (tmp < 19) tmp++; else tmp = 0;
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		GPIOA->ODR ^= GPIO_Pin_5;
		//sprintf(send_buffer, "Index = %d \r\n", tmp);
		//print();
	}
}

void USART2_IRQHandler()
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		uint8_t rcv_Byte = USART_ReceiveData(USART2);
		USART_SendData(USART2, rcv_Byte);
		switch (rcv_Byte)
		{
		case 'a':
			TIM1->CNT = 0;
			TIM1->ARR = 400;
			break;
		case 'b':
			TIM1->CNT = 0;
			TIM1->ARR = 800;
			break;
		case 'c':
			TIM1->CNT = 0;
			TIM1->ARR = 4000;
			break;
		}

	}
	if (USART_GetITStatus(USART2, USART_IT_TC) == SET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_TC);
		print();
	}
}
