CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar

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

info-cc = @echo "  CC        $(1)"
