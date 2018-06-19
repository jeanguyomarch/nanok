/* NanoK - MIT License */

#include "stm32f4xx_hal.h"

__attribute__((naked)) void
SysTick_Handler(void)
{
  HAL_IncTick();
}
