
#include  <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/serio.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <asm/io.h>
#include <asm/irq.h>


static struct input_dev *s3c_ts_dev;
struct s3c_ts_regs {
	unsigned long adccon;
	unsigned long adctsc;
	unsigned long adcdly;
	unsigned long adcdat0;
	unsigned long adcdat1;
	unsigned long adcupdn;
};
static volatile struct s3c_ts_regs *s3c_ts_regs;
static struct timer_list ts_timer;

static void enter_wait_pen_down_mode(void)
{
	s3c_ts_regs->adctsc = 0xd3;
	
}

static void enter_wait_pen_up_mode(void)
{
	
	s3c_ts_regs->adctsc = 0x1d3;

}

static void enter_measure_xy_mode(void)
{
	
	s3c_ts_regs->adctsc = (1<<2)|(1<<3);
}

static void start_adc(void)
{
	s3c_ts_regs->adccon |= (1<<0);
	
}

static int s3c_filter_ts(int x[],int y[])
{
#define ERR_LINIT 10
	 int avr_x,avr_y;
	int det_x,det_y;
	 avr_x = (x[0] + x[1])/2;
	 avr_y = (y[0] + y[1])/2;

	det_x = (x[2] >avr_x)?(x[2] -avr_x):(avr_x -x[2]);
	
	det_y = (y[2] >avr_y)?(y[2] -avr_y):(avr_y -y[2]);

	if ((det_x > ERR_LINIT)|| (det_y > ERR_LINIT))
	return 0;

	
	avr_x = (x[1] + x[2])/2;
	avr_y = (y[1] + y[2])/2;
	
	det_x = (x[3] >avr_x)?(x[3] -avr_x):(avr_x -x[3]);
	   
	det_y = (y[3] >avr_y)?(y[3] -avr_y):(avr_y -y[3]);
	if ((det_x > ERR_LINIT)|| (det_y > ERR_LINIT))
	return 0;

	return 1;
}
	
static void s3c_ts_timer_function
	(unsigned long data)
{
	if (s3c_ts_regs->adcdat0 &(1<<15))
	{
		input_report_abs(s3c_ts_dev,ABS_PRESSURE,0);
		input_report_key(s3c_ts_dev,BTN_TOUCH,0);
		input_sync(s3c_ts_dev);	
		enter_wait_pen_down_mode();
	}
	else
	{
		enter_measure_xy_mode();
		start_adc();
	}
}

static irqreturn_t pen_down_up(int irq,void *dev_id)
{
	if (s3c_ts_regs->adcdat0 &(1<<15))
	{
		//printk("pen up\n");
		input_report_abs(s3c_ts_dev,ABS_PRESSURE,0);
		input_report_key(s3c_ts_dev,BTN_TOUCH,0);
		input_sync(s3c_ts_dev);

		enter_wait_pen_down_mode();
		
	}
	else
	{
		//printk("pen down\n");
		//
        enter_measure_xy_mode();
		start_adc();
	}
	
	return IRQ_HANDLED;

}

static irqreturn_t adc_irq(int irq,void *dev_id)
{
	static int cnt =0;
	int adcdat0,adcdat1;
	static int x[4],y[4];;
	
	adcdat0 =s3c_ts_regs->adcdat0;
	adcdat1 =s3c_ts_regs->adcdat1;

	
	if (s3c_ts_regs->adcdat0 &(1<<15))
	{
		cnt =0;
		input_report_abs(s3c_ts_dev,ABS_PRESSURE,0);
		input_report_key(s3c_ts_dev,BTN_TOUCH,0);
		input_sync(s3c_ts_dev);
	
		enter_wait_pen_down_mode();
	}
	else
	{
		x[cnt]=adcdat0&0x3ff;
		y[cnt]=adcdat1&0x3ff;
		++cnt;
		if (cnt ==4)
		{
			if (s3c_filter_ts(x,y))
			{
				//printk("x= %d,y =%d\n",(x[0]+x[1]+x[2]+x[3])/4,
				//(y[0]+y[1]+y[2]+y[3])/4);
				input_report_abs(s3c_ts_dev,ABS_X,(x[0]+x[1]+x[2]+x[3])/4);
				input_report_abs(s3c_ts_dev,ABS_Y,(y[0]+y[1]+y[2]+y[3])/4);
				input_report_abs(s3c_ts_dev,ABS_PRESSURE,1);
				input_report_key(s3c_ts_dev,BTN_TOUCH,1);
				input_sync(s3c_ts_dev);

			}
		
				cnt =0;
				enter_wait_pen_up_mode();
				mod_timer(&ts_timer,jiffies+HZ/100);

		}
		else
		{
			enter_measure_xy_mode();
			start_adc();
		}
	}

	return IRQ_HANDLED;
}






static int s3c_ts_init(void)
{
	struct clk* clk;
	s3c_ts_dev = input_allocate_device();

//	s3c_ts_dev 

	
	set_bit(EV_KEY,s3c_ts_dev->evbit); 
	set_bit(EV_ABS,s3c_ts_dev->evbit); 
	set_bit(BTN_TOUCH,s3c_ts_dev->keybit);
	input_set_abs_params(s3c_ts_dev,ABS_X,0,0x3FF,0,
		0);
	input_set_abs_params(s3c_ts_dev,ABS_Y,0,0x3FF,0,
		0);
	input_set_abs_params(s3c_ts_dev,ABS_PRESSURE,0,1,
		0,0);

	input_register_device(s3c_ts_dev);

	clk = clk_get(NULL,"adc");
	clk_enable(clk);
	s3c_ts_regs = ioremap(0x58000000,sizeof(struct 
		s3c_ts_regs));
	s3c_ts_regs->adccon = (1<<14)| (49<<6);
	request_irq(IRQ_TC,pen_down_up,
		IRQF_SAMPLE_RANDOM,"ts_pen",NULL);

	request_irq(IRQ_ADC,adc_irq,
		IRQF_SAMPLE_RANDOM,"adc",NULL);

	
	s3c_ts_regs->adcdly = 0xffff;

	init_timer(&ts_timer);
	ts_timer.function =s3c_ts_timer_function;
	add_timer(&ts_timer);
	enter_wait_pen_down_mode();
	return 0;
}

static void s3c_ts_exit(void)
{
	free_irq(IRQ_TC,NULL);
	free_irq(IRQ_ADC,NULL);
	iounmap(s3c_ts_regs);
	input_unregister_device(s3c_ts_dev);
	input_free_device(s3c_ts_dev);
	del_timer(&ts_timer);

}

module_init(s3c_ts_init);
module_exit(s3c_ts_exit);
MODULE_LICENSE("GPL");

