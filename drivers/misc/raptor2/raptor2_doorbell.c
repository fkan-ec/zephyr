#define DT_DRV_COMPAT raptor2_doorbell

#include <kernel.h>
#include <device.h>
#include <devicetree.h>

typedef void (*irq_config_func_t)(const struct device *dev);

struct doorbell_data {
	uint32_t isr_count;
};

struct doorbell_cfg {
	uint32_t irq;
	uint64_t mem_base;
	irq_config_func_t irq_config_func;
};

void doorbell_isr(struct device *dev)
{
	struct doorbell_data *data;
	struct doorbell_cfg *config;

	data = (struct doorbell_data *)dev->data;
	config = (struct doorbell_cfg *)dev->config;

	data->isr_count++;
	printk("Doorbell ISR triggered %d for irq %d\n", data->isr_count, config->irq);
}

static int doorbell_init(const struct device *dev)
{
	struct doorbell_cfg *config;

	config = (struct doorbell_cfg *)dev->config;

	config->irq_config_func(dev);

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
