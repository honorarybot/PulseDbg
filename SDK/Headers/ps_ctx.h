#include <stdint.h>

#pragma once

typedef enum _PS_CPU_MODE
{
	cmReal = 0,
	cmSmm = 1,
	cmV86 = 2,
	cmProt32 = 3,
	cmProt16 = 4,
	cmLong64 = 5,
	cmLong32 = 6,
	cmLong16 = 7
} PS_CPU_MODE;

typedef struct _PS_CTX
{
	// Location
	uint64_t rip;
	// Space
	uint64_t cr3;
	// Stack
	uint64_t rsp;
	// Gpr
	uint64_t rax;
	uint64_t rbx;
	uint64_t rcx;
	uint64_t rdx;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rbp;
	uint64_t rflags;
	uint64_t r8;
	uint64_t r9;
	uint64_t r10;
	uint64_t r11;
	uint64_t r12;
	uint64_t r13;
	uint64_t r14;
	uint64_t r15;
	// Segment
	uint16_t cs;
	uint32_t cs_access;
	uint64_t cs_base;
	uint32_t cs_limit;
	uint16_t ds;
	uint32_t ds_access;
	uint64_t ds_base;
	uint32_t ds_limit;
	uint16_t ss;
	uint32_t ss_access;
	uint64_t ss_base;
	uint32_t ss_limit;
	uint16_t es;
	uint32_t es_access;
	uint64_t es_base;
	uint32_t es_limit;
	uint16_t fs;
	uint32_t fs_access;
	uint64_t fs_base;
	uint32_t fs_limit;
	uint16_t gs;
	uint32_t gs_access;
	uint64_t gs_base;
	uint32_t gs_limit;
	// Control
	uint64_t cr0;
	uint64_t cr2;
	uint64_t cr4;
	uint64_t cr8;
	// Descriptor table
	uint64_t gdt_base;
	uint16_t gdt_limit;
	uint64_t idt_base;
	uint16_t idt_limit;
	// Descriptor
	uint16_t ldt;
	uint32_t ldt_access;
	uint64_t ldt_base;
	uint32_t ldt_limit;
	uint16_t tss;
	uint32_t tss_access;
	uint64_t tss_base;
	uint32_t tss_limit;
	// Debug
	uint64_t dr0;
	uint64_t dr1;
	uint64_t dr2;
	uint64_t dr3;
	uint64_t dr6;
	uint64_t dr7;
} PS_CTX, *PPS_CTX;

typedef struct _PS_CTX_EXT
{
	// Feature control
	uint64_t xcr0;
	// FPU
	uint16_t fpu_ctrl;
	uint16_t fpu_sts;
	uint16_t fpu_tag;
	uint16_t fpu_opcode;
	uint64_t fpu_ip;
	uint64_t fpu_op_offs;
	uint8_t  st0[10];
	uint8_t  st1[10];
	uint8_t  st2[10];
	uint8_t  st3[10];
	uint8_t  st4[10];
	uint8_t  st5[10];
	uint8_t  st6[10];
	uint8_t  st7[10];
	// MMX
	uint64_t mm0;
	uint64_t mm1;
	uint64_t mm2;
	uint64_t mm3;
	uint64_t mm4;
	uint64_t mm5;
	uint64_t mm6;
	uint64_t mm7;
	// XMM
	uint32_t mxcsr;
	uint32_t mxcsr_mask;
	uint8_t  xmm0[16];
	uint8_t  xmm1[16];
	uint8_t  xmm2[16];
	uint8_t  xmm3[16];
	uint8_t  xmm4[16];
	uint8_t  xmm5[16];
	uint8_t  xmm6[16];
	uint8_t  xmm7[16];
	uint8_t  xmm8[16];
	uint8_t  xmm9[16];
	uint8_t  xmm10[16];
	uint8_t  xmm11[16];
	uint8_t  xmm12[16];
	uint8_t  xmm13[16];
	uint8_t  xmm14[16];
	uint8_t  xmm15[16];
	// YMM (16 * 256 bit)
	uint8_t  ymm0[32];
	uint8_t  ymm1[32];
	uint8_t  ymm2[32];
	uint8_t  ymm3[32];
	uint8_t  ymm4[32];
	uint8_t  ymm5[32];
	uint8_t  ymm6[32];
	uint8_t  ymm7[32];
	uint8_t  ymm8[32];
	uint8_t  ymm9[32];
	uint8_t  ymm10[32];
	uint8_t  ymm11[32];
	uint8_t  ymm12[32];
	uint8_t  ymm13[32];
	uint8_t  ymm14[32];
	uint8_t  ymm15[32];
} PS_CTX_EXT, *PPS_CTX_EXT;

//
//  Partial context request mask
//

#define DBG_CTX_PART_FLAG_RIP           (1ULL << 0)
#define DBG_CTX_PART_FLAG_CR3           (1ULL << 1)
#define DBG_CTX_PART_FLAG_RSP           (1ULL << 2)
#define DBG_CTX_PART_FLAG_RAX           (1ULL << 3)
#define DBG_CTX_PART_FLAG_RBX           (1ULL << 4)
#define DBG_CTX_PART_FLAG_RCX           (1ULL << 5)
#define DBG_CTX_PART_FLAG_RDX           (1ULL << 6)
#define DBG_CTX_PART_FLAG_RSI           (1ULL << 7)
#define DBG_CTX_PART_FLAG_RDI           (1ULL << 8)
#define DBG_CTX_PART_FLAG_RBP           (1ULL << 9)
#define DBG_CTX_PART_FLAG_RFLAGS        (1ULL << 10)
#define DBG_CTX_PART_FLAG_R8            (1ULL << 11)
#define DBG_CTX_PART_FLAG_R9            (1ULL << 12)
#define DBG_CTX_PART_FLAG_R10           (1ULL << 13)
#define DBG_CTX_PART_FLAG_R11           (1ULL << 14)
#define DBG_CTX_PART_FLAG_R12           (1ULL << 15)
#define DBG_CTX_PART_FLAG_R13           (1ULL << 16)
#define DBG_CTX_PART_FLAG_R14           (1ULL << 17)
#define DBG_CTX_PART_FLAG_R15           (1ULL << 18)
#define DBG_CTX_PART_FLAG_CS            (1ULL << 19)
#define DBG_CTX_PART_FLAG_CS_ACCESS     (1ULL << 20)
#define DBG_CTX_PART_FLAG_CS_BASE       (1ULL << 21)
#define DBG_CTX_PART_FLAG_CS_LIMIT      (1ULL << 22)
#define DBG_CTX_PART_FLAG_DS            (1ULL << 23)
#define DBG_CTX_PART_FLAG_DS_ACCESS     (1ULL << 24)
#define DBG_CTX_PART_FLAG_DS_BASE       (1ULL << 25)
#define DBG_CTX_PART_FLAG_DS_LIMIT      (1ULL << 26)
#define DBG_CTX_PART_FLAG_SS            (1ULL << 27)
#define DBG_CTX_PART_FLAG_SS_ACCESS     (1ULL << 28)
#define DBG_CTX_PART_FLAG_SS_BASE       (1ULL << 29)
#define DBG_CTX_PART_FLAG_SS_LIMIT      (1ULL << 30)
#define DBG_CTX_PART_FLAG_ES            (1ULL << 31)
#define DBG_CTX_PART_FLAG_ES_ACCESS     (1ULL << 32)
#define DBG_CTX_PART_FLAG_ES_BASE       (1ULL << 33)
#define DBG_CTX_PART_FLAG_ES_LIMIT      (1ULL << 34)
#define DBG_CTX_PART_FLAG_FS            (1ULL << 35)
#define DBG_CTX_PART_FLAG_FS_ACCESS     (1ULL << 36)
#define DBG_CTX_PART_FLAG_FS_BASE       (1ULL << 37)
#define DBG_CTX_PART_FLAG_FS_LIMIT      (1ULL << 38)
#define DBG_CTX_PART_FLAG_GS            (1ULL << 39)
#define DBG_CTX_PART_FLAG_GS_ACCESS     (1ULL << 40)
#define DBG_CTX_PART_FLAG_GS_BASE       (1ULL << 41)
#define DBG_CTX_PART_FLAG_GS_LIMIT      (1ULL << 42)
#define DBG_CTX_PART_FLAG_CR0           (1ULL << 43)
#define DBG_CTX_PART_FLAG_CR2           (1ULL << 44)
#define DBG_CTX_PART_FLAG_CR4           (1ULL << 45)
#define DBG_CTX_PART_FLAG_CR8           (1ULL << 46)
#define DBG_CTX_PART_FLAG_GDT_BASE      (1ULL << 47)
#define DBG_CTX_PART_FLAG_GDT_LIMIT     (1ULL << 48)
#define DBG_CTX_PART_FLAG_IDT_BASE      (1ULL << 49)
#define DBG_CTX_PART_FLAG_IDT_LIMIT     (1ULL << 50)
#define DBG_CTX_PART_FLAG_LDT           (1ULL << 51)
#define DBG_CTX_PART_FLAG_LDT_ACCESS    (1ULL << 52)
#define DBG_CTX_PART_FLAG_LDT_BASE      (1ULL << 53)
#define DBG_CTX_PART_FLAG_LDT_LIMIT     (1ULL << 54)
#define DBG_CTX_PART_FLAG_TSS           (1ULL << 55)
#define DBG_CTX_PART_FLAG_TSS_ACCESS    (1ULL << 56)
#define DBG_CTX_PART_FLAG_TSS_BASE      (1ULL << 57)
#define DBG_CTX_PART_FLAG_TSS_LIMIT     (1ULL << 58)
#define DBG_CTX_PART_FLAG_DR0           (1ULL << 59)
#define DBG_CTX_PART_FLAG_DR1           (1ULL << 60)
#define DBG_CTX_PART_FLAG_DR2           (1ULL << 61)
#define DBG_CTX_PART_FLAG_DR3           (1ULL << 62)
#define DBG_CTX_PART_FLAG_DR6           (1ULL << 63)
#define DBG_CTX_PART_FLAG_DR7           (1ULL << 63)

//
//  Partial context request mask group aliases
//

#define DBG_CTX_PART_GPR_MASK           0x000000000007FFFD
#define DBG_CTX_PART_CTRL_MASK          0x0000780000000002
#define DBG_CTX_PART_SEG_MASK           0x000007FFFFF80000
#define DBG_CTX_PART_DESC_MASK          0x07FF800000000000
#define DBG_CTX_PART_DEBUG_MASK         0xF800000000000000
#define DBG_CTX_PART_FULL_MASK          0xFFFFFFFFFFFFFFFF

//
//  Partial extended context request mask
//

#define DBG_CTX_EX_PART_FLAG_XCR0       (1ULL << 0)
#define DBG_CTX_EX_PART_FLAG_FCW        (1ULL << 1)
#define DBG_CTX_EX_PART_FLAG_FSW        (1ULL << 2)
#define DBG_CTX_EX_PART_FLAG_FTW        (1ULL << 3)
#define DBG_CTX_EX_PART_FLAG_FOP        (1ULL << 4)
#define DBG_CTX_EX_PART_FLAG_FIP        (1ULL << 5)
#define DBG_CTX_EX_PART_FLAG_FDP        (1ULL << 6)
#define DBG_CTX_EX_PART_FLAG_ST0        (1ULL << 7)
#define DBG_CTX_EX_PART_FLAG_ST1        (1ULL << 8)
#define DBG_CTX_EX_PART_FLAG_ST2        (1ULL << 9)
#define DBG_CTX_EX_PART_FLAG_ST3        (1ULL << 10)
#define DBG_CTX_EX_PART_FLAG_ST4        (1ULL << 11)
#define DBG_CTX_EX_PART_FLAG_ST5        (1ULL << 12)
#define DBG_CTX_EX_PART_FLAG_ST6        (1ULL << 13)
#define DBG_CTX_EX_PART_FLAG_ST7        (1ULL << 14)
#define DBG_CTX_EX_PART_FLAG_MM0        (1ULL << 15)
#define DBG_CTX_EX_PART_FLAG_MM1        (1ULL << 16)
#define DBG_CTX_EX_PART_FLAG_MM2        (1ULL << 17)
#define DBG_CTX_EX_PART_FLAG_MM3        (1ULL << 18)
#define DBG_CTX_EX_PART_FLAG_MM4        (1ULL << 19)
#define DBG_CTX_EX_PART_FLAG_MM5        (1ULL << 20)
#define DBG_CTX_EX_PART_FLAG_MM6        (1ULL << 21)
#define DBG_CTX_EX_PART_FLAG_MM7        (1ULL << 22)
#define DBG_CTX_EX_PART_FLAG_MXCSR      (1ULL << 23)
#define DBG_CTX_EX_PART_FLAG_MXCSR_MASK (1ULL << 24)
#define DBG_CTX_EX_PART_FLAG_XMM0       (1ULL << 25)
#define DBG_CTX_EX_PART_FLAG_XMM1       (1ULL << 26)
#define DBG_CTX_EX_PART_FLAG_XMM2       (1ULL << 27)
#define DBG_CTX_EX_PART_FLAG_XMM3       (1ULL << 28)
#define DBG_CTX_EX_PART_FLAG_XMM4       (1ULL << 29)
#define DBG_CTX_EX_PART_FLAG_XMM5       (1ULL << 30)
#define DBG_CTX_EX_PART_FLAG_XMM6       (1ULL << 31)
#define DBG_CTX_EX_PART_FLAG_XMM7       (1ULL << 32)
#define DBG_CTX_EX_PART_FLAG_XMM8       (1ULL << 33)
#define DBG_CTX_EX_PART_FLAG_XMM9       (1ULL << 34)
#define DBG_CTX_EX_PART_FLAG_XMM10      (1ULL << 35)
#define DBG_CTX_EX_PART_FLAG_XMM11      (1ULL << 36)
#define DBG_CTX_EX_PART_FLAG_XMM12      (1ULL << 37)
#define DBG_CTX_EX_PART_FLAG_XMM13      (1ULL << 38)
#define DBG_CTX_EX_PART_FLAG_XMM14      (1ULL << 39)
#define DBG_CTX_EX_PART_FLAG_XMM15      (1ULL << 40)
#define DBG_CTX_EX_PART_FLAG_YMM0       (1ULL << 41)
#define DBG_CTX_EX_PART_FLAG_YMM1       (1ULL << 42)
#define DBG_CTX_EX_PART_FLAG_YMM2       (1ULL << 43)
#define DBG_CTX_EX_PART_FLAG_YMM3       (1ULL << 44)
#define DBG_CTX_EX_PART_FLAG_YMM4       (1ULL << 45)
#define DBG_CTX_EX_PART_FLAG_YMM5       (1ULL << 46)
#define DBG_CTX_EX_PART_FLAG_YMM6       (1ULL << 47)
#define DBG_CTX_EX_PART_FLAG_YMM7       (1ULL << 48)
#define DBG_CTX_EX_PART_FLAG_YMM8       (1ULL << 49)
#define DBG_CTX_EX_PART_FLAG_YMM9       (1ULL << 50)
#define DBG_CTX_EX_PART_FLAG_YMM10      (1ULL << 51)
#define DBG_CTX_EX_PART_FLAG_YMM11      (1ULL << 52)
#define DBG_CTX_EX_PART_FLAG_YMM12      (1ULL << 53)
#define DBG_CTX_EX_PART_FLAG_YMM13      (1ULL << 54)
#define DBG_CTX_EX_PART_FLAG_YMM14      (1ULL << 55)
#define DBG_CTX_EX_PART_FLAG_YMM15      (1ULL << 56)
