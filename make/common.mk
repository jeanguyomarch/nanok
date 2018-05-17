ifdef V
  ifneq (V,)
   BUILD_VERBOSE := 1
  endif # V != ''
endif # V

ifndef BUILD_VERBOSE
   BUILD_VERBOSE := 0
endif

ifeq ($(BUILD_VERBOSE),1)
   Q :=
else
   Q := @
endif


APP ?= apps/sim.mk
include $(APP)
