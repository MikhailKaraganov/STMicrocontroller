#include "stm32f4xx.h"              
#include <LCD.h>
#include "stdlib.h"

#define DELAY1 300

 int main (void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	 
	
	 
	
	GPIOA->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0
									| GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | 
									GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0;
	GPIOA->PUPDR = GPIO_PuPd_DOWN;
	GPIOA->OSPEEDR = GPIO_High_Speed;
	GPIOA->ODR = 0x00000; 
	 
	GPIOE->MODER &= GPIO_MODER_MODER11;
	GPIOE->PUPDR = GPIO_MODER_MODER11_0;
	GPIOE->OSPEEDR = GPIO_MODER_MODER11_1;
	 
	
	GPIOD->MODER = GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0
									| GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 |
									GPIO_MODER_MODER6_1 |	GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0;
	//GPIOD->OTYPER = (1<<14) | (1<<13) | (1<<12)|(1<<15);
	GPIOD->OSPEEDR = GPIO_High_Speed;
	GPIOD->PUPDR = GPIO_PuPd_DOWN;
	GPIOD->ODR = 0x00000;
  
	 
	GPIOB->MODER = GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0
									| GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | 
									GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0;;
	GPIOB->PUPDR = GPIO_PuPd_DOWN;
	GPIOB->OSPEEDR = GPIO_High_Speed;
	GPIOB->BSRRH = (1<<0) | (1<<1);
	GPIOB->ODR = 0x00000;
	
	__enable_irq();
	TIM6_init();
	
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	
	ReturnHome(); 
	ClearDisplay();
	EntryModeSet(1,0);
	DisplayOnOffControl(1,1,1);
	CursorOrDisplayShift(1,0);
	FunctionSet(1,1,0);
	DisplayOnOffControl(1,1,1);

ToLCD("Start!");
ReturnHome();
	
delay(DELAY1);
	
	ClearDisplay();
	SetDDRamAdress(S1C1);
	ToLCD("Counter");

	delay(DELAY1);
	SetDDRamAdress(S2C3);
		
	int k =0;
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	
	
	while (1) {
		SetDDRamAdress(S1C1);
		ToLCD("Continu!");
		NVIC_EnableIRQ(TIM6_DAC_IRQn);
		SetDDRamAdress(S2C1);
		
		
		/*
		SetDDRamAdress(S2C1);
		ToLCD("Dig1");
		SetDDRamAdress(S2C1);
		delay(1000);
		ToLCD("Dig2");
		SetDDRamAdress(S2C1);
		delay(1000);
		ToLCD("Dig3");
		*/
		
		char s[10];
		if ((TIM6->CNT) == 0) 
			{	
				SetDDRamAdress(S2C1);
				k++;
				sprintf(s, "%d", k); 
				ToLCD(s);
			}
	}
		
}

void TIM6_DAC_IRQHandler (void)
{
	ClearDisplay();
	SetDDRamAdress(S2C1);
	ToLCD("IRQonWay");
	delay(900000);
	ClearDisplay();
	SetDDRamAdress(S2C1);
	ToLCD("AndNow");
	ClearDisplay();
	TIM6->SR = 00;
}
