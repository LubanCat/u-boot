/*
 * Copyright (c) 2024 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <dm.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/hardware.h>
#include <asm/arch/grf_rk3506.h>
#include <asm/arch/ioc_rk3506.h>

DECLARE_GLOBAL_DATA_PTR;

#define FIREWALL_DDR_BASE	0xff5f0000
#define FW_DDR_MST1_REG 	0x24

#define GPIO0_IOC_BASE		0xff950000
#define GPIO1_IOC_BASE		0xff660000

#define GPIO2_IOC_BASE		0xff4d8000
#define GPIO2A_IOMUX_SEL_0	0x40
#define GPIO2A_IOMUX_SEL_1	0x44

#define GPIO3_IOC_BASE	GPIO2_IOC_BASE
#define GPIO3A_IOMUX_SEL_0	0x60
#define GPIO3A_IOMUX_SEL_1	0x64

#define CRU_BASE		0xff9a0000
#define CRU_GLB_RST_CON		0xc10

void board_debug_uart_init(void)
{
	/* No need to change uart*/
}

#ifdef CONFIG_SPL_BUILD
void rockchip_stimer_init(void)
{
	/* If Timer already enabled, don't re-init it */
	u32 reg = readl(CONFIG_ROCKCHIP_STIMER_BASE + 0x4);
	if (reg & 0x1)
		return;
	writel(0x00010000, CONFIG_ROCKCHIP_STIMER_BASE + 0x4);

	asm volatile("mcr p15, 0, %0, c14, c0, 0"
		     : : "r"(COUNTER_FREQUENCY));
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE + 0x14);
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE + 0x18);
	writel(0x00010001, CONFIG_ROCKCHIP_STIMER_BASE + 0x4);
}
#endif

void board_set_iomux(enum if_type if_type, int devnum, int routing)
{
	switch (if_type) {
	case IF_TYPE_MMC:
		if (devnum == 0) {
			writel(0xffff1111, GPIO3_IOC_BASE + GPIO3A_IOMUX_SEL_0);
			writel(0x00ff0011, GPIO3_IOC_BASE + GPIO3A_IOMUX_SEL_1);
		}
		break;
	case IF_TYPE_MTD:
		if (routing == 0) {
			/* FSPI M0 */
			writel(0xffff1111, GPIO2_IOC_BASE + GPIO2A_IOMUX_SEL_0);
			writel(0x00ff0011, GPIO2_IOC_BASE + GPIO2A_IOMUX_SEL_1);
		}
		break;
	default:
		break;
	}
}

int arch_cpu_init(void)
{
#if defined(CONFIG_SPL_BUILD)
	u32 val;

	/* Set the sdmmc/emmc to access ddr memory */
	val = readl(FIREWALL_DDR_BASE + FW_DDR_MST1_REG);
	writel(val & 0xffff00ff, FIREWALL_DDR_BASE + FW_DDR_MST1_REG);

	/* Set the sdmmc/emmc iomux */
	board_set_iomux(IF_TYPE_MMC, 0, 0);

	/* Set the fspi to access ddr memory */
	val = readl(FIREWALL_DDR_BASE + FW_DDR_MST1_REG);
	writel(val & 0xff00ffff, FIREWALL_DDR_BASE + FW_DDR_MST1_REG);

	/* Set the fspi iomux */
	board_set_iomux(IF_TYPE_MTD, 0, 0);

	/*
	 * Wdt0 and WDT1 trigger global reset enable.
	 * Wdt0 and WDT1 trigger first global reset.
	 */
	writel(0x18c0, CRU_BASE + CRU_GLB_RST_CON);
#endif
	return 0;
}
