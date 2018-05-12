
srcdir ?= .
builddir ?= .
ky ?= $(builddir)/ky.a

include make/compiler.mk
include make/common.mk


define gen-compile-obj
$$(builddir)/$(1): $$(srcdir)/$(patsubst %.o,%.c,$(1))
	$(call info-cc,$$<)
	$$(Q)$$(CC) -c $$< -o $$@ $$(CC_WARNINGS) $$(C_STANDARD) -Iinclude
	$$(Q)$$(AR) Drcs $$(ky) $$@

endef

include $(srcdir)/build.mk

.PHONY: all $(SUBDIRS)

all: $(SUBDIRS) $(foreach obj,$(objs),$(builddir)/$(obj) )

$(foreach obj,$(objs),$(eval $(call gen-compile-obj,$(obj))))

$(SUBDIRS):
	@mkdir -p $(builddir)/$(srcdir)/$@
	@$(MAKE) -f make/build.mk srcdir=$(srcdir)/$@ builddir=$(builddir)/$(srcdir)/$@ ky=$(ky)
