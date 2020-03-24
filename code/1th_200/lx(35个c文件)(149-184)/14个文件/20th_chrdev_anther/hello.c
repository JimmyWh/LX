#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>
#include <linux/poll.h>
#include <linux/cdev.h>


static int major;
static struct cdev hello_cdev;
static struct cdev hello2_cdev;

static struct class *cls;


#define HELLO_CNT 2


static int hello_open(struct inode *inode, 
			struct file *file)	
{
	printk("hello_open\n");
	return 0;
	
} 

static int hello2_open(struct inode *inode, 
			struct file *file)	
{
	printk("hello2_open\n");
	return 0;
	
} 


static struct file_operations hello_fops = {
	
	.owner = THIS_MODULE,
	.open  = hello_open,
};



static struct file_operations hello2_fops = {
	
	.owner = THIS_MODULE,
	.open  = hello2_open,
};

static int hello_init(void)
{
	dev_t devid;
#if 0
	major = register_chrdev(0,"hello",hello_fops);
#else
	if (major) {
		devid = MKDEV(major, 0);
		register_chrdev_region(devid, HELLO_CNT, "hello");
	} else {
		alloc_chrdev_region(&devid, 0, HELLO_CNT, "hello");
		major = MAJOR(devid);
	}
	cdev_init(&hello_cdev,&hello_fops);
	cdev_add(&hello_cdev,devid,HELLO_CNT);

	
	devid = MKDEV(major, 2);
	register_chrdev_region(devid, 1, "hello2");
	cdev_init(&hello2_cdev,&hello2_fops);
	cdev_add(&hello2_cdev,devid,1);


#endif
	cls = class_create(THIS_MODULE,"hello");
	class_device_create(cls, NULL,
		MKDEV(major,0),
		NULL,"hello0");
	class_device_create(cls, NULL,
		MKDEV(major,1),
		NULL,"hello1");
	class_device_create(cls, NULL,
			MKDEV(major,2),
			NULL,"hello2");

	class_device_create(cls, NULL,
			MKDEV(major,3),
			NULL,"hello3");
	return 0;
}

static void hello_eixt(void)
{
	class_device_destroy(cls,MKDEV(major,0));
	class_device_destroy(cls,MKDEV(major,1));
	class_device_destroy(cls,MKDEV(major,2));
	class_device_destroy(cls,MKDEV(major,3));
		

	class_destroy(cls);
	cdev_del(&hello_cdev);
	unregister_chrdev_region(MKDEV(major,2),
		HELLO_CNT);

	cdev_del(&hello2_cdev);
	unregister_chrdev_region(MKDEV(major,2),
		1);
}

module_init(hello_init);
module_exit(hello_eixt);
MODULE_LICENSE("GPL");
