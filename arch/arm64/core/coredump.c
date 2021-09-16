/*
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <debug/coredump.h>

#define ARCH_HDR_VER			1

uint64_t z_aarch64_coredump_fault_sp;
uint64_t z_aarch64_coredump_fault_far;

struct arm_arch_block {
	struct {
		uint64_t x0;
		uint64_t x1;
		uint64_t x2;
		uint64_t x3;
		uint64_t x4;
		uint64_t x5;
		uint64_t x6;
		uint64_t x7;
		uint64_t x8;
		uint64_t x9;
		uint64_t x10;
		uint64_t x11;
		uint64_t x12;
		uint64_t x13;
		uint64_t x14;
		uint64_t x15;
		uint64_t x16;
		uint64_t x17;
		uint64_t x18;
		uint64_t x19;
		uint64_t x20;
		uint64_t x21;
		uint64_t x22;
		uint64_t x23;
		uint64_t x24;
		uint64_t x25;
		uint64_t x26;
		uint64_t x27;
		uint64_t x28;
		uint64_t x29;
		uint64_t x30;
		uint64_t sp;
		uint64_t pc;
		uint64_t cpsr;
	} r;
} __packed;

/*
 * This might be too large for stack space if defined
 * inside function. So do it here.
 */
static struct arm_arch_block arch_blk;

void arch_coredump_info_dump(const z_arch_esf_t *esf)
{
	struct coredump_arch_hdr_t hdr = {
		.id = COREDUMP_ARCH_HDR_ID,
		.hdr_version = ARCH_HDR_VER,
		.num_bytes = sizeof(arch_blk),
	};

	/* Nothing to process */
	if (esf == NULL) {
		return;
	}

	(void)memset(&arch_blk, 0, sizeof(arch_blk));

	arch_blk.r.x0 = esf->x0;
	arch_blk.r.x1 = esf->x1;
	arch_blk.r.x2 = esf->x2;
	arch_blk.r.x3 = esf->x3;
	arch_blk.r.x4 = esf->x4;
	arch_blk.r.x5 = esf->x5;
	arch_blk.r.x6 = esf->x6;
	arch_blk.r.x7 = esf->x7;
	arch_blk.r.x8 = esf->x8;
	arch_blk.r.x9 = esf->x9;
	arch_blk.r.x10 = esf->x10;
	arch_blk.r.x11 = esf->x11;
	arch_blk.r.x12 = esf->x12;
	arch_blk.r.x13 = esf->x13;
	arch_blk.r.x14 = esf->x14;
	arch_blk.r.x15 = esf->x15;
	arch_blk.r.x16 = esf->x16;
	arch_blk.r.x17 = esf->x17;
	arch_blk.r.x18 = esf->x18;
	arch_blk.r.x30 = esf->x30;
	arch_blk.r.sp = z_aarch64_coredump_fault_sp;
	arch_blk.r.pc = esf->elr;
	arch_blk.r.cpsr = esf->spsr;

	/* Send for output */
	coredump_buffer_output((uint8_t *)&hdr, sizeof(hdr));
	coredump_buffer_output((uint8_t *)&arch_blk, sizeof(arch_blk));
}

uint16_t arch_coredump_tgt_code_get(void)
{
	return COREDUMP_TGT_AARCH64;
}
