/* NanoK - MIT License */

#include "nanok/log.h"

#include <stm32f429i_discovery_lcd.h>
#include <string.h>
#include <stdarg.h>

static void
_lcd_clear(void)
{
   BSP_LCD_Clear(LCD_COLOR_WHITE);
   BSP_LCD_SetFont(&Font16);
   BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"NanoK", CENTER_MODE);
   BSP_LCD_SetFont(&Font12);
   BSP_LCD_DrawHLine(0, 17, (uint16_t)(BSP_LCD_GetXSize()));
}


KAPI void
arch_log_init(void)
{
   BSP_LCD_Init();
   BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER);
   BSP_LCD_SelectLayer(0);
   BSP_LCD_SetFont(&Font12);
   BSP_LCD_DisplayOn();
   _lcd_clear();
}

KAPI void
arch_log_puts(const char *string)
{
  static unsigned int line = 0u;

  BSP_LCD_DisplayStringAtLine((uint16_t)(line + 2u),
                              (uint8_t *)string);

  line += 1u;
  if (line >= 25u)
    {
       line = 0u;
       _lcd_clear();
    }
}

KAPI void
arch_log_puts_n(const char *message, size_t length __unused__)
{
   arch_log_puts(message);
}

KAPI void
arch_log_printf(const char *format, ...)
{
   char printf_buf[35];
   va_list args;

   va_start(args, format);
   vsnprintf(printf_buf, sizeof(printf_buf), format, args);
   va_end(args);

   arch_log_puts(printf_buf);
}
