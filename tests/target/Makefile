include make/compiler.mk

builddir ?= .
ky ?= $(builddir)/ky.a

SUBDIRS := run

THIS_DIR := tests/$(TESTS_DIR)
LDSCRIPT := src/arch/$(ARCH)/ldscript.ld

outdir := $(builddir)/$(THIS_DIR)

CPPFLAGS += -isystem lib/stm32/BSP/STM32F429I-Discovery

all: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) APP=$(APP) -f make/build.mk srcdir=$(THIS_DIR)/$@ builddir=$(builddir)
	$(call info-ld,$(outdir)/$@/$@)
	$(Q)$(LD) -T $(LDSCRIPT) $(LDFLAGS) $(outdir)/$@/_$@.o -o $(outdir)/$@/$@.elf $(ky)
	$(Q)$(OBJCOPY) -O binary $(outdir)/$@/$@.elf $(outdir)/$@/$@.bin

.PHONY: all $(SUBDIRS)
