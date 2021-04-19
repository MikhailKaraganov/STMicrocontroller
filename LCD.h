#include "stm32f4xx.h"              
#include "stdlib.h"
#include "stdio.h"

#define S1C1 0x00
#define S1C2 0x01
#define S1C3 0x02
#define S1C4 0x03
#define S1C5 0x04
#define S1C6 0x05
#define S1C7 0x06
#define S1C8 0x07
#define S2C1 0x40
#define S2C2 0x41
#define S2C3 0x42
#define S2C4 0x43
#define S2C5 0x44
#define S2C6 0x45
#define S2C7 0x46
#define S2C8 0x47

#define D0 0x30
#define	D1 0x31
#define D2 0x32 
#define D3 0x33
#define D4 0x34
#define D5 0x35 
#define D6 0x36
#define D7 0x37
#define D8 0x38
#define D9 0x39
#define A 0x41
#define	B 0x42
#define C 0x43
#define	D 0x44
#define	E 0x45
#define	F 0x46
#define	G 0x47
#define	H 0x48
#define	I 0x49
#define	J 0x4A
#define	K 0x4B
#define	L 0x4C
#define	M 0x4D
#define	N 0x4E
#define	O 0x4F
#define	P 0x50
#define Q 0x51
#define R 0x52
#define S 0x53
#define T 0x54
#define U 0x55
#define V 0x56
#define W 0x57
#define X 0x58
#define Y 0x59
#define Z 0x5A
#define POINT 0x2E
#define prob 0x20
#define vosc 0X21

int i=0;
int state = 0;

void TIM6_init () 
{
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM6EN, ENABLE);
	TIM6->DIER = 0b1;
	TIM6->PSC = 16000;
	TIM6->ARR = 1000;
	TIM6->CR1 = 0b10000101;
	
}



void delay(int step) {
		while (i != step ) 
		{
		i=i+1;
		}
		i=0;
	}

void ClearDisplay (void) {
	GPIOA->BSRRL |= (1<<0);
	GPIOB->BSRRL |= (1<<2);
	i = 0;
	delay(6000);
	GPIOB->BSRRH |= (1<<2);
	GPIOA->BSRRH |= (1<<0);
}
void ReturnHome (void) {
	GPIOA->BSRRL |= (1<<1);
	GPIOB->BSRRL |= (1<<2);
	i = 0;
	delay(7000);
	GPIOB->BSRRH |= (1<<2);
	GPIOA->BSRRH |= (1<<1);
}
void EntryModeSet (int ID, int Sh) {  // I/D - cursor moving direction, shift of display
	GPIOA->BSRRL |= (1<<2) | (ID<<1) | (Sh<<0);
	GPIOB->BSRRL |= (1<<2);
	delay(3000);
	GPIOB->BSRRH |= (1<<2);
	GPIOA->BSRRH |= (1<<2) | (ID<<1) | (Sh<<0);
}
void DisplayOnOffControl (int Di, int Cu, int Bl) { // Display, Cursor, Bliinking of Cursor //(1 or 0)
	GPIOA->BSRRL |= (1<<3) | (Di<<2) | (Cu<<1) | (Bl<<0);
	GPIOB->BSRRL |= (1<<2);
	delay(3000);
	GPIOB->BSRRH |= (1<<2);
	GPIOA->BSRRH |= (1<<3) | (Di<<2) | (Cu<<1) | (Bl<<0);
}
void CursorOrDisplayShift (int SC, int RL) { // cursor and display shift control and its direction
	GPIOA->BSRRL |= (1<<4)|(SC<<3)|(RL<<2); 
	GPIOB->BSRRL |= (1<<2);
	delay(3000);
	GPIOB->BSRRH |= (1<<2);
	GPIOA->BSRRH |= (1<<4)|(SC<<3)|(RL<<2);
}
void FunctionSet (int DL, int Nu, int Fo) {	// Data length (8-bits/4-bits), number of display line (N - 0/1), Font tipe (F) 
	GPIOA->BSRRL |= (1<<5)|(DL<<4)|(Nu<<3)|(Fo<<2); 
	GPIOB->BSRRL |= (1<<2);
	delay(3000);
	GPIOB->BSRRH |= (1<<2);
	GPIOA->BSRRH |= (1<<5)|(DL<<4)|(Nu<<3)|(Fo<<2);
}
void SetDDRamAdress (int SnCn) { 
	GPIOA->ODR = SnCn;
	GPIOA->BSRRL = (1<<7);
	GPIOB->BSRRL = (1<<2);
	delay(3000);
	GPIOB->BSRRH = (1<<2);
	GPIOA->ODR = 0x0000000;
}
int ReadBusyFlag () {
	GPIOB->BSRRL |= (1<<2) | (1<<1);
	if (((GPIOA->ODR)&0x80) == 0 ) {
	GPIOB->BSRRH |= (1<<2);
	return 0;
	}
	else {
	GPIOB->BSRRH |= (1<<2);
	return 1;
	}
}

void WriteDataToRAM(int CHAR) {
	GPIOB->BSRRL |= (1>>0);
	GPIOA->ODR = CHAR;
	GPIOA->BSRRL |= (1>>7);
	GPIOB->BSRRL |= (1<<2);
	delay(3000);
	GPIOB->BSRRH |= (1<<2)| (1<<0);
	GPIOA->ODR = 0x0000000;
}
void ToLCD (char* CHAR) {   //   "CHAR"  ==  "Smth to LCD"
	int i = 0;
	while (*(CHAR+i)!='\0') {
		WriteDataToRAM(*(CHAR+i));
		i++;
	}
}
