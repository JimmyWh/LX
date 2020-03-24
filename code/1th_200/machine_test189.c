#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/regulator/driver.h>
#include <linux/mfd/core.h>
#include <linux/mfd/tps6105x.h>

static struct regulator_consumer_supply myregulator_supplies[] = {
		REGULATOR_SUPPLY("VCC","mylcd"),
};


static struct regulator_init_data mymachine_init_data = {
	.constraints = {
			.min_uV 			= 12000000,
			.max_uV 			= 12000000,
			.valid_modes_mask   = REGULATOR_MODE_NORMAL,
			.valid_ops_mask     = REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = 1,
		.consumer_supplies     = myregulator_supplies,
};


static void mymachine_release(struct device *dev)
{

}

static struct platform_device mymachine_dev = {
	.name = "mymachine",
	.id = -1,	
	.dev = {
		.release       = mymachine_release,
		.platform_data = &mymachine_init_data,
	},
};

static int mymachine_init(void)
{
	platform_device_register(&mymachine_dev);
	return 0;
}

static void mymachine_exit(void)
{
	platform_device_unregister(&mymachine_dev);
}

module_init(mymachine_init);
module_exit(mymachine_exit);
MODULE_LICENSE("GPL");




