# SPDX-License-Identifier: GPL-2.0-or-later
# Generic leaf rules include Makefile.
# Copyright (c) Linux Test Project, 2017-2022
# Copyright (C) 2009, Cisco Systems Inc.
# Ngie Cooper, July 2009

#
# generic_leaf_target
#
# Generate a set of basic targets (all, clean, install) for a leaf directory
# (no subdirectories).
#
# $(MAKE_DEPS)			: What should we execute beforehand as a
#				  dependency of $(MAKE_TARGETS)?
#
# $(INSTALL_FILES) -> install
#
# Helpful variables are:
#
# $(MAKE_TARGETS)		: What to execute as direct dependencies of
# 				  all.
# 				  1. Defaults to the basename of the targets
# 				     produced by the %.c -> % implicit pattern
# 				     rules, e.g. the MAKE_TARGET in a directory
# 				     like the following:
#
#				  $$ ls /bar
# 				  foo.c
#
#				     Would be `foo'. Similarly, the following
#				     dir structure:
#
#				  $$ ls /bar
# 				  foo.c zanzibar.c
#
#				     Would be `foo zanzibar'.
#
#				  2. If you define MAKE_TARGETS as an empty
#				     string, this will override the defaults.
#				     I did this to avoid providing too much
#				     rope to hang one's self in the event of
#				     unwanted behavior.
#
# $(HOST_MAKE_TARGETS)	: Host tools which use $HOSTCC.
#
# $(CLEAN_TARGETS)		: What targets should be cleaned (must be
#				  real files or directories). This will automatically append
#				  adds the .o suffix to all files referenced by
#				  $(MAKE_TARGETS)) to CLEAN_TARGETS, if MAKE_TARGETS wasn't
#				  defined (see
#				  $(MAKE_TARGETS)).
# $(INSTALL_MODE)		: What mode should we using when calling
# 				  install(1)?
#
# Also, if you wish to change the installation directory, from the set default
# (testcases/bin) you must do something like either one of the following items:
#
# Method A:
#
# INSTALL_DIR			:= /path/to/installdir/from/$(DESTDIR)/$(prefix)
#
# e.g. if I wanted to install my binaries in testcases/bin, I would do:
#
# INSTALL_DIR			:= testcases/bin
#
# in my calling Makefile.
#
# Or Method B:
#
# INSTALL_DIR			:= /path/to/installdir/from/$(DESTDIR)
#
# e.g. if I wanted to install my binaries in $(libdir) (which may not exist
# outside of $(prefix) right now, but could in the future), I could do the
# following:
#
# INSTALL_DIR			:= $(libdir)
#

.PHONY: all clean install check

ifneq ($(strip $(MAKE_TARGETS)),)
$(MAKE_TARGETS) += $(HOST_MAKE_TARGETS)
endif

$(MAKE_TARGETS): | $(MAKE_DEPS)

all: $(MAKE_TARGETS)

clean:: $(CLEAN_DEPS)
	-$(RM) -f -r $(CLEAN_TARGETS)

$(INSTALL_FILES): | $(INSTALL_DEPS)

install: $(INSTALL_FILES)

$(CHECK_TARGETS): | $(CHECK_DEPS)
check: $(CHECK_HEADER_TARGETS) $(CHECK_TARGETS) $(SHELL_CHECK_TARGETS)

# vim: syntax=make
