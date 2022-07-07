#include <stm32f4xx.h>
#include "delay.h"

#define GPIOAEN		(1U << 0)
#define PA5			(1U << 5)

int main(void)
{
	//1. Setup the peripheral clocks (AHB/APB)
	RCC -> AHB1ENR |= GPIOAEN;

	//2. Peripheral Setup
	GPIOA -> MODER |= (1U << 10);	// turn pin 5 as o/p
	GPIOA -> MODER &= ~(1U << 11);	// PA5

	while (1)
	{
		GPIOA -> ODR |= PA5;
		delay_ms(500);
		GPIOA -> ODR &= ~PA5;
		delay_ms(500);
	}
}
