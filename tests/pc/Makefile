include make/compiler.mk

builddir ?= .
ky ?= $(builddir)/ky.a 

SUBDIRS := pool
SUBDIRS += list
SUBDIRS += run
SUBDIRS += await


THIS_DIR := tests/$(TESTS_DIR)

CPPFLAGS += -I$(THIS_DIR)/include

outdir := $(builddir)/$(THIS_DIR)

all: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) APP=$(APP) -f make/build.mk srcdir=$(THIS_DIR)/$@ builddir=$(builddir)
	$(call info-ld,$(outdir)/$@/$@)
	$(Q)$(LD) $(LDFLAGS) $(outdir)/$@/_$@.o -o $(outdir)/$@/$@ $(ky)

define run-test
	@echo "-----------------------------------------------"
	@echo "-- Running test $(1)"
	$(Q)$(builddir)/$(THIS_DIR)/$(1)/$(1)

endef

run-tests: $(SUBDIRS)
	$(foreach test,$(SUBDIRS),$(call run-test,$(test)))

$(builddir)/tests/$(TESTS_DIR):
	@mkdir -p $@

.PHONY: all run-tests $(tests)
