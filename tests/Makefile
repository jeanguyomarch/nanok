include make/common.mk
include make/compiler.mk

builddir ?= .
ky ?= $(builddir)/ky.a

TESTS := pool
TESTS += list

all: $(TESTS)

define gen-test

$$(builddir)/tests/$(1): tests/$(1)/test.c $$(ky) tests/include/ktest/ktest.h | $$(builddir)/tests
	$(call info-cc,$$<)
	$$(Q)$$(CC) $$^ -o $$@ $$(CC_WARNINGS) $$(C_STANDARD) -Iinclude -Itests/include

$(1): $$(builddir)/tests/$(1)

endef

$(foreach test,$(TESTS),$(eval $(call gen-test,$(test))))

define run-test
	@echo "-- Running test $(1)"
	@$(builddir)/tests/$(1)

endef

run: $(TESTS)
	$(foreach test,$(TESTS),$(call run-test,$(test)))

$(builddir)/tests:
	@mkdir -p $@

.PHONY: all run $(TESTS)
