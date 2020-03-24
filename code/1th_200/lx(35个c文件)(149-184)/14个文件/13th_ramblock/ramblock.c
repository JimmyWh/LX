#include <linux/module.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/genhd.h>
#include <linux/hdreg.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/wait.h>
#include <linux/blkdev.h>
#include <linux/blkpg.h>
#include <linux/delay.h>
#include <linux/io.h>



#include <asm/system.h>
#include <asm/uaccess.h>
#include <asm/dma.h>

static struct gendisk *ramblock_disk;
static request_queue_t *ramblock_queue;
static DEFINE_SPINLOCK(ramblock_lock);
static int major;


#define RAMBLOCK_SIZE (1024*1024)
static unsigned char *ramblok_buf;

static int ramblock_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{

	geo->heads = 2;
	geo->sectors = 32;
	geo->cylinders = RAMBLOCK_SIZE/2/32/512;
	return 0;
}



static struct block_device_operations ramblock_fops = {
	.owner	= THIS_MODULE,
	//.ioctl	= ramblock_ioctl,
	.getgeo = ramblock_getgeo,
};


static void do_ramblock_request(request_queue_t * q)
{
	//static int cnt =0;
	
	struct request *req;
	//static int r_cnt =0;
	//static int w_cnt =0;
	//printk("do_ramblock_request %d\n",++cnt);
	
	while ((req = elv_next_request(q)) != NULL) 
	{
		
		unsigned long offset = req->sector << 9;

		unsigned long len    = req->current_nr_sectors << 9;

		if (rq_data_dir(req) ==READ)
		{
			//printk("do_ramblock_request read %d\n",++r_cnt);
			memcpy(req->buffer,ramblok_buf + offset,len);
		}
		else
		{//	printk("do_ramblock_request write %d\n",++w_cnt);
			
			memcpy(ramblok_buf + offset,req->buffer,len);
		
			
		}
		
		end_request(req, 1);	/* wrap up, 0 = fail, 1 = success */
	}
}


static int ramblock_init(void)
{
	ramblock_disk = alloc_disk(16);
	ramblock_queue = blk_init_queue(do_ramblock_request, &ramblock_lock);
	ramblock_disk->queue = ramblock_queue;
		

	major = register_blkdev(0,"ramblock");
	
	ramblock_disk->major = major;
	ramblock_disk->first_minor = 0;
	sprintf(ramblock_disk->disk_name, "ramblock");
	ramblock_disk->fops = &ramblock_fops;
	
	set_capacity(ramblock_disk, RAMBLOCK_SIZE/512);

	ramblok_buf = kzalloc(RAMBLOCK_SIZE,GFP_KERNEL);
	

	add_disk(ramblock_disk);
	return 0;
}

static void ramblock_exit(void)
{
	unregister_blkdev(major,"ramblock");
	del_gendisk(ramblock_disk);
	put_disk(ramblock_disk);
	blk_cleanup_queue(ramblock_queue);
	kfree(ramblok_buf);
}

module_init(ramblock_init);
module_exit(ramblock_exit);
MODULE_LICENSE("GPL");

