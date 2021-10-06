#define DT_DRV_COMPAT raptor2_doorbell

#include <kernel.h>
#include <device.h>
#include <devicetree.h>

/* Enable / Disable SIF register based interrupts */
#define SIF_REG_INT	0
#define E1_TO_E1_INT	1
#define SU_TO_E1_INT	0

#if SIF_REG_INT
#define SIF_REG_EVENT_TO_CPU_BASE	0x69080540UL

#define GIC_SPI_INT_BASE	32
#define NUM_INTR_PER_REG	32
#endif

typedef void (*irq_config_func_t)(const struct device *dev);

struct doorbell_data {
	uint32_t isr_count;
};

struct doorbell_cfg {
	uint32_t irq;
	uint32_t rbell_irq;
	uint32_t affinity;
	uint64_t mem_base;
	irq_config_func_t irq_config_func;
};

#if SIF_REG_INT
static void doorbell_update_irq_bit(uint32_t irq, bool value)
{
	uint32_t bit_pos;
	uint32_t bit_base_offset;
	mem_addr_t reg_addr;

	bit_pos = irq % NUM_INTR_PER_REG;
	bit_base_offset = irq / NUM_INTR_PER_REG;
	reg_addr = (mem_addr_t) (SIF_REG_EVENT_TO_CPU_BASE + (bit_base_offset * 4));

	if (value) {
		sys_write32(sys_read32(reg_addr) | (uint32_t)(1 << bit_pos),
			    reg_addr);
	} else {
		sys_write32(sys_read32(reg_addr) & (uint32_t)(~(1 << bit_pos)),
			    reg_addr);
	}
}
#endif

void doorbell_isr(struct device *dev)
{
	struct doorbell_data *data;
	struct doorbell_cfg *config;

	data = (struct doorbell_data *)dev->data;
	config = (struct doorbell_cfg *)dev->config;

#if SIF_REG_INT
	/* Clear the SIF REG IRQ */
	/* GIC SPI interrupt number will be (actual hwirq + GIC_SPI_INT_BASE) */
	doorbell_update_irq_bit((config->irq - GIC_SPI_INT_BASE), 0);

	/* Sample code to trigger irq on remote end (Linux) */
	/* SIF: Use actual hwirq number for Linux side remote irq */
	//doorbell_update_irq_bit(config->rbell_irq, 1);
#endif

#if E1_TO_E1_INT
	/* No need to clear the IRQ explicitly */

	/* Sample code to trigger irq on remote end (Linux) */
	/* GIC-SPI: Set the Linux side interrupt as pending inside GIC */
	//z_arm64_spi_irq_set_pending(config->rbell_irq);
#endif

#if SU_TO_E1_INT
	/* Clear SU side IRQ */
	su_clear_irq(config->irq);
#endif

	data->isr_count++;
	printk("Doorbell ISR triggered %d for irq %d with mpidr 0x%llx\n",
		data->isr_count, config->irq, GET_MPIDR());
}

static int doorbell_init(const struct device *dev)
{
	struct doorbell_cfg *config;

	config = (struct doorbell_cfg *)dev->config;

	config->irq_config_func(dev);
	z_arm64_irq_affinity_set(config->irq, config->affinity);

	return 0;
}

/* Device instantiation */

#define RAPTOR2_DOORBELL_INIT(n) \
	static void doorbell_irq_config_func_##n(const struct device *dev) \
	{ \
		IRQ_CONNECT(DT_INST_IRQN(n), \
		    DT_INST_IRQ(n, priority), \
		    doorbell_isr, \
		    DEVICE_DT_INST_GET(n), \
		    0); \
		irq_enable(DT_INST_IRQN(n)); \
	} \
	static struct doorbell_data doorbell_data_##n = { \
		.isr_count = 0, \
	}; \
	static struct doorbell_cfg doorbell_cfg_##n = { \
		.irq = DT_INST_IRQN(n), \
		.rbell_irq = DT_INST_PROP(n, rbell_irq), \
		.affinity = DT_INST_PROP(n, cpu_affinity), \
		.mem_base = DT_INST_REG_ADDR(n), \
		.irq_config_func = doorbell_irq_config_func_##n, \
	}; \
	DEVICE_DT_INST_DEFINE(n, \
			doorbell_init, \
			device_pm_control_nop, \
			&doorbell_data_##n, \
			&doorbell_cfg_##n, \
			SMP, \
			50, \
			NULL);

DT_INST_FOREACH_STATUS_OKAY(RAPTOR2_DOORBELL_INIT)
