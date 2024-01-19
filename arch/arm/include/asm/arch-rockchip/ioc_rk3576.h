/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#ifndef _ASM_ARCH_IOC_RK3576_H
#define _ASM_ARCH_IOC_RK3576_H

#include <common.h>

/* pmu0_ioc register structure define */
struct rk3576_pmu0_ioc_reg {
     uint32_t gpio0a_iomux_sel_l;                 /* address offset: 0x0000 */
     uint32_t gpio0a_iomux_sel_h;                 /* address offset: 0x0004 */
     uint32_t gpio0b_iomux_sel_l;                 /* address offset: 0x0008 */
     uint32_t reserved000c;                       /* address offset: 0x000c */
     uint32_t gpio0a_ds_l;                        /* address offset: 0x0010 */
     uint32_t gpio0a_ds_h;                        /* address offset: 0x0014 */
     uint32_t gpio0b_ds_l;                        /* address offset: 0x0018 */
     uint32_t reserved001c;                       /* address offset: 0x001c */
     uint32_t gpio0a_pull;                        /* address offset: 0x0020 */
     uint32_t gpio0b_pull_l;                      /* address offset: 0x0024 */
     uint32_t gpio0a_ie;                          /* address offset: 0x0028 */
     uint32_t gpio0b_ie_l;                        /* address offset: 0x002c */
     uint32_t gpio0a_smt;                         /* address offset: 0x0030 */
     uint32_t gpio0b_smt_l;                       /* address offset: 0x0034 */
     uint32_t gpio0a_pdis;                        /* address offset: 0x0038 */
     uint32_t gpio0b_pdis_l;                      /* address offset: 0x003c */
     uint32_t osc_con;                            /* address offset: 0x0040 */
};

check_member(rk3576_pmu0_ioc_reg, osc_con, 0x0040);

/* pmu1_ioc register structure define */
struct rk3576_pmu1_ioc_reg {
     uint32_t gpio0b_iomux_sel_h;                 /* address offset: 0x0000 */
     uint32_t gpio0c_iomux_sel_l;                 /* address offset: 0x0004 */
     uint32_t gpio0c_iomux_sel_h;                 /* address offset: 0x0008 */
     uint32_t gpio0d_iomux_sel_l;                 /* address offset: 0x000c */
     uint32_t gpio0d_iomux_sel_h;                 /* address offset: 0x0010 */
     uint32_t gpio0b_ds_h;                        /* address offset: 0x0014 */
     uint32_t gpio0c_ds_l;                        /* address offset: 0x0018 */
     uint32_t gpio0c_ds_h;                        /* address offset: 0x001c */
     uint32_t gpio0d_ds_l;                        /* address offset: 0x0020 */
     uint32_t gpio0d_ds_h;                        /* address offset: 0x0024 */
     uint32_t gpio0b_pull_h;                      /* address offset: 0x0028 */
     uint32_t gpio0c_pull;                        /* address offset: 0x002c */
     uint32_t gpio0d_pull;                        /* address offset: 0x0030 */
     uint32_t gpio0b_ie_h;                        /* address offset: 0x0034 */
     uint32_t gpio0c_ie;                          /* address offset: 0x0038 */
     uint32_t gpio0d_ie;                          /* address offset: 0x003c */
     uint32_t gpio0b_smt_h;                       /* address offset: 0x0040 */
     uint32_t gpio0c_smt;                         /* address offset: 0x0044 */
     uint32_t gpio0d_smt;                         /* address offset: 0x0048 */
     uint32_t gpio0b_pdis_h;                      /* address offset: 0x004c */
     uint32_t gpio0c_pdis;                        /* address offset: 0x0050 */
     uint32_t gpio0d_pdis;                        /* address offset: 0x0054 */
};

check_member(rk3576_pmu1_ioc_reg, gpio0d_pdis, 0x0054);

/* top_ioc register structure define */
struct rk3576_top_ioc_reg {
     uint32_t reserved0000[2];                    /* address offset: 0x0000 */
     uint32_t gpio0b_iomux_sel_l;                 /* address offset: 0x0008 */
     uint32_t gpio0b_iomux_sel_h;                 /* address offset: 0x000c */
     uint32_t gpio0c_iomux_sel_l;                 /* address offset: 0x0010 */
     uint32_t gpio0c_iomux_sel_h;                 /* address offset: 0x0014 */
     uint32_t gpio0d_iomux_sel_l;                 /* address offset: 0x0018 */
     uint32_t gpio0d_iomux_sel_h;                 /* address offset: 0x001c */
     uint32_t gpio1a_iomux_sel_l;                 /* address offset: 0x0020 */
     uint32_t gpio1a_iomux_sel_h;                 /* address offset: 0x0024 */
     uint32_t gpio1b_iomux_sel_l;                 /* address offset: 0x0028 */
     uint32_t gpio1b_iomux_sel_h;                 /* address offset: 0x002c */
     uint32_t gpio1c_iomux_sel_l;                 /* address offset: 0x0030 */
     uint32_t gpio1c_iomux_sel_h;                 /* address offset: 0x0034 */
     uint32_t gpio1d_iomux_sel_l;                 /* address offset: 0x0038 */
     uint32_t gpio1d_iomux_sel_h;                 /* address offset: 0x003c */
     uint32_t gpio2a_iomux_sel_l;                 /* address offset: 0x0040 */
     uint32_t gpio2a_iomux_sel_h;                 /* address offset: 0x0044 */
     uint32_t gpio2b_iomux_sel_l;                 /* address offset: 0x0048 */
     uint32_t gpio2b_iomux_sel_h;                 /* address offset: 0x004c */
     uint32_t gpio2c_iomux_sel_l;                 /* address offset: 0x0050 */
     uint32_t gpio2c_iomux_sel_h;                 /* address offset: 0x0054 */
     uint32_t gpio2d_iomux_sel_l;                 /* address offset: 0x0058 */
     uint32_t gpio2d_iomux_sel_h;                 /* address offset: 0x005c */
     uint32_t gpio3a_iomux_sel_l;                 /* address offset: 0x0060 */
     uint32_t gpio3a_iomux_sel_h;                 /* address offset: 0x0064 */
     uint32_t gpio3b_iomux_sel_l;                 /* address offset: 0x0068 */
     uint32_t gpio3b_iomux_sel_h;                 /* address offset: 0x006c */
     uint32_t gpio3c_iomux_sel_l;                 /* address offset: 0x0070 */
     uint32_t gpio3c_iomux_sel_h;                 /* address offset: 0x0074 */
     uint32_t gpio3d_iomux_sel_l;                 /* address offset: 0x0078 */
     uint32_t gpio3d_iomux_sel_h;                 /* address offset: 0x007c */
     uint32_t gpio4a_iomux_sel_l;                 /* address offset: 0x0080 */
     uint32_t gpio4a_iomux_sel_h;                 /* address offset: 0x0084 */
     uint32_t gpio4b_iomux_sel_l;                 /* address offset: 0x0088 */
     uint32_t gpio4b_iomux_sel_h;                 /* address offset: 0x008c */
     uint32_t reserved0090[24];                   /* address offset: 0x0090 */
     uint32_t ioc_misc_con;                       /* address offset: 0x00f0 */
     uint32_t sdmmc_detn_flt;                     /* address offset: 0x00f4 */
};

check_member(rk3576_top_ioc_reg, sdmmc_detn_flt, 0x00f4);

#endif /* _ASM_ARCH_IOC_RK3576_H */