/* NanoK - MIT License */

#include "stm32f4xx_hal.h"

void SysTick_Handler(void)
{
  HAL_IncTick();
}
