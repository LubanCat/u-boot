/*
 * Copyright (c) 2025 Rockchip Electronics Co., Ltd
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
#include <asm/arch/grf_rv1126b.h>
#include <asm/arch/ioc_rv1126b.h>
#include <asm/system.h>

DECLARE_GLOBAL_DATA_PTR;

#define PMUIO0_IOC_BASE			0x201a0000
#define GPIO0A_IOMUX_SEL_L		0x0
#define GPIO0A_IOMUX_SEL_H		0x4
#define GPIO0B_IOMUX_SEL_L		0x8
#define GRF_JTAG_CON0			0x904

#define VCCIO1_IOC_BASE			0x201b0000
#define GPIO1A_IOMUX_SEL_L		0x20
#define GPIO1A_IOMUX_SEL_H		0x24
#define GPIO1B_IOMUX_SEL_L		0x28
#define GPIO1B_IOMUX_SEL_H		0x2c

#define VCCIO2_IOC_BASE			0x201b8000
#define GPIO2A_IOMUX_SEL_L		0x40
#define GPIO2A_IOMUX_SEL_H		0x44
#define GPIO2A_PULL			0x320

#define VCCIO3_IOC_BASE			0x201c0000
#define GPIO3A_IOMUX_SEL_L		0x60
#define GPIO3A_IOMUX_SEL_H		0x64
#define GPIO3B_IOMUX_SEL_H		0x6c
#define GPIO3A_PULL			0x330

#define SGRF_SYS_BASE			0x20220000
#define SGRF_SYS_AHB_SECURE_SGRF_CON	0x14
#define SGRF_SYS_AXI_SECURE_SGRF_CON0	0x18
#define FIREWALL_SLV_CON0		0x20
#define FIREWALL_SLV_CON1		0x24
#define FIREWALL_SLV_CON2		0x28
#define FIREWALL_SLV_CON3		0x2c
#define FIREWALL_SLV_CON4		0x30
#define FIREWALL_SLV_CON5		0x34
#define OTP_SGRF_CON			0x1c

#ifdef CONFIG_ARM64
#include <asm/armv8/mmu.h>

static struct mm_region rv1126b_mem_map[] = {
	{
		.virt = 0x20000000UL,
		.phys = 0x20000000UL,
		.size = 0x2800000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		.virt = 0x3ff1e000UL,
		.phys = 0x3ff1e000UL,
		.size = 0xe2000UL,
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
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = rv1126b_mem_map;
#endif

void board_debug_uart_init(void)
{
	/* No need to change uart in most time. */
}

#ifdef CONFIG_SPL_BUILD
void rockchip_stimer_init(void)
{
	u32 reg;

	/* If Timer already enabled, don't re-init it */
	reg = readl(CONFIG_ROCKCHIP_STIMER_BASE + 0x4);
	if (reg & 0x1)
		return;
#ifdef COUNTER_FREQUENCY
	asm volatile("msr CNTFRQ_EL0, %0" : : "r" (COUNTER_FREQUENCY));
#endif
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE + 0x14);
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE + 0x18);
	writel(0x00010001, CONFIG_ROCKCHIP_STIMER_BASE + 0x04);
}
#endif

void board_set_iomux(enum if_type if_type, int devnum, int routing)
{
	switch (if_type) {
	case IF_TYPE_MMC:
		if (devnum == 0) {
			writel(0xffff1111, VCCIO1_IOC_BASE + GPIO1A_IOMUX_SEL_L);
			writel(0xffff1111, VCCIO1_IOC_BASE + GPIO1A_IOMUX_SEL_H);
			writel(0xf0f01010, VCCIO1_IOC_BASE + GPIO1B_IOMUX_SEL_L);
		} else if (devnum == 1) {
			writel(0xffff1111, VCCIO2_IOC_BASE + GPIO2A_IOMUX_SEL_L);
			writel(0x00ff0011, VCCIO2_IOC_BASE + GPIO2A_IOMUX_SEL_H);
			writel(0x00f00010, PMUIO0_IOC_BASE + GPIO0A_IOMUX_SEL_H);
			/* Pull up */
			writel(0x0cff0455, VCCIO2_IOC_BASE + GPIO2A_PULL);
		} else if (devnum == 2) {
			writel(0xffff1111, VCCIO3_IOC_BASE + GPIO3A_IOMUX_SEL_L);
			writel(0x00ff0011, VCCIO3_IOC_BASE + GPIO3A_IOMUX_SEL_H);
			writel(0x0f000300, VCCIO3_IOC_BASE + GPIO3B_IOMUX_SEL_H);
			/* Pull up */
			writel(0x0ffc0554, VCCIO2_IOC_BASE + GPIO3A_PULL);
		}
		break;
	case IF_TYPE_MTD:
		if (routing == 0) {
			/* FSPI0 M0 */
			writel(0x0f0f0101, VCCIO1_IOC_BASE + GPIO1B_IOMUX_SEL_L);
			writel(0xffff1111, VCCIO1_IOC_BASE + GPIO1B_IOMUX_SEL_H);
			writel(0x00f00020, VCCIO1_IOC_BASE + GPIO1A_IOMUX_SEL_H);
		} else if (routing == 1) {
			/* FSPI1 M0 */
			writel(0x0fff0111, PMUIO0_IOC_BASE + GPIO0B_IOMUX_SEL_L);
			writel(0xff001100, PMUIO0_IOC_BASE + GPIO0A_IOMUX_SEL_H);
			writel(0x00f00010, PMUIO0_IOC_BASE + GPIO0A_IOMUX_SEL_L);
		} else if (routing == 2) {
			/* FSPI1 M1 */
			writel(0xffff2222, VCCIO1_IOC_BASE + GPIO1A_IOMUX_SEL_L);
			writel(0xf0f02020, VCCIO1_IOC_BASE + GPIO1B_IOMUX_SEL_L);
		}
		break;
	default:
		printf("Bootdev 0x%x is not support\n", if_type);
	}
}

void board_unset_iomux(enum if_type if_type, int devnum, int routing)
{
	switch (if_type) {
	case IF_TYPE_MMC:
		if (devnum == 0) {
			writel(0xffff0000, VCCIO1_IOC_BASE + GPIO1A_IOMUX_SEL_L);
			writel(0xffff0000, VCCIO1_IOC_BASE + GPIO1A_IOMUX_SEL_H);
			writel(0xf0f00000, VCCIO1_IOC_BASE + GPIO1B_IOMUX_SEL_L);
		} else if (devnum == 1) {
			writel(0xffff0000, VCCIO2_IOC_BASE + GPIO2A_IOMUX_SEL_L);
			writel(0x00ff0000, VCCIO2_IOC_BASE + GPIO2A_IOMUX_SEL_H);
			writel(0x00f00000, PMUIO0_IOC_BASE + GPIO0A_IOMUX_SEL_H);
			/* Pull down */
			writel(0x0cff0000, VCCIO2_IOC_BASE + GPIO2A_PULL);
		} else if (devnum == 2) {
			writel(0xffff0000, VCCIO3_IOC_BASE + GPIO3A_IOMUX_SEL_L);
			writel(0x00ff0000, VCCIO3_IOC_BASE + GPIO3A_IOMUX_SEL_H);
			writel(0x0f000000, VCCIO3_IOC_BASE + GPIO3B_IOMUX_SEL_H);
			/* Pull down */
			writel(0x0ffc0000, VCCIO2_IOC_BASE + GPIO3A_PULL);
		}
		break;
	case IF_TYPE_MTD:
		if (routing == 0) {
			/* FSPI0 M0 */
			writel(0x0f0f0000, VCCIO1_IOC_BASE + GPIO1B_IOMUX_SEL_L);
			writel(0xffff0000, VCCIO1_IOC_BASE + GPIO1B_IOMUX_SEL_H);
			writel(0x00f00000, VCCIO1_IOC_BASE + GPIO1A_IOMUX_SEL_H);
		} else if (routing == 1) {
			/* FSPI1 M0 */
			writel(0x0fff0000, PMUIO0_IOC_BASE + GPIO0B_IOMUX_SEL_L);
			writel(0xff000000, PMUIO0_IOC_BASE + GPIO0A_IOMUX_SEL_H);
			writel(0x00f00000, PMUIO0_IOC_BASE + GPIO0A_IOMUX_SEL_L);
		} else if (routing == 2) {
			/* FSPI1 M1 */
			writel(0xffff0000, VCCIO1_IOC_BASE + GPIO1A_IOMUX_SEL_L);
			writel(0xf0f00000, VCCIO1_IOC_BASE + GPIO1B_IOMUX_SEL_L);
		}
		break;
	default:
		break;
	}
}

#ifndef CONFIG_TPL_BUILD
int arch_cpu_init(void)
{
#if defined(CONFIG_SPL_BUILD) || defined(CONFIG_SUPPORT_USBPLUG)
	/* Set emmc master secure */
	writel(0x10000, SGRF_SYS_BASE + SGRF_SYS_AHB_SECURE_SGRF_CON);
	/* Set fspi master secure */
	writel(0x20000, SGRF_SYS_BASE + SGRF_SYS_AHB_SECURE_SGRF_CON);
	/* Set sdmmc0 master secure */
	writel(0x40000, SGRF_SYS_BASE + SGRF_SYS_AHB_SECURE_SGRF_CON);
	/* Set sdmmc1 master secure */
	writel(0x80000, SGRF_SYS_BASE + SGRF_SYS_AHB_SECURE_SGRF_CON);
	/* Set rkce master secure */
	writel(0x80030000, SGRF_SYS_BASE + SGRF_SYS_AXI_SECURE_SGRF_CON0);
	/* Set decom master secure */
	writel(0xC00000, SGRF_SYS_BASE + SGRF_SYS_AXI_SECURE_SGRF_CON0);

	/* Set all devices slave non-secure */
	writel(0xffff0000, SGRF_SYS_BASE + FIREWALL_SLV_CON0);
	writel(0xffff0000, SGRF_SYS_BASE + FIREWALL_SLV_CON1);
	writel(0xffff0000, SGRF_SYS_BASE + FIREWALL_SLV_CON2);
	writel(0xffff0000, SGRF_SYS_BASE + FIREWALL_SLV_CON3);
	writel(0xffff0000, SGRF_SYS_BASE + FIREWALL_SLV_CON4);
	writel(0xffff0000, SGRF_SYS_BASE + FIREWALL_SLV_CON5);
	/* Set OTP to none secure mode */
	writel(0x00020000, SGRF_SYS_BASE + OTP_SGRF_CON);
#endif

#if defined(CONFIG_ROCKCHIP_EMMC_IOMUX)
	board_set_iomux(IF_TYPE_MMC, 0, 0);
#elif defined(CONFIG_ROCKCHIP_SFC_IOMUX)
	/*
	 * (IF_TYPE_MTD, 0, 0) FSPI0
	 * (IF_TYPE_MTD, 1, 0) FSPI1 M0
	 * (IF_TYPE_MTD, 2, 0) FSPI1 M1
	 */
	board_set_iomux(IF_TYPE_MTD, 0, 0);
#endif /* CONFIG_ROCKCHIP_EMMC_IOMUX */

#if defined(CONFIG_MMC_DW_ROCKCHIP)
	/* Set the sdmmc iomux and power cycle */
	board_set_iomux(IF_TYPE_MMC, 1, 0);
	/* Enable force_jtag */
	writel(0x00080008, PMUIO0_IOC_BASE + GRF_JTAG_CON0);
#endif

	return 0;
}
#endif

#if defined(CONFIG_ROCKCHIP_EMMC_IOMUX) && defined(CONFIG_ROCKCHIP_SFC_IOMUX)
#error FSPI0 M0 and eMMC iomux is incompatible for rv1126b Soc. You should close one of them.
#endif
