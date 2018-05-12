-include make/common.mk

CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar

INCLUDE_DIRS :=					\
   -Iinclude					\
   -Iinclude/$(ARCH)


CC_WARNINGS :=					\
   -Wall					\
   -Wextra					\
   -Wshadow					\
   -Winit-self					\
   -Wfloat-equal				\
   -Wtrigraphs					\
   -Wconversion					\
   -Wcast-align					\
   -Wlogical-op					\
   -Wunsafe-loop-optimizations			\
   -Wdouble-promotion				\
   -Wformat=2

C_STANDARD = -std=gnu11

COMMON_CFLAGS := $(CC_WARNINGS) $(C_STANDARD) $(INCLUDE_DIRS) -g3 -O0

info-cc = @echo "  CC        $(1)"
