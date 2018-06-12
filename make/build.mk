srcdir ?= .
builddir ?= .

include make/compiler.mk
include make/common.mk

include $(srcdir)/build.mk

objs := $(foreach src,$(sources),$(builddir)/$(srcdir)/$(src:.c=.o)) # XXX
deps := $(objs:.o=.d)
outdir := $(builddir)/$(srcdir)
run-ar = $(AR) TDrcs $(outdir)/_$(notdir $(srcdir)).o $(1)

subobjs := $(foreach subdir,$(SUBDIRS),$(outdir)/$(subdir)/_$(notdir $(subdir)).o)

all: $(SUBDIRS) $(objs)
ifneq ($(SUBDIRS),)
	@$(call run-ar,$(subobjs))
endif

$(outdir)/%.d: $(srcdir)/%.c
	@mkdir -p $(dir $@)
	@$(RM) $@
	@$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,$(builddir)/$(srcdir)/\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

-include $(deps)

$(outdir)/%.o: $(srcdir)/%.c
	$(call info-cc,$<)
	$(Q)$(CC) $(COMMON_CFLAGS) -c $< -o $@
	@$(call run-ar,$@)

$(outdir)/%.o: $(srcdir)/%.S
	@mkdir -p $(dir $@)
	$(call info-as,$<)
	$(Q)$(CC) -c $< -o $@
	@$(call run-ar,$@)


$(SUBDIRS):
	@$(MAKE) -f make/build.mk srcdir=$(srcdir)/$@ builddir=$(builddir)

.PHONY: all $(SUBDIRS)
