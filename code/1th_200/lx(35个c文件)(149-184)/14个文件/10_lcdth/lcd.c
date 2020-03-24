

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/wait.h>
#include <linux/platform_device.h>
#include <linux/clk.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/div64.h>

#include <asm/mach/map.h>
#include <asm/arch/regs-lcd.h>
#include <asm/arch/regs-gpio.h>
#include <asm/arch/fb.h>

static struct fb_info *s3c_lcd;


static volatile unsigned long *gpbcon;
static volatile unsigned long *gpbdat;
static volatile unsigned long *gpccon;
static volatile unsigned long *gpdcon;
static volatile unsigned long *gpgcon;
 
 
struct lcd_regs {
	 unsigned long	 lcdcon1;
	 unsigned long	 lcdcon2;
	 unsigned long	 lcdcon3;
	 unsigned long	 lcdcon4;
	 unsigned long	 lcdcon5;
	 unsigned long	 lcdsaddr1;
	 unsigned long	 lcdsaddr2;
	 unsigned long	 lcdsaddr3;
	 unsigned long	 redlut;
	 unsigned long	 greenlut;
	 unsigned long	 bluelut;
	 unsigned long	 reserved[9];
	 unsigned long	 dithmode;
	 unsigned long	 tpal;
	 unsigned long	 lcdintpnd;
	 unsigned long	 lcdsrcpnd;
	 unsigned long	 lcdintmsk;
	 unsigned long	 lpcsel;
 };



static inline u_int chan_to_field(u_int chan, struct fb_bitfield *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	return chan << bf->offset;
}


static int s3c_lcdfb_setcolreg(unsigned int regno, unsigned int red,
			     unsigned int green, unsigned int blue,
			     unsigned int transp, struct fb_info *info)
{
	unsigned int val;
	if (regno > 16)
		return 1;

	
	val  = chan_to_field(red, &info->var.red);
	val |= chan_to_field(green, &info->var.green);
	val |= chan_to_field(blue, &info->var.blue);
	
	((u32 *)(info->pseudo_palette))[regno] = val;
	return 0;
}


static volatile struct lcd_regs *lcd_regs;
static unsigned long pseudo_palette[16];

static struct fb_ops s3c_fb_ops = {
	.owner		= THIS_MODULE,
	.fb_setcolreg	= s3c_lcdfb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
};

static int lcd_init(void)
{
	s3c_lcd = framebuffer_alloc(0,NULL);

	strcpy(s3c_lcd->fix.id,"mylcd");

    s3c_lcd->fix.smem_len = 240*320*16/8;
	s3c_lcd->fix.type = FB_TYPE_PACKED_PIXELS;
	s3c_lcd->fix.visual = FB_VISUAL_TRUECOLOR;
	s3c_lcd->fix.line_length = 240*2;

	s3c_lcd->var.xres = 240;
	s3c_lcd->var.yres = 320;
	s3c_lcd->var.xres_virtual = 240;
	s3c_lcd->var.yres_virtual = 320;
	
	s3c_lcd->var.bits_per_pixel=16;
	s3c_lcd->var.red.offset =11;
	s3c_lcd->var.red.length = 5;

	s3c_lcd->var.green.offset =5;
	s3c_lcd->var.green.length = 6;

	s3c_lcd->var.blue.offset =0;
	s3c_lcd->var.blue.length =5;
	s3c_lcd->var.activate =FB_ACTIVATE_NOW;
	
	s3c_lcd->fbops = &s3c_fb_ops;
	//s3c_lcd->screen_base = 
	s3c_lcd->screen_size = 240*324*16/8;

	s3c_lcd->pseudo_palette = pseudo_palette;//

	gpbcon = ioremap(0x56000010,8);
	gpbdat = gpbcon + 1;

	gpccon = ioremap(0x56000020,4);
	gpdcon = ioremap(0x56000030,4);
	gpgcon = ioremap(0x56000060,4);

	*gpccon = 0xaaaaaaaa;
	*gpdcon = 0xaaaaaaaa;
    *gpbcon &= ~(3);
    *gpbcon |= 1; 
    *gpbdat &= ~1;
	*gpgcon | (3 <<8);
	lcd_regs = ioremap(0x4D000000,
		sizeof(struct lcd_regs));


	lcd_regs->lcdcon1 = (4 <<8)|(3<<5)|
		(0x0c <<1);

	lcd_regs->lcdcon2 = (3 <<24) |
		(319 <<14) | (1 <<6 ) |(0 <<0);

	lcd_regs->lcdcon3 = (16<<19)|
		(239<<8)|(10<<0);

	lcd_regs->lcdcon4 = 4;

	lcd_regs->lcdcon5 =(1<<11)|(1<<9)
		|(1<<8)|(1<<0);

	s3c_lcd->screen_base = dma_alloc_writecombine(NULL,
		s3c_lcd->fix.smem_len,&s3c_lcd->fix.smem_start,GFP_KERNEL);
	
	//s3c_lcd->fix.smem_start =
	lcd_regs->lcdsaddr1 = (s3c_lcd->fix.smem_start >>1)&~(3<<30);
	lcd_regs->lcdsaddr2 = ((s3c_lcd->fix.smem_start + s3c_lcd->fix.smem_len) >>1) &0x1fffff;
	lcd_regs->lcdsaddr3 = (240*16/16);

	lcd_regs->lcdcon1 |= (1<<0);
	lcd_regs->lcdcon5 |= (1<<3);
	*gpbdat |= 1;
	
	register_framebuffer(s3c_lcd); 
	return 0;
}

static void lcd_exit(void)
{
	unregister_framebuffer(s3c_lcd);
	lcd_regs->lcdcon1 &= ~(1<<0);
	*gpbdat &= ~1;
	dma_free_writecombine(NULL,
		s3c_lcd->fix.smem_len
		,s3c_lcd->screen_base,
		s3c_lcd->fix.smem_start);

	iounmap(lcd_regs);
    iounmap(gpbcon);
	iounmap(gpccon);
	iounmap(gpdcon);
	iounmap(gpgcon);
	framebuffer_release(s3c_lcd);
}

module_init(lcd_init);
module_exit(lcd_exit);
MODULE_LICENSE("GPL");


