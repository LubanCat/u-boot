/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2017 Microsemi Corporation.
 * Padmarao Begari, Microsemi Corporation <padmarao.begari@microsemi.com>
 */

#ifndef RISCV_CSR_ENCODING_H
#define RISCV_CSR_ENCODING_H

#ifdef CONFIG_RISCV_SMODE
#define MODE_PREFIX(__suffix)	s##__suffix
#else
#define MODE_PREFIX(__suffix)	m##__suffix
#endif

#define MSTATUS_UIE	0x00000001
#define MSTATUS_SIE	0x00000002
#define MSTATUS_HIE	0x00000004
#define MSTATUS_MIE	0x00000008
#define MSTATUS_UPIE	0x00000010
#define MSTATUS_SPIE	0x00000020
#define MSTATUS_HPIE	0x00000040
#define MSTATUS_MPIE	0x00000080
#define MSTATUS_SPP	0x00000100
#define MSTATUS_HPP	0x00000600
#define MSTATUS_MPP	0x00001800
#define MSTATUS_FS	0x00006000
#define MSTATUS_XS	0x00018000
#define MSTATUS_MPRV	0x00020000
#define MSTATUS_PUM	0x00040000
#define MSTATUS_VM	0x1F000000
#define MSTATUS32_SD	0x80000000
#define MSTATUS64_SD	0x8000000000000000

#define MCAUSE32_CAUSE	0x7FFFFFFF
#define MCAUSE64_CAUSE	0x7FFFFFFFFFFFFFFF
#define MCAUSE32_INT	0x80000000
#define MCAUSE64_INT	0x8000000000000000

#define SSTATUS_UIE	0x00000001
#define SSTATUS_SIE	0x00000002
#define SSTATUS_UPIE	0x00000010
#define SSTATUS_SPIE	0x00000020
#define SSTATUS_SPP	0x00000100
#define SSTATUS_FS	0x00006000
#define SSTATUS_XS	0x00018000
#define SSTATUS_PUM	0x00040000
#define SSTATUS32_SD	0x80000000
#define SSTATUS64_SD	0x8000000000000000

#define MIP_SSIP	BIT(IRQ_S_SOFT)
#define MIP_HSIP	BIT(IRQ_H_SOFT)
#define MIP_MSIP	BIT(IRQ_M_SOFT)
#define MIP_STIP	BIT(IRQ_S_TIMER)
#define MIP_HTIP	BIT(IRQ_H_TIMER)
#define MIP_MTIP	BIT(IRQ_M_TIMER)
#define MIP_SEIP	BIT(IRQ_S_EXT)
#define MIP_HEIP	BIT(IRQ_H_EXT)
#define MIP_MEIP	BIT(IRQ_M_EXT)

#define SIP_SSIP	MIP_SSIP
#define SIP_STIP	MIP_STIP

#define PRV_U	0
#define PRV_S	1
#define PRV_H	2
#define PRV_M	3

#define VM_MBARE	0
#define VM_MBB		1
#define VM_MBBID	2
#define VM_SV32		8
#define VM_SV39		9
#define VM_SV48		10

#define IRQ_S_SOFT	1
#define IRQ_H_SOFT	2
#define IRQ_M_SOFT	3
#define IRQ_S_TIMER	5
#define IRQ_H_TIMER	6
#define IRQ_M_TIMER	7
#define IRQ_S_EXT	9
#define IRQ_H_EXT	10
#define IRQ_M_EXT	11
#define IRQ_COP		12
#define IRQ_HOST	13

#define CAUSE_MISALIGNED_FETCH		0
#define CAUSE_FETCH_ACCESS		1
#define CAUSE_ILLEGAL_INSTRUCTION	2
#define CAUSE_BREAKPOINT		3
#define CAUSE_MISALIGNED_LOAD		4
#define CAUSE_LOAD_ACCESS		5
#define CAUSE_MISALIGNED_STORE		6
#define CAUSE_STORE_ACCESS		7
#define CAUSE_USER_ECALL		8
#define CAUSE_SUPERVISOR_ECALL		9
#define CAUSE_MACHINE_ECALL		11
#define CAUSE_FETCH_PAGE_FAULT		12
#define CAUSE_LOAD_PAGE_FAULT		13
#define CAUSE_STORE_PAGE_FAULT		15

#define DEFAULT_RSTVEC		0x00001000
#define DEFAULT_NMIVEC		0x00001004
#define DEFAULT_MTVEC		0x00001010
#define CONFIG_STRING_ADDR	0x0000100C
#define EXT_IO_BASE		0x40000000
#define DRAM_BASE		0x80000000

// page table entry (PTE) fields
#define PTE_V		0x001 // Valid
#define PTE_TYPE	0x01E // Type
#define PTE_R		0x020 // Referenced
#define PTE_D		0x040 // Dirty
#define PTE_SOFT	0x380 // Reserved for Software

#define PTE_TYPE_TABLE		0x00
#define PTE_TYPE_TABLE_GLOBAL	0x02
#define PTE_TYPE_URX_SR		0x04
#define PTE_TYPE_URWX_SRW	0x06
#define PTE_TYPE_UR_SR		0x08
#define PTE_TYPE_URW_SRW	0x0A
#define PTE_TYPE_URX_SRX	0x0C
#define PTE_TYPE_URWX_SRWX0x0E
#define PTE_TYPE_SR		0x10
#define PTE_TYPE_SRW		0x12
#define PTE_TYPE_SRX		0x14
#define PTE_TYPE_SRWX		0x16
#define PTE_TYPE_SR_GLOBAL	0x18
#define PTE_TYPE_SRW_GLOBAL	0x1A
#define PTE_TYPE_SRX_GLOBAL	0x1C
#define PTE_TYPE_SRWX_GLOBAL	0x1E

#define PTE_PPN_SHIFT	10

#define PTE_TABLE(PTE)	((0x0000000AU >> ((PTE) & 0x1F)) & 1)
#define PTE_UR(PTE)	((0x0000AAA0U >> ((PTE) & 0x1F)) & 1)
#define PTE_UW(PTE)	((0x00008880U >> ((PTE) & 0x1F)) & 1)
#define PTE_UX(PTE)	((0x0000A0A0U >> ((PTE) & 0x1F)) & 1)
#define PTE_SR(PTE)	((0xAAAAAAA0U >> ((PTE) & 0x1F)) & 1)
#define PTE_SW(PTE)	((0x88888880U >> ((PTE) & 0x1F)) & 1)
#define PTE_SX(PTE)	((0xA0A0A000U >> ((PTE) & 0x1F)) & 1)

#define PTE_CHECK_PERM(_PTE, _SUPERVISOR, STORE, FETCH) \
	typeof(_PTE) (PTE) = (_PTE); \
	typeof(_SUPERVISOR) (SUPERVISOR) = (_SUPERVISOR); \
	((STORE) ? ((SUPERVISOR) ? PTE_SW(PTE) : PTE_UW(PTE)) : \
	(FETCH) ? ((SUPERVISOR) ? PTE_SX(PTE) : PTE_UX(PTE)) : \
	((SUPERVISOR) ? PTE_SR(PTE) : PTE_UR(PTE)))

#ifdef __riscv

#ifdef CONFIG_64BIT
# define MSTATUS_SD MSTATUS64_SD
# define SSTATUS_SD SSTATUS64_SD
# define MCAUSE_INT MCAUSE64_INT
# define MCAUSE_CAUSE MCAUSE64_CAUSE
# define RISCV_PGLEVEL_BITS 9
#else
# define MSTATUS_SD MSTATUS32_SD
# define SSTATUS_SD SSTATUS32_SD
# define RISCV_PGLEVEL_BITS 10
# define MCAUSE_INT MCAUSE32_INT
# define MCAUSE_CAUSE MCAUSE32_CAUSE
#endif

#define RISCV_PGSHIFT 12
#define RISCV_PGSIZE BIT(RISCV_PGSHIFT)

/* CSR numbers */
#define CSR_FFLAGS		0x1
#define CSR_FRM			0x2
#define CSR_FCSR		0x3

#define CSR_SSTATUS		0x100
#define CSR_SEDELEG		0x102
#define CSR_SIDELEG		0x103
#define CSR_SIE			0x104
#define CSR_STVEC		0x105
#define CSR_SCOUNTEREN		0x106
#define CSR_SSCRATCH		0x140
#define CSR_SEPC		0x141
#define CSR_SCAUSE		0x142
#define CSR_STVAL		0x143
#define CSR_SIP			0x144
#define CSR_SATP		0x180

#define CSR_MSTATUS		0x300
#define CSR_MISA		0x301
#define CSR_MEDELEG		0x302
#define CSR_MIDELEG		0x303
#define CSR_MIE			0x304
#define CSR_MTVEC		0x305
#define CSR_MCOUNTEREN		0x306
#define CSR_MHPMEVENT3		0x323
#define CSR_MHPMEVENT4		0x324
#define CSR_MHPMEVENT5		0x325
#define CSR_MHPMEVENT6		0x326
#define CSR_MHPMEVENT7		0x327
#define CSR_MHPMEVENT8		0x328
#define CSR_MHPMEVENT9		0x329
#define CSR_MHPMEVENT10		0x32a
#define CSR_MHPMEVENT11		0x32b
#define CSR_MHPMEVENT12		0x32c
#define CSR_MHPMEVENT13		0x32d
#define CSR_MHPMEVENT14		0x32e
#define CSR_MHPMEVENT15		0x32f
#define CSR_MHPMEVENT16		0x330
#define CSR_MHPMEVENT17		0x331
#define CSR_MHPMEVENT18		0x332
#define CSR_MHPMEVENT19		0x333
#define CSR_MHPMEVENT20		0x334
#define CSR_MHPMEVENT21		0x335
#define CSR_MHPMEVENT22		0x336
#define CSR_MHPMEVENT23		0x337
#define CSR_MHPMEVENT24		0x338
#define CSR_MHPMEVENT25		0x339
#define CSR_MHPMEVENT26		0x33a
#define CSR_MHPMEVENT27		0x33b
#define CSR_MHPMEVENT28		0x33c
#define CSR_MHPMEVENT29		0x33d
#define CSR_MHPMEVENT30		0x33e
#define CSR_MHPMEVENT31		0x33f
#define CSR_MSCRATCH		0x340
#define CSR_MEPC		0x341
#define CSR_MCAUSE		0x342
#define CSR_MTVAL		0x343
#define CSR_MIP			0x344
#define CSR_PMPCFG0		0x3a0
#define CSR_PMPCFG1		0x3a1
#define CSR_PMPCFG2		0x3a2
#define CSR_PMPCFG3		0x3a3
#define CSR_PMPADDR0		0x3b0
#define CSR_PMPADDR1		0x3b1
#define CSR_PMPADDR2		0x3b2
#define CSR_PMPADDR3		0x3b3
#define CSR_PMPADDR4		0x3b4
#define CSR_PMPADDR5		0x3b5
#define CSR_PMPADDR6		0x3b6
#define CSR_PMPADDR7		0x3b7
#define CSR_PMPADDR8		0x3b8
#define CSR_PMPADDR9		0x3b9
#define CSR_PMPADDR10		0x3ba
#define CSR_PMPADDR11		0x3bb
#define CSR_PMPADDR12		0x3bc
#define CSR_PMPADDR13		0x3bd
#define CSR_PMPADDR14		0x3be
#define CSR_PMPADDR15		0x3bf

#define CSR_TSELECT		0x7a0
#define CSR_TDATA1		0x7a1
#define CSR_TDATA2		0x7a2
#define CSR_TDATA3		0x7a3
#define CSR_DCSR		0x7b0
#define CSR_DPC			0x7b1
#define CSR_DSCRATCH		0x7b2

#define CSR_MCYCLE		0xb00
#define CSR_MINSTRET		0xb02
#define CSR_MHPMCOUNTER3	0xb03
#define CSR_MHPMCOUNTER4	0xb04
#define CSR_MHPMCOUNTER5	0xb05
#define CSR_MHPMCOUNTER6	0xb06
#define CSR_MHPMCOUNTER7	0xb07
#define CSR_MHPMCOUNTER8	0xb08
#define CSR_MHPMCOUNTER9	0xb09
#define CSR_MHPMCOUNTER10	0xb0a
#define CSR_MHPMCOUNTER11	0xb0b
#define CSR_MHPMCOUNTER12	0xb0c
#define CSR_MHPMCOUNTER13	0xb0d
#define CSR_MHPMCOUNTER14	0xb0e
#define CSR_MHPMCOUNTER15	0xb0f
#define CSR_MHPMCOUNTER16	0xb10
#define CSR_MHPMCOUNTER17	0xb11
#define CSR_MHPMCOUNTER18	0xb12
#define CSR_MHPMCOUNTER19	0xb13
#define CSR_MHPMCOUNTER20	0xb14
#define CSR_MHPMCOUNTER21	0xb15
#define CSR_MHPMCOUNTER22	0xb16
#define CSR_MHPMCOUNTER23	0xb17
#define CSR_MHPMCOUNTER24	0xb18
#define CSR_MHPMCOUNTER25	0xb19
#define CSR_MHPMCOUNTER26	0xb1a
#define CSR_MHPMCOUNTER27	0xb1b
#define CSR_MHPMCOUNTER28	0xb1c
#define CSR_MHPMCOUNTER29	0xb1d
#define CSR_MHPMCOUNTER30	0xb1e
#define CSR_MHPMCOUNTER31	0xb1f
#define CSR_MCYCLEH		0xb80
#define CSR_MINSTRETH		0xb82
#define CSR_MHPMCOUNTER3H	0xb83
#define CSR_MHPMCOUNTER4H	0xb84
#define CSR_MHPMCOUNTER5H	0xb85
#define CSR_MHPMCOUNTER6H	0xb86
#define CSR_MHPMCOUNTER7H	0xb87
#define CSR_MHPMCOUNTER8H	0xb88
#define CSR_MHPMCOUNTER9H	0xb89
#define CSR_MHPMCOUNTER10H	0xb8a
#define CSR_MHPMCOUNTER11H	0xb8b
#define CSR_MHPMCOUNTER12H	0xb8c
#define CSR_MHPMCOUNTER13H	0xb8d
#define CSR_MHPMCOUNTER14H	0xb8e
#define CSR_MHPMCOUNTER15H	0xb8f
#define CSR_MHPMCOUNTER16H	0xb90
#define CSR_MHPMCOUNTER17H	0xb91
#define CSR_MHPMCOUNTER18H	0xb92
#define CSR_MHPMCOUNTER19H	0xb93
#define CSR_MHPMCOUNTER20H	0xb94
#define CSR_MHPMCOUNTER21H	0xb95
#define CSR_MHPMCOUNTER22H	0xb96
#define CSR_MHPMCOUNTER23H	0xb97
#define CSR_MHPMCOUNTER24H	0xb98
#define CSR_MHPMCOUNTER25H	0xb99
#define CSR_MHPMCOUNTER26H	0xb9a
#define CSR_MHPMCOUNTER27H	0xb9b
#define CSR_MHPMCOUNTER28H	0xb9c
#define CSR_MHPMCOUNTER29H	0xb9d
#define CSR_MHPMCOUNTER30H	0xb9e
#define CSR_MHPMCOUNTER31H	0xb9f

#define CSR_CYCLE		0xc00
#define CSR_TIME		0xc01
#define CSR_INSTRET		0xc02
#define CSR_HPMCOUNTER3		0xc03
#define CSR_HPMCOUNTER4		0xc04
#define CSR_HPMCOUNTER5		0xc05
#define CSR_HPMCOUNTER6		0xc06
#define CSR_HPMCOUNTER7		0xc07
#define CSR_HPMCOUNTER8		0xc08
#define CSR_HPMCOUNTER9		0xc09
#define CSR_HPMCOUNTER10	0xc0a
#define CSR_HPMCOUNTER11	0xc0b
#define CSR_HPMCOUNTER12	0xc0c
#define CSR_HPMCOUNTER13	0xc0d
#define CSR_HPMCOUNTER14	0xc0e
#define CSR_HPMCOUNTER15	0xc0f
#define CSR_HPMCOUNTER16	0xc10
#define CSR_HPMCOUNTER17	0xc11
#define CSR_HPMCOUNTER18	0xc12
#define CSR_HPMCOUNTER19	0xc13
#define CSR_HPMCOUNTER20	0xc14
#define CSR_HPMCOUNTER21	0xc15
#define CSR_HPMCOUNTER22	0xc16
#define CSR_HPMCOUNTER23	0xc17
#define CSR_HPMCOUNTER24	0xc18
#define CSR_HPMCOUNTER25	0xc19
#define CSR_HPMCOUNTER26	0xc1a
#define CSR_HPMCOUNTER27	0xc1b
#define CSR_HPMCOUNTER28	0xc1c
#define CSR_HPMCOUNTER29	0xc1d
#define CSR_HPMCOUNTER30	0xc1e
#define CSR_HPMCOUNTER31	0xc1f
#define CSR_CYCLEH		0xc80
#define CSR_TIMEH		0xc81
#define CSR_INSTRETH		0xc82
#define CSR_HPMCOUNTER3H	0xc83
#define CSR_HPMCOUNTER4H	0xc84
#define CSR_HPMCOUNTER5H	0xc85
#define CSR_HPMCOUNTER6H	0xc86
#define CSR_HPMCOUNTER7H	0xc87
#define CSR_HPMCOUNTER8H	0xc88
#define CSR_HPMCOUNTER9H	0xc89
#define CSR_HPMCOUNTER10H	0xc8a
#define CSR_HPMCOUNTER11H	0xc8b
#define CSR_HPMCOUNTER12H	0xc8c
#define CSR_HPMCOUNTER13H	0xc8d
#define CSR_HPMCOUNTER14H	0xc8e
#define CSR_HPMCOUNTER15H	0xc8f
#define CSR_HPMCOUNTER16H	0xc90
#define CSR_HPMCOUNTER17H	0xc91
#define CSR_HPMCOUNTER18H	0xc92
#define CSR_HPMCOUNTER19H	0xc93
#define CSR_HPMCOUNTER20H	0xc94
#define CSR_HPMCOUNTER21H	0xc95
#define CSR_HPMCOUNTER22H	0xc96
#define CSR_HPMCOUNTER23H	0xc97
#define CSR_HPMCOUNTER24H	0xc98
#define CSR_HPMCOUNTER25H	0xc99
#define CSR_HPMCOUNTER26H	0xc9a
#define CSR_HPMCOUNTER27H	0xc9b
#define CSR_HPMCOUNTER28H	0xc9c
#define CSR_HPMCOUNTER29H	0xc9d
#define CSR_HPMCOUNTER30H	0xc9e
#define CSR_HPMCOUNTER31H	0xc9f

#define CSR_MVENDORID		0xf11
#define CSR_MARCHID		0xf12
#define CSR_MIMPID		0xf13
#define CSR_MHARTID		0xf14

#endif /* __riscv */

#endif /* RISCV_CSR_ENCODING_H */