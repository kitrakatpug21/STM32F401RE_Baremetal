#include <stm32f4xx.h>

#define GPIOBEN		(1U << 1)
#define GPIOAEN		(1U << 0)
#define PA5_ON		(1U << 5)
#define PA5_OFF		(1U << 21)
#define PB3_ON		(1U << 3)
#define PB3_OFF		(1U << 19)

int main(void)
{
	//1. Setup the peripheral clocks (AHB/APB)
	RCC -> AHB1ENR |= GPIOBEN|GPIOAEN;

	//2. Peripheral Setup
	GPIOB -> MODER |= (1U << 6);	// turn pin 3 as o/p
	GPIOB -> MODER &= ~(1U << 7);	// PB3

	GPIOA -> MODER |= (1U << 10);	// turn pin 5 as o/p
	GPIOA -> MODER &= ~(1U << 11);	// PA5

	while (1)
	{
		GPIOB -> BSRR = 0; GPIOA -> BSRR = 0;
		GPIOB -> BSRR |= PB3_ON; GPIOA -> BSRR |= PA5_OFF;
		for(long i = 0;i<400000;i++);
		GPIOB -> BSRR = 0; GPIOA -> BSRR = 0;
		GPIOB -> BSRR |= PB3_OFF; GPIOA -> BSRR |= PA5_ON;
		for(long i = 0;i<400000;i++);
	}
}
