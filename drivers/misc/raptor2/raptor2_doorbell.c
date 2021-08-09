#include <kernel.h>
#include <device.h>
#include <devicetree.h>

#define DOORBELL	DT_NODELABEL(doorbell0)

struct doorbell_data {
	uint32_t isr_count;
};

struct doorbell_cfg {
	uint64_t mem_base;
};

void doorbell_isr(struct device *dev)
{
	struct doorbell_data *data;

	data = (struct doorbell_data *)dev->data;
	data->isr_count++;
	printk("Doorbell ISR triggered %d\n", data->isr_count);
}

static int doorbell_init(const struct device *dev)
{
	IRQ_CONNECT(DT_IRQN(DOORBELL),
		    DT_IRQ(DOORBELL, priority),
		    doorbell_isr,
		    DEVICE_DT_GET(DOORBELL),
		    0);
	irq_enable(DT_IRQN(DOORBELL));

	return 0;
}

/* Device instantiation */
static struct doorbell_data doorbell_data_0 = {
	.isr_count = 0,
};

static struct doorbell_cfg doorbell_cfg_0 = {
	.mem_base = DT_REG_ADDR(DOORBELL),
};

DEVICE_DT_DEFINE(DOORBELL, \
		doorbell_init, \
		device_pm_control_nop, \
		&doorbell_data_0, \
		&doorbell_cfg_0, \
		SMP, \
		50, \
		NULL);

