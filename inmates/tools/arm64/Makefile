#
# Jailhouse, a Linux-based partitioning hypervisor
#
# Copyright (c) Siemens AG, 2013-2015
#
# Authors:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This work is licensed under the terms of the GNU GPL, version 2.  See
# the COPYING file in the top-level directory.
#

include $(INMATES_LIB)/Makefile.lib

INMATES := linux-loader.bin arceos-loader-phytiumpi.bin arceos-loader-raspi4.bin \
	   starry-loader-phytiumpi.bin starry-loader-raspi4.bin

linux-loader-y := linux-loader.o
arceos-loader-phytiumpi-y := arceos-loader-phytiumpi.o
arceos-loader-raspi4-y := arceos-loader-raspi4.o
starry-loader-phytiumpi-y := starry-loader-phytiumpi.o
starry-loader-raspi4-y := starry-loader-raspi4.o

$(eval $(call DECLARE_TARGETS,$(INMATES)))
