include make/common.mk

SUBDIRS := src
BUILD_DIR := build
KY := $(BUILD_DIR)/ky.a

all: $(SUBDIRS)

clean distclean mrproper:
	$(Q)$(RM) -r $(BUILD_DIR)

check:
	@$(MAKE) -f tests/Makefile builddir=$(BUILD_DIR) ky=$(KY) run

$(SUBDIRS):
	@$(MAKE) -f make/build.mk srcdir=$@ builddir=$(BUILD_DIR) ky=$(KY)

.PHONY: all $(SUBDIRS) clean distclean mrproper check
