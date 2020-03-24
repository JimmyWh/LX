#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/irq.h>

#include <asm/gpio.h>
#include <asm/io.h>
//#include <asm/arch/regs-gpio.h>



static struct input_dev *buttons_dev;
static struct timer_list buttons_timer;
static struct pin_desc *irq_pd;
	

struct pin_desc{
	int irq;
	char *name;
	unsigned int pin;
	unsigned int key_val;
};

static struct pin_desc pin_desc[4] = {
		{IRQ_EINT0,"S2",S3C2410_GPF(0),KEY_L},
		{IRQ_EINT2,"S3",S3C2410_GPF(2),KEY_S},
		{IRQ_EINT11,"S4",S3C2410_GPF(3),KEY_ENTER},
		{IRQ_EINT19,"S5",S3C2410_GPF(11),KEY_LEFTSHIFT},

};

static irqreturn_t buttons_irq(int irq, void *data)
{

	irq_pd = (struct pin_desc*)data;
	mod_timer(&buttons_timer, jiffies + HZ/100);
	return IRQ_RETVAL(IRQ_HANDLED);
}


static void buttons_timer_function(unsigned long data)
{
	struct pin_desc *pindesc = irq_pd;
	unsigned int pinval;

	if (!pindesc)
		return;

	pinval = s3c2410_gpio_getpin(pindesc->pin);

	if (pinval)
	{
		input_event(buttons_dev, EV_KEY, pindesc->key_val,0);
		input_sync(buttons_dev);
	}
	else
	{
		input_event(buttons_dev, EV_KEY, pindesc->key_val,1);
		input_sync(buttons_dev);
	}

}

static int buttons_init(void)
{
	int i;

	buttons_dev = input_allocate_device();

	set_bit(EV_KEY,buttons_dev->evbit);
	set_bit(EV_REP,buttons_dev->evbit);

	set_bit(KEY_L      ,buttons_dev->keybit);
	set_bit(KEY_S      ,buttons_dev->keybit);	
	set_bit(KEY_ENTER  ,buttons_dev->keybit);
	set_bit(KEY_LEFTSHIFT,buttons_dev->keybit);

	input_register_device(buttons_dev);
	init_timer(&buttons_timer);
	buttons_timer.function = buttons_timer_function;
	add_timer(&buttons_timer);

	for (i=0;i <4;i++)
	{
		request_irq(pin_desc[i].irq, buttons_irq, (IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING), pin_desc[i].name, &pin_desc[i]);
	}

	//指定这些中断可以用于唤醒系统
	irq_set_irq_wake(IRQ_EINT0, 1);
	irq_set_irq_wake(IRQ_EINT2, 1);
	irq_set_irq_wake(IRQ_EINT11, 1);

	return 0;

}


static void buttons_exit(void)
{
	int i;

	irq_set_irq_wake(IRQ_EINT0, 0);
	irq_set_irq_wake(IRQ_EINT2, 0);
	irq_set_irq_wake(IRQ_EINT11, 0);

	for (i=0;i <4;i++)
	{
		free_irq(pin_desc[i].irq, &pin_desc[i]);
	}
	del_timer(&buttons_timer);
	input_unregister_device(buttons_dev);
	input_free_device(buttons_dev);

}

module_init(buttons_init);
module_init(buttons_exit);
MODULE_LICENSE("GPL");




