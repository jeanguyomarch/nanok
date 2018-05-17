include make/compiler.mk

SUBDIRS := src
SUBDIRS += $(foreach lib,$(LIBS),lib/$(lib))


BUILD_DIR := build
KY := $(BUILD_DIR)/ky.a

all: $(SUBDIRS)

clean distclean:
	$(Q)$(RM) -r $(BUILD_DIR)

mrproper:
	$(Q)$(RM) -r $(BUILD_DIR)
	$(Q)$(RM) -r env/.env

ifeq ($(ARCH),pc)
check: $(SUBDIRS)
	@$(MAKE) APP=$(APP) -f tests/$(TESTS_DIR)/Makefile builddir=$(BUILD_DIR) ky=$(KY) run-tests
endif

tests: $(SUBDIRS)
	@$(MAKE) APP=$(APP) -f tests/$(TESTS_DIR)/Makefile builddir=$(BUILD_DIR) ky=$(KY) all

$(SUBDIRS):
	@$(MAKE) APP=$(APP) -f make/build.mk srcdir=$@ builddir=$(BUILD_DIR)
	$(Q)$(AR) $(ARFLAGS) $(KY) $(BUILD_DIR)/$@/_$(notdir $@).o

.PHONY: all $(SUBDIRS) clean distclean mrproper check tests
