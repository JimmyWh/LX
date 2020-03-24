#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
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
#include <asm/uaccess.h>

static unsigned short ignore[]      = { I2C_CLIENT_END };
static unsigned short normal_addr[] = { 0x50, I2C_CLIENT_END }; /* ¦Ì??¡¤?¦Ì¨º?7?? */

static unsigned short force_addr[]= {ANY_I2C_BUS,0x60,I2C_CLIENT_END};
static unsigned short *force[] = {force_addr,NULL};

static struct i2c_driver at24cxx_driver;
struct i2c_client *at24cxx_client;



static struct i2c_client_address_data addr_data = {
	.normal_i2c	= ignore,  /* ¨°a¡¤¡é3?SD?o?o¨ª¨¦¨¨¡À?¦Ì??¡¤2¡é¦Ì?¦Ì?ACKD?o?,2??¨¹¨¨¡¤?¡§¡ä??¨²?a??¨¦¨¨¡À? */
	.probe		= ignore,
	.ignore		= ignore,
	.forces     = force,
};


static int major;

ssize_t at24cxx_read(struct file *file, char __user *buf, 
	size_t size, loff_t *offset)
{

	
	unsigned char address;
	unsigned char data;
	struct i2c_msg msgs[2];
	int result;

	if (size != 1)
		return -EINVAL;
	
	copy_from_user(&address,buf,1);

	msgs[0].addr = at24cxx_client->addr;
	msgs[0].buf  = &address;
	msgs[0].len  =	1;
	msgs[0].flags = 0;

	msgs[1].addr = at24cxx_client->addr;
	msgs[1].buf  = &data;
	msgs[1].len  =	1;
	msgs[1].flags = I2C_M_RD;


	
	result = i2c_transfer(at24cxx_client->adapter,msgs,2);

	if (result == 2)
	{
		copy_to_user(buf,&data,1);
		return 1;
	}
	else
		return -EIO;

}

ssize_t at24cxx_write(struct file *file, const char __user *buf, 
	size_t size, loff_t *offset)
{

	unsigned char val[2];
	struct i2c_msg msgs[1];
	int result;

	if (size != 2)
		return -EINVAL;
	
	copy_from_user(val,buf,2);

	msgs[0].addr = at24cxx_client->addr;
	msgs[0].buf  = val;
	msgs[0].len  =  2;
	msgs[0].flags = 0;


	
	result = i2c_transfer(at24cxx_client->adapter,msgs,1);

	if (result == 1)
		return 2;
	else
		return -EIO;
}


static struct file_operations at24cxx_fops={

	.owner = THIS_MODULE,
	.read  = at24cxx_read,
	.write = at24cxx_write,

};

static struct class *cls;

static int at24cxx_detect(struct i2c_adapter *adapter, int address, int kind)
{	
	
	
	//printk("at24cxx_detect\n");
	at24cxx_client = kzalloc(sizeof(struct i2c_client), GFP_KERNEL);
	at24cxx_client->addr = address;
	at24cxx_client->adapter = adapter;
	at24cxx_client->driver = &at24cxx_driver;

	strcpy(at24cxx_client->name, "at24cxx");
	i2c_attach_client(at24cxx_client);
	major = register_chrdev(0,"at24cxx",&at24cxx_fops);

	cls = class_create(THIS_MODULE,"at24cxx");
	class_device_create(cls,NULL,MKDEV(major,0),NULL,"at24cxx");
	return 0;
}

static int at24cxx_attach(struct i2c_adapter *adapter)
{
	return i2c_probe(adapter, &addr_data, at24cxx_detect);
}

static int at24cxx_detach(struct i2c_client *client)
{
	
	printk("at24cxx_detach\n");
	class_device_destroy(cls,MKDEV(major,0));
	class_destroy(cls);
	unregister_chrdev(major,"at24cxx");
	i2c_detach_client(client);
	kfree(i2c_get_clientdata(client));
	return 0;
}


/* 1. ¡¤???¨°???i2c_driver?¨¢11¨¬? */
/* 2. ¨¦¨¨??i2c_driver?¨¢11¨¬? */
static struct i2c_driver at24cxx_driver = {
	.driver = {
		.name	= "at24cxx",
	},
	.attach_adapter = at24cxx_attach,
	.detach_client  = at24cxx_detach,
};

static int at24cxx_init(void)
{
	i2c_add_driver(&at24cxx_driver);
	return 0;
}

static void at24cxx_exit(void)
{
	i2c_del_driver(&at24cxx_driver);
}

module_init(at24cxx_init);
module_exit(at24cxx_exit);

MODULE_LICENSE("GPL");

