/*
 * Copyright (c) 2023 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <dm.h>
#include <misc.h>
#include <mmc.h>
#include <spl.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/hardware.h>
#include <asm/arch/ioc_rk3576.h>
#include <asm/system.h>

DECLARE_GLOBAL_DATA_PTR;

#define VCCIO_IOC_BASE	0x26046000
#define GPIO1A_IOMUX_SEL_0	0x4020
#define GPIO1A_IOMUX_SEL_1	0x4024
#define GPIO1B_IOMUX_SEL_0	0x4028
#define GPIO2A_IOMUX_SEL_0	0x4040
#define GPIO2A_IOMUX_SEL_1	0x4044

#define VCCIO6_IOC_BASE	0x2604a000
#define VCCIO7_IOC_BASE	0x2604b000

#define FW_SYS_SGRF_BASE	0x26005000
#define SGRF_DOMAIN_CON2	0x8
#define SGRF_DOMAIN_CON5	0x14

#ifdef CONFIG_ARM64
#include <asm/armv8/mmu.h>

static struct mm_region rk3576_mem_map[] = {
	{
		.virt = 0x20000000UL,
		.phys = 0x20000000UL,
		.size = 0xb080000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		.virt = 0x3fe70000UL,
		.phys = 0x3fe70000UL,
		.size = 0x190000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		.virt = 0x40000000UL,
		.phys = 0x40000000UL,
		.size = 0x100000000UL - 0x40000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	}, {
		.virt = 0x900000000UL,
		.phys = 0x900000000UL,
		.size = 0x100800000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = rk3576_mem_map;
#endif

void board_debug_uart_init(void)
{
}

#ifdef CONFIG_SPL_BUILD
void rockchip_stimer_init(void)
{
	/* If Timer already enabled, don't re-init it */
	u32 reg = readl(CONFIG_ROCKCHIP_STIMER_BASE + 0x4);
	if (reg & 0x1)
		return;

	asm volatile("msr CNTFRQ_EL0, %0" : : "r" (COUNTER_FREQUENCY));
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE + 0x14);
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE + 0x18);
	writel(0x00010001, CONFIG_ROCKCHIP_STIMER_BASE + 0x4);
}
#endif

#ifndef CONFIG_TPL_BUILD
int arch_cpu_init(void)
{
#ifdef CONFIG_SPL_BUILD
	u32 val;

	/* Set the emmc to access ddr memory */
	val = readl(FW_SYS_SGRF_BASE + SGRF_DOMAIN_CON2);
	writel(val | 0x7, FW_SYS_SGRF_BASE + SGRF_DOMAIN_CON2);

	/* Set the sdmmc0 to access ddr memory */
	val = readl(FW_SYS_SGRF_BASE + SGRF_DOMAIN_CON5);
	writel(val | 0x700, FW_SYS_SGRF_BASE + SGRF_DOMAIN_CON5);

	/* Set the emmc iomux */
	writel(0xffff1111, VCCIO_IOC_BASE + GPIO1A_IOMUX_SEL_0);
	writel(0xffff1111, VCCIO_IOC_BASE + GPIO1A_IOMUX_SEL_1);
	writel(0xffff1111, VCCIO_IOC_BASE + GPIO1B_IOMUX_SEL_0);

	/* Set the sdmmc0 iomux */
	writel(0xffff1111, VCCIO_IOC_BASE + GPIO2A_IOMUX_SEL_0);
	writel(0x00ff0011, VCCIO_IOC_BASE + GPIO2A_IOMUX_SEL_1);
#endif
	return 0;
}
#endif
