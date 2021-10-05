/*
 * Copyright 2021 EdgeQ Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <devicetree.h>
#include <sys/util.h>
#include <arch/arm64/arm_mmu.h>

static const struct arm_mmu_region mmu_regions[] = {

	MMU_REGION_FLAT_ENTRY("GIC",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, arm_gic), 0),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, arm_gic), 0),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("GIC",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, arm_gic), 1),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, arm_gic), 1),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

#if defined(CONFIG_BOARD_EDGEQ_RAPTOR2_SOCFM)
	MMU_REGION_FLAT_ENTRY("UART",
			      DT_REG_ADDR(DT_INST(0, arm_pl011)),
			      DT_REG_SIZE(DT_INST(0, arm_pl011)),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS),

	MMU_REGION_FLAT_ENTRY("ADMAREG",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 0),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 0),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OCM",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 1),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 1),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OLMEM",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 2),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 2),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("PLMEM",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 3),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 3),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("MXL1REG",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 4),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 4),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("MXL2REG",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 5),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 5),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("CRSSREG",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 6),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 6),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("CRSSMEMSS",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 7),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 7),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

#elif defined(CONFIG_BOARD_EDGEQ_RAPTOR2_PROTIUM) || \
	defined(CONFIG_BOARD_EDGEQ_RAPTOR2_PROTIUM_SINGLE_PPU) || \
	defined (CONFIG_BOARD_EDGEQ_RAPTOR2_A0) || \
	defined (CONFIG_BOARD_EDGEQ_RAPTOR2_A0_PPU)

	MMU_REGION_FLAT_ENTRY("UART",
			      DT_REG_ADDR(DT_INST(0, ns16550)),
			      DT_REG_SIZE(DT_INST(0, ns16550)),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS),

	MMU_REGION_FLAT_ENTRY("ADMAREG",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 0),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 0),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OCM",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 1),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 1),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OLMEM",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 2),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 2),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("PLMEM",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 3),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 3),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("MXL1REG",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 4),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 4),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("MXL2REG",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 5),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 5),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("CRSSREG",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 6),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 6),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("CRSSMEMSS",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 7),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 7),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("SIFREG",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 8),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 8),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OTRXQSU0",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 9),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 9),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OTRXQSU1",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 10),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 10),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OTRXQSU2",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 11),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 11),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OTRXQSU3",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 12),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 12),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OTRXQSU4",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 13),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 13),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OTRXQSU5",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 14),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 14),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OTRXQSU6",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 15),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 15),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("OTRXQSU7",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 16),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 16),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("DSU0CMU",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 17),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 17),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("DSU0REG",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 18),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 18),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("DSU1CMU",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 19),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 19),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("MXL0CMU",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 20),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 20),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("MXL1CMU",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 21),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 21),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("CRSS0CMU",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 22),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 22),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("CRSS1CMU",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 23),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 23),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("CRSS2CMU",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 24),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 24),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

	MMU_REGION_FLAT_ENTRY("CRSS3CMU",
			      DT_REG_ADDR_BY_IDX(DT_INST(0, raptor2_mmio), 25),
			      DT_REG_SIZE_BY_IDX(DT_INST(0, raptor2_mmio), 25),
			      MT_DEVICE_nGnRnE | MT_P_RW_U_NA | MT_NS),

#else
#error "Please define UART MMU region mapping"
#endif
};

const struct arm_mmu_config mmu_config = {
	.num_regions = ARRAY_SIZE(mmu_regions),
	.mmu_regions = mmu_regions,
};
