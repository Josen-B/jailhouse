/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for Phytium E2000Q
 * Copyright (c) 2022-2024 ZCShou
 *
 * Authors:
 *  ZCShou <72115@163.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */
#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[73];
	struct jailhouse_irqchip irqchips[1];
} __attribute__((packed)) config = {
	.header = {
		.signature = JAILHOUSE_SYSTEM_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.architecture = JAILHOUSE_ARM64,
		.flags = JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE,
		.hypervisor_memory = {
			.phys_start = 0xb0000000,
			.size		= 0x01000000,
		},
		.debug_console = {
			.address = 0x2800d000,
			.size	 = 0x1000,
			.type	 = JAILHOUSE_CON_TYPE_PL011,
			.flags	 = JAILHOUSE_CON_ACCESS_MMIO | JAILHOUSE_CON_REGDIST_4,
		},
		.platform_info = {
			.pci_mmconfig_base = 0x40000000,
			.pci_mmconfig_end_bus = 0xff,
			.pci_is_virtual = 0,
			.pci_domain = 0,
			.arm = {
				.gic_version = 3,
				.gicd_base = 0x30800000, /* GICD */
				.gicr_base = 0x30880000, /* GICR */
				.gicc_base = 0x30840000, /* GICC */
				.gich_base = 0x30850000, /* GICH */
				.gicv_base = 0x30860000, /* GICV */
				.maintenance_irq = 25,
			},
		},
		.root_cell = {
			.name = "phytium",

			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
			.num_irqchips = ARRAY_SIZE(config.irqchips),
			.vpci_irq_base = 95-32,
		},
	},

	.cpus = {
		0b1111,
	},

	.mem_regions = {
		/* Main Memory Address Space */
		/* RAM-0 */
		{
			.phys_start = 0x80000000,
			.virt_start = 0x80000000,
			.size		= 0x80000000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_EXECUTE,
		},

		/* RAM-1 */
		{
			.phys_start = 0x2000000000,
			.virt_start = 0x2000000000,
			.size		= 0x2000000000, //Maximum support 128G
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_EXECUTE,
		},

		/* I/O Address Space */

		/* MMCSD0 */
		{
			.phys_start = 0x28000000,
			.virt_start = 0x28000000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* MMCSD1 */
		{
			.phys_start = 0x28001000,
			.virt_start = 0x28001000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* NANDFlash: disabled */
		{
			.phys_start = 0x28002000,
			.virt_start = 0x28002000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* HDA: disabled */
		{
			.phys_start = 0x28006000,
			.virt_start = 0x28006000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* Inner ROM: for QSPI */
		{
			.phys_start = 0x00000000,
			.virt_start = 0x0fffffff,
			.size		= 0x10000000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* QSPI */
		{
			.phys_start = 0x28008000,
			.virt_start = 0x28008000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* DDMA1 */
		{
			.phys_start = 0x28005000,
			.virt_start = 0x28005000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* I2S */
		{
			.phys_start = 0x28009000,
			.virt_start = 0x28009000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* CAN0 */
		{
			.phys_start = 0x2800A000,
			.virt_start = 0x2800A000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* CAN1 */
		{
			.phys_start = 0x2800B000,
			.virt_start = 0x2800B000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* UART0: disabled */
		{
			.phys_start = 0x2800c000,
			.virt_start = 0x2800c000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* UART1 */
		{
			.phys_start = 0x2800d000,
			.virt_start = 0x2800d000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* UART2 */
		{
			.phys_start = 0x2800e000,
			.virt_start = 0x2800e000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* UART3: disabled */
		{
			.phys_start = 0x2800f000,
			.virt_start = 0x2800f000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* LPC: for Baseboard Management Controller */
		{
			.phys_start = 0x28010000,
			.virt_start = 0x28010000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* I2C0: MIO9 */
		{
			.phys_start = 0x28026000,
			.virt_start = 0x28026000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* I2C1: MIO14 */
		{
			.phys_start = 0x28030000,
			.virt_start = 0x28030000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* GPIO0 */
		{
			.phys_start = 0x28034000,
			.virt_start = 0x28034000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* GPIO1 */
		{
			.phys_start = 0x28035000,
			.virt_start = 0x28035000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* GPIO2 */
		{
			.phys_start = 0x28036000,
			.virt_start = 0x28036000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* GPIO3 */
		{
			.phys_start = 0x28037000,
			.virt_start = 0x28037000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* GPIO4 */
		{
			.phys_start = 0x28038000,
			.virt_start = 0x28038000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* GPIO5 */
		{
			.phys_start = 0x28039000,
			.virt_start = 0x28039000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* SPIM0: disabled */
		{
			.phys_start = 0x2803A000,
			.virt_start = 0x2803A000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* SPIM1: disalbed */
		{
			.phys_start = 0x2803B000,
			.virt_start = 0x2803B000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* SPIM2 */
		{
			.phys_start = 0x2803C000,
			.virt_start = 0x2803C000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* SPIM3: disabled */
		{
			.phys_start = 0x2803D000,
			.virt_start = 0x2803D000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* WDT0 */
		{
			.phys_start = 0x28040000,
			.virt_start = 0x28040000,
			.size		= 0x2000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* WDT1 */
		{
			.phys_start = 0x28042000,
			.virt_start = 0x28042000,
			.size		= 0x2000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* PWM0: disabled */
		{
			.phys_start = 0x2804A000,
			.virt_start = 0x2804A000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* PWM1: disabled */
		{
			.phys_start = 0x2804B000,
			.virt_start = 0x2804B000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* Timer && Fan Tachometer: disabled (Tacho0 ~ Tacho37) */
		{
			.phys_start = 0x28054000,
			.virt_start = 0x28054000,
			.size		= 0x38000, /* =0x1000*38 */
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* Keypad */
		{
			.phys_start = 0x2807A000,
			.virt_start = 0x2807A000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* SMMU-v3 */
		{
			.phys_start = 0x30000000,
			.virt_start = 0x30000000,
			.size		= 0x800000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* ITS */
		{
			.phys_start = 0x30820000,
			.virt_start = 0x30820000,
			.size		= 0x20000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* DEV1_CFG: for usb_vhub0 */
		{
			.phys_start = 0x31990000,
			.virt_start = 0x31990000,
			.size		= 0x10000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* DEV2_CFG: for usb_vhub2 */
		{
			.phys_start = 0x319A0000,
			.virt_start = 0x319A0000,
			.size		= 0x10000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* DEV3_CFG: for usb_vhub3 */
		{
			.phys_start = 0x319B0000,
			.virt_start = 0x319B0000,
			.size		= 0x10000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* EDAC */
		{
			.phys_start = 0x31400000,
			.virt_start = 0x31400000,
			.size           = 0x2000,
			.flags          = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		{
			.phys_start = 0x32B28000,
			.virt_start = 0x32B28000,
			.size           = 0x1000,
			.flags          = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* usb_vhub0: OTG */
		{
			.phys_start = 0x31800000,
			.virt_start = 0x31800000,
			.size		= 0x800000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* usb_vhub1: peripheral */
		{
			.phys_start = 0x31880000,
			.virt_start = 0x31880000,
			.size		= 0x800000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* usb_vhub2: peripheral */
		{
			.phys_start = 0x31900000,
			.virt_start = 0x31900000,
			.size		= 0x800000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* USB2_0 UIB: for USB2-0 */
		{
			.phys_start = 0x32880000,
			.virt_start = 0x32880000,
			.size		= 0x40000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* USB2_1 UIB: for USB2-1 */
		{
			.phys_start = 0x328C0000,
			.virt_start = 0x328C0000,
			.size		= 0x40000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* USB2-0: disalbed */
		{
			.phys_start = 0x32800000,
			.virt_start = 0x32800000,
			.size		= 0x40000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* USB2-1: disalbed */
		{
			.phys_start = 0x32840000,
			.virt_start = 0x32840000,
			.size		= 0x40000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* USB3-0 */
		{
			.phys_start = 0x31A08000,
			.virt_start = 0x31A08000,
			.size		= 0x18000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* USB3-1 */
		{
			.phys_start = 0x31A28000,
			.virt_start = 0x31A28000,
			.size		= 0x18000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* SATA0 */
		{
			.phys_start = 0x31A40000,
			.virt_start = 0x31A40000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* SATA1 */
		{
			.phys_start = 0x32014000,
			.virt_start = 0x32014000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* DC */
		{
			.phys_start = 0x32000000,
			.virt_start = 0x32000000,
			.size		= 0x4000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* DP0 */
		{
			.phys_start = 0x32004000,
			.virt_start = 0x32004000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* DP1 */
		{
			.phys_start = 0x32005000,
			.virt_start = 0x32005000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* I2S0_DMA: for I2S0 */
		{
			.phys_start = 0x32008000,
			.virt_start = 0x32008000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* I2S0: for DP0 */
		{
			.phys_start = 0x32009000,
			.virt_start = 0x32009000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* I2S1_DMA: for I2S1 */
		{
			.phys_start = 0x3200A000,
			.virt_start = 0x3200A000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* I2S1: for DP1 */
		{
			.phys_start = 0x3200B000,
			.virt_start = 0x3200B000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* MAC0 */
		{
			.phys_start = 0x3200C000,
			.virt_start = 0x3200C000,
			.size		= 0x2000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* MAC1 */
		{
			.phys_start = 0x3200E000,
			.virt_start = 0x3200E000,
			.size		= 0x2000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* MAC2 */
		{
			.phys_start = 0x32010000,
			.virt_start = 0x32010000,
			.size		= 0x2000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* MAC3 */
		{
			.phys_start = 0x32012000,
			.virt_start = 0x32012000,
			.size		= 0x2000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* Mailbox */
		{
			.phys_start = 0x32A00000,
			.virt_start = 0x32A00000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* SRAM */
		{
			.phys_start = 0x32A10000,
			.virt_start = 0x32A10000,
			.size		= 0x2000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* SCE: System Cryto Engine */
		{
			.phys_start = 0x32A30000,
			.virt_start = 0x32A30000,
			.size		= 0x6000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* Hardware Random Number Generator:rng */
		{
			.phys_start = 0x32A36000,
			.virt_start = 0x32A36000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* Semaphore: hwspinlock (disabled) */
		{
			.phys_start = 0x32B36000,
			.virt_start = 0x32B36000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},

		/* PCIe ECAM */
		{
			.phys_start = 0x40000000,
			.virt_start = 0x40000000,
			.size		= 0x10000000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* PCIe IO */
		{
			.phys_start = 0x50000000,
			.virt_start = 0x50000000,
			.size		= 0x00F00000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* PCIe Mem32 */
		{
			.phys_start = 0x58000000,
			.virt_start = 0x58000000,
			.size		= 0x28000000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* PCIe Mem64 */
		{
			.phys_start = 0x1000000000,
			.virt_start = 0x1000000000,
			.size		= 0x1000000000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
	},

	.irqchips = {
		/* GIC */
		{
			.address = 0x30800000,
			.pin_base = 32,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			},
		},
	},
};

