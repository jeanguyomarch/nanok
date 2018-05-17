include make/common.mk

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar
OBJCOPY := $(CROSS_COMPILE)objcopy

export CPPFLAGS ?=

CPPFLAGS +=					\
   -Iinclude					\
   -Iinclude/$(ARCH)

export CC_WARNINGS =				\
   -Wall					\
   -Wextra					\
   -Wshadow					\
   -Winit-self					\
   -Wfloat-equal				\
   -Wtrigraphs					\
   -Wconversion					\
   -Wlogical-op					\
   -Wunsafe-loop-optimizations			\
   -Wdouble-promotion				\
   -Wformat=2

export CFLAGS = $(CC_WARNINGS) -O0 -g3 -ggdb

export LDFLAGS =				\
   -Wall

export ARFLAGS = TDrcs


export C_STANDARD = -std=gnu11


COMMON_CFLAGS = $(CPPFLAGS) $(CFLAGS) $(C_STANDARD)

-include make/arch/$(ARCH)/compiler.mk

info-cc =      @echo "  CC        $(1)"
info-as =      @echo "  AS        $(1)"
info-ar =      @echo "  AR        $(1)"
info-ld =      @echo "  LD        $(1)"
info-objcopy = @echo "  OBJCOPY   $(1)"
info-strip   = @echo "  STRIP     $(1)"
