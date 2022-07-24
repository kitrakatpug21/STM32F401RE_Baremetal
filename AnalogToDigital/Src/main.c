#include <stm32f4xx.h>
#include <stdio.h>
#include "delay.h"
#include "uart2.h"
#define EOC (1U<<1)

void adc_single_conversion_init()
{
	//1. Enable clock access for GPIOA and ADC
	// AHB1- gpioA, APB2 - adc1
	RCC -> AHB1ENR |= (1U<<0); // GPIOA
	RCC -> APB2ENR |= (1U<<8); // ADC
	//2. Set PA1 pin to analog mode functionality
	GPIOA -> MODER |= (1U<<1)|(1U<<0);
	//3. Setup the conversion sequence
	//ADC1 -> SQR3 |= (1U<<0);// i setup SQR3 -> SQ1 as CH1
	ADC1 -> SQR3 = 0;
	//4. Setup the length of conversion sequence
	ADC1 -> SQR1 = 0;	// length of conversion is 0(=1 -1)
	//5. Enable the ADC modules
	ADC1 -> CR2 |= (1U<<0); // ADON = 1
//}
//uint16_t adc_start_conversion()
//{
	//1. Begin the conversion
	ADC1 -> CR2 |= (1U<<30);
	//2. wait for conversion to complete
	while(!((ADC1 -> SR) & EOC));
	//3. Clear the flag bits and read result
	printf("ADC RESULT: %ld\r\n",ADC1 -> DR);
}

int main(void)
{
	while(1)
	{
		adc_single_conversion_init();
		delay_ms(100);
	}
}

