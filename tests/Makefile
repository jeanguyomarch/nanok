include make/common.mk
include make/compiler.mk

builddir ?= .
ky ?= $(builddir)/ky.a

TESTS := pool
TESTS += list
TESTS += run

all: $(TESTS)

Q=

define gen-test

$$(builddir)/tests/$(1): tests/$(1)/test.c $$(ky) tests/include/ktest/ktest.h | $$(builddir)/tests
	$(call info-cc,$$<)
	$$(Q)$$(CC) $$(COMMON_CFLAGS) $$^ -o $$@ -Itests/include

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
