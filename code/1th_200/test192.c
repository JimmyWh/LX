#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/usb.h>
#include <linux/videodev2.h>
#include <linux/vmalloc.h>
#include <linux/wait.h>
#include <linux/mm.h>
#include <asm/atomic.h>
#include <asm/unaligned.h>
#include <media/v4l2-common.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf-core.h>

static unsigned long *GPJCON;
static unsigned long *GPJDAT;
static unsigned long *GPJUP;
static unsigned long *CISRCFMT;
static unsigned long *CIWDOFST;
static unsigned long *CIGCTRL;

static unsigned long *CIPRCLRSA1;
static unsigned long *CIPRCLRSA2;
static unsigned long *CIPRCLRSA3;
static unsigned long *CIPRCLRSA4;
static unsigned long *CIPRTRGFMT;
static unsigned long *CIPRCTRL;
static unsigned long *CIPRSCPRERATIO;
static unsigned long *CIPRSCPREDST;
static unsigned long *CIPRSCCTRL;
static unsigned long *CIPRTAREA;
static unsigned long *CIIMGCPT;
static unsigned long *SRCPND;
static unsigned long *INTPND;
static unsigned long *SUBSRCPND;


static void cmos_ov7740_gpio_cfg()
{
	*GPJCON = 0x2aaaaaa;
	*GPJDAT = 0;
	*GPJUP  = 0;
}

static void cmos_ov7740_camif_reset(void)
{
	*CISRCFMT |= (1 << 31);
	*CIGCTRL  |= (1 << 31);
	mdelay(10);
	*CIGCTRL &= ~(1 << 31);
	mdelay(10);

}

static void cmos_ov7740_clk_cfg(void)
{
	struct clk *camif_clk;
	struct clk *camif_upll_clk;
	camif_upll_clk = clk_get(NULL,"camif");
	if (!camif_clk || IS_ERR(camif_clk))
	{
		printk(KERN_INFO "failed to get CAMIF clock source\n");
	}
	clk_enable(camif_upll_clk);
	camif_upll_clk = clk_get(NULL,"camif-upll");
}

static int __devinit cmos_ov7740_probe(struct i2c_client *client,
							const struct i2c_device_id *id)
{
	printk(" %s %s %d\n",__FILE__,__FUNCTION__,__LINE__);

	GPJCON     = ioremap(0x560000d0, 4);
	GPJDAT     = ioremap(0x560000d4, 4);
	GPJUP      = ioremap(0x560000d8, 4);
	CISRCFMT   = ioremap(0x4F000000, 4);
	CIWDOFST   = ioremap(0x4F000004, 4);
	CIGCTRL    = ioremap(0x4F000008, 4);
	CIPRCLRSA1 = ioremap(0x4F00006C, 4);
	CIPRCLRSA2 = ioremap(0x4F000070, 4);
	CIPRCLRSA3 = ioremap(0x4F000074, 4);
	CIPRCLRSA4 = ioremap(0x4F000078, 4);
	CIPRTRGFMT = ioremap(0x4F00007C, 4);
	CIPRCTRL   = ioremap(0x4F000080, 4);
	CIPRSCPRERATIO = ioremap(0x4F000084, 4);
	CIPRSCPREDST   = ioremap(0x4F000088, 4);
	CIPRSCCTRL     = ioremap(0x4F00008C, 4);
	CIPRTAREA      = ioremap(0x4F000090, 4);
	CIIMGCPT       = ioremap(0x4F0000A0, 4);
	SRCPND         = ioremap(0x4F000000, 4);
	INTPND         = ioremap(0x4F000010, 4);
	SUBSRCPND      = ioremap(0x4F0000A0, 4);

	cmos_ov7740_gpio_cfg();
	cmos_ov7740_camif_reset();
	cmos_ov7740_clk_cfg();
	
	
}


static struct i2c_driver cmos_ov7740_driver = {
	.driver = {
			.name  = "cmos_ov7740",
			.owner = THIS_MODULE,	
		},
		.probe  = cmos_ov7740_probe,
	

};


static int cmos_ov7740_drv_init(void)
{
	i2c_add_driver(driver);

}

