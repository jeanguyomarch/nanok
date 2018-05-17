CPPFLAGS += -DSTM32F429xx
CPPFLAGS += -isystem lib/stm32/STM32F4xx_HAL_Driver/Inc
CPPFLAGS += -isystem lib/stm32/CMSIS/Device/ST/STM32F4xx/Include
CPPFLAGS += -isystem lib/stm32/CMSIS/Include
CPPFLAGS += -isystem include/stm32

CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb
CFLAGS += -mfloat-abi=softfp
CFLAGS += -mfpu=fpv4-sp-d16
CFLAGS += -march=armv7e-m
CFLAGS += -fomit-frame-pointer
CFLAGS += -ffreestanding
CFLAGS += -nostdlib
CFLAGS += -O0 -g3 -ggdb

LDFLAGS += -mcpu=cortex-m4
LDFLAGS += -specs=nosys.specs
LDFLAGS += -Wl,--gc-sections
