#include "System_Clock.h"

#define SET_PLLN	0b010110100U //180
#define SET_PLLM	0b000100U	//4
#define SET_PLLP	0b00U		//0->Prescaler 2

void SetAHBPrescaler(void)
{
    // Clear AHB prescaler bits
    RCC->CFGR &= ~RCC_CFGR_HPRE;

    // Set AHB prescaler to 8
    RCC->CFGR |= RCC_CFGR_HPRE_DIV8;
}

void SystemClock_Config(void)
{

    //HSE_frq = 8 MHz
    //PLLCLK = HSE_frq / PLLM * PLLN / PLLP //PLLP=2 in default!!
	// Enable HSE
	RCC->CR |= RCC_CR_HSEON;
	while((RCC->CR & RCC_CR_HSERDY) == 0); // wait until HSE is ready


    // Configure PLL
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN |
                      RCC_PLLCFGR_PLLP);

    // Setzen Sie die neuen Werte.
    RCC->PLLCFGR |= (RCC_PLLCFGR_PLLSRC_HSE    // HSE als PLL-Quelle.
                   | (25 << 0)                  // PLLM = 4.
                   | (256 << 6));         			// PLLN = 180.

    // Clear AHB prescaler bits
    RCC->CFGR &= ~RCC_CFGR_HPRE;

    // Set AHB prescaler to 8
    RCC->CFGR |= RCC_CFGR_HPRE_DIV8;

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    while((RCC->CR & RCC_CR_PLLRDY) == 0); // wait until PLL is ready


     // Configure Flash prefetch, Instruction cache, Data cache and wait state
    //FLASH->ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;

    // Select PLL as system clock source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // wait until PLL is used as system clock source
}



