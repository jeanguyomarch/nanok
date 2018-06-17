/* NanoK - MIT License */

#include "nanok/init.h"
#include "nanok/assert.h"

#include <stm32f4xx.h>
#include <stm32f4xx_hal.h>

#include <stdbool.h>

/*
 * The system Clock is configured as follows:
 *    System Clock source            = PLL (HSE)
 *    SYSCLK(Hz)                     = 180000000
 *    HCLK(Hz)                       = 180000000
 *    AHB Prescaler                  = 1
 *    APB1 Prescaler                 = 4
 *    APB2 Prescaler                 = 2
 *    HSE Frequency(Hz)              = 8000000
 *    PLL_M                          = 8
 *    PLL_N                          = 360
 *    PLL_P                          = 2
 *    PLL_Q                          = 7
 *    VDD(V)                         = 3.3
 *    Main regulator output voltage  = Scale1 mode
 *    Flash Latency(WS)              = 5
 */
static void
_clock_init(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device
   is clocked below the maximum system frequency, to update the voltage
   scaling value regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    NK_ASSERT(false);

  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    NK_ASSERT(false);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
   clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    NK_ASSERT(false);
}



KAPI void
arch_init(void)
{
   HAL_Init();
   _clock_init();

   HAL_NVIC_SetPriorityGrouping(0);
   HAL_NVIC_SetPriority(SVCall_IRQn, 0xFF, 0x00);

   __disable_irq();

   // Enable FPU
   SCB->CPACR |= 0xF << 20;
   __ISB();
   // Enable automatic saving of FPU registers
   FPU->FPCCR |= FPU_FPCCR_ASPEN_Msk;
   // Disable lazy stacking of FPU registers
   FPU->FPCCR &= ~FPU_FPCCR_LSPEN_Msk;
}
