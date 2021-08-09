#define DT_DRV_COMPAT raptor2_doorbell

#include <kernel.h>
#include <device.h>
#include <devicetree.h>

#define SIF_REG_EVENT_TO_CPU_BASE	0x69080540UL

typedef void (*irq_config_func_t)(const struct device *dev);

struct doorbell_data {
	uint32_t isr_count;
};

struct doorbell_cfg {
	uint32_t irq;
	uint32_t affinity;
	uint64_t mem_base;
	irq_config_func_t irq_config_func;
};

void doorbell_isr(struct device *dev)
{
	uint32_t bit_pos;
	uint32_t bit_base_offset;
	uint32_t value;
	mem_addr_t reg_addr;
	struct doorbell_data *data;
	struct doorbell_cfg *config;

	data = (struct doorbell_data *)dev->data;
	config = (struct doorbell_cfg *)dev->config;

	bit_pos = (config->irq - 32) % 32;
	bit_base_offset = (config->irq - 32) / 32;
	reg_addr = (mem_addr_t) (SIF_REG_EVENT_TO_CPU_BASE + (bit_base_offset * 4));

	value = sys_read32(reg_addr);
	value = value & (uint32_t)(~(1 << bit_pos));
	sys_write32(value, reg_addr);

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
