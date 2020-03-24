#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
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

#include <linux/clk.h>
#include <asm/io.h>

#define OV7740_INIT_REGS_SIZE  (sizeof(ov7740_setting_30fps_VGA_640_480)/sizeof(ov7740_setting_30fps_VGA_640_480))

#define CAM_SRC_HSIZE (640)
#define CAM_SRC_VSIZE (480)

#define CAM_ORDER_YCbYCr (0)
#define CAM_ORDER_YCrYCb (1)
#define CAM_ORDER_CbYCry (2)
#define CAM_ORDER_CrYCby (3)

#define WinHorOfst   (0)
#define WinVerOfst   (0)

struct cmos_ov7740_scaler{
	unsigned int PreHorRatio;
	unsigned int PreVerRatio;
	unsigned int H_Shift;
	unsigned int V_Shift;
	unsigned int PreDstWidth;
	unsigned int PreDstHeight;
	unsigned int MainHorRatio;
	unsigned int MAinVerRatio;
	unsigned int SHfactor;
	unsigned int ScaleUpDown;
};

static struct cmos_ov7740_scaler sc;

typedef struct cmos_ov7740_i2c_value{
	unsigned char regaddr;
	unsigned char value;
}ov7740_t;

ov7740_t ov7740_setting_30fps_VGA_640_480[] = 
{
	{0x12, 0x80},
	{0x47, 0x02},
	{0x17, 0x27},
	{0x04, 0x40},
	{0x1B, 0x81},
	{0x29, 0x17},
	{0x5F, 0x03},
	{0x3A, 0x09},
	{0x33, 0x44},
	{0x68, 0x1A},

	{0x14, 0x38},
	{0x5F, 0x04},
	{0x64, 0x00},
	{0x67, 0x90},
	{0x27, 0x80},
	{0x45, 0x41},
	{0x4B, 0x40},
	{0x36, 0x2f},
	{0x11, 0x01},
	{0x36, 0x3f},
	{0x0c, 0x12},

	{0x12, 0x00},
	{0x17, 0x25},
	{0x18, 0xa0},
	{0x1a, 0xf0},
	{0x31, 0xa0},
	{0x32, 0xf0},

	{0x85, 0x08},
	{0x86, 0x02},
	{0x87, 0x01},
	{0xd5, 0x10},
	{0x0d, 0x34},
	{0x19, 0x03},
	{0x2b, 0xf8},
	{0x2c, 0x01},

	{0x53, 0x00},
	{0x89, 0x30},
	{0x8d, 0x30},
	{0x8f, 0x85},
	{0x93, 0x30},
	{0x95, 0x85},
	{0x99, 0x30},
	{0x9b, 0x85},

	{0xac, 0x6E},
	{0xbe, 0xff},
	{0xbf, 0x00},
	{0x38, 0x14},
	{0xe9, 0x00},
	{0x3D, 0x08},
	{0x3E, 0x80},
	{0x3F, 0x40},
	{0x40, 0x7F},
	{0x41, 0x6A},
	{0x42, 0x29},
	{0x49, 0x64},
	{0x4A, 0xA1},
	{0x4E, 0x13},
	{0x4D, 0x50},
	{0x44, 0x58},
	{0x4C, 0x1A},
	{0x4E, 0x14},
	{0x38, 0x11},
	{0x84, 0x70}
};

struct cmos_ov7740_fmt{
	char *name;
	u32  fourcc;
	int depth;
};

static struct cmos_ov7740_fmt formats[] = {
		{
			.name   = "RGB565",
			.fourcc = V4L2_PIX_FMT_RGB565,
			.depth  = 16,
		},
		{
			.name    = "PACKED_RGB_888",
			.fourcc  = V4L2_PIX_FMT_RGB24,
			.depth   = 24,
		}

};

struct camif_buffer{
	unsigned int order;
	unsigned long virt_base;
	unsigned long phy_base;
};

struct camif_buffer img_buff[]= {
	{
		.order = 0,
		.virt_base = (unsigned long)NULL,
		.phy_base  = (unsigned long)NULL,
	},
	{
		.order = 0,
		.virt_base = (unsigned long)NULL,
		.phy_base  = (unsigned long)NULL,
	},
	{
		.order = 0,
		.virt_base = (unsigned long)NULL,
		.phy_base  = (unsigned long)NULL,
	},
	{
		.order = 0,
		.virt_base = (unsigned long)NULL,
		.phy_base  = (unsigned long)NULL,
	}

};

static struct i2c_client *cmos_ov7740_client;

static unsigned long *GPJCON;
static unsigned long *GPJDAT;
static unsigned long *GPJUP;

// CAMIF
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

// IRQ
static unsigned long *SRCPND;
static unsigned long *INTPND;
static unsigned long *SUBSRCPND;

static unsigned int SRC_Width,SRC_Height;
static unsigned int TargetHsize_Pr,TargetVsize_Pr;
static unsigned long buf_size;
static unsigned int bytesperline;

static DECLARE_WAIT_QUEUE_HEAD(cam_wait_queue);

static volatile int ev_cam = 0;

static irqreturn_t cmos_ov7740_camif_irq_c(int irq,void *dev_id)
{
	return IRQ_HANDLED
}

static irqreturn_t cmos_ov7740_camif_irq_p(int irq,void *dev_id)
{
	*SRCPND    = 1 << 6;
	*INTPND    = 1 << 6;
	*SUBSRCPND = 1 << 12;

	env_cam = 1;

	wake_up_interruptible(cam_wait_queue);

	return IRQ_HANDLED;
}

static int cmos_ov7740_vidioc_querycap(struct file *file,void *priv,
					struct v4l2_capability *cap)
{
	memset(cap,0,sizeof *cap);
	strcpy(cap->driver,"cmos_ov7740");
	strcpy(cap->card,"cmos_ov7740");
	cap->version = 2;

	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE;

	return 0;

}

static int cmos_ov7740_vidioc_enum_fmt_vid_cap(struct file *file,void *priv,struct v4l2_fmtdesc *f)
{
	struct cmos_ov7740_fmt *fmt;

	if (f->index >= ARRAY_SIZE(formats))
		return -EINVAL;

	fmt = &formats[f->index];

	strlcpy(f->description,fmt->name,sizeof(f->description));
	f->pixelformat = fmt->fourcc;

	return 0;
	
}

static int cmos_ov7740_vidioc_g_fmt_vid_cap(struct file *file,void *priv,
							struct v4l2_format *f)
{
	return 0;
}

static int cmos_ov7740_vidioc_try_fmt_vid_cap(struct file *file,void *priv,struct v4l2_format *f)
{
	if (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
	{
		return -EINVAL;
	}

	if ((f->fmt.pix.pixelformat != V4L2_PIX_FMT_RGB565) && (f->fmt.pix.pixelformat != V4L2_PIX_FMT_RGB24))
		return -EINVAL;

	return 0;

}

static int cmos_ov7740_vidioc_s_fmt_vid_cap(struct file *file ,void *priv,struct v4l2_format *f)
{
	int ret = cmos_ov7740_vidioc_try_fmt_vid_cap(file, NULL, f);
	if (ret < 0)
		return ret;

	TargetHsize_Pr = f->fmt.pix.width;
	TargetVsize_Pr = f->fmt.pix.height;

	if (f->fmt.pix.pixelformat == V4L2_PIX_FMT_RGB565)
	{
		*CIPRSCCTRL &= ~(1 <<30);
		f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
		buf_size = f->fmt.pix.sizeimage;
		bytesperline = f->fmt.pix.bytesperline;
		
	}
	else if(f->fmt.pix.pixelformat == V4L2_PIX_FMT_RGB24)
	{
		*CIPRSCCTRL |= (1 <<30);
		f->fmt.pix.bytesperline = (f->fmt.pix.width * 32) >> 3;
		f->fmt.pix.sizeimage    = f->fmt.pix.height * f->fmt.pix.bytesperline;
		buf_size = f->fmt.pix.sizeimage;
		bytesperline = f->fmt.pix.bytesperline;	
	}
	
	*CIPRTRGFMT = (TargetHsize_Pr << 16) | (0x0 << 14)|(TargetVsize_Pr << 0);

	return 0;

}

static int cmos_ov7740_vidioc_reqbufs(struct file *file,void *priv,struct v4l2_requestbuffers *p)
{
	unsigned int order;

	order = get_order(buf_size);

	img_buff[0].order = order;
	img_buff[0].virt_base = __get_free_pages(GFP_KERNEL|__GFP_DMA,img_buff[0].order);
	if (img_buff[0].virt_base == (unsigned long)NULL)
	{
		printk("error0\n");
		goto error0;
	}
	img_buff[0].phy_base = __virt_to_phys(img_buff[0].virt_base);
	
	img_buff[1].order = order;
	img_buff[1].virt_base = __get_free_pages(GFP_KERNEL|__GFP_DMA,img_buff[1].order);
	if (img_buff[1].virt_base == (unsigned long)NULL)
	{
		printk("error1\n");
		goto error1;
	}
	img_buff[1].phy_base = __virt_to_phys(img_buff[1].virt_base);

	img_buff[2].order = order;
	img_buff[2].virt_base = __get_free_pages(GFP_KERNEL|__GFP_DMA,img_buff[0].order);
	if (img_buff[2].virt_base == (unsigned long)NULL)
	{
		printk("error2\n");
		goto error2;
	}
	img_buff[2].phy_base = __virt_to_phys(img_buff[0].virt_base);

	img_buff[3].order = order;
	img_buff[3].virt_base = __get_free_pages(GFP_KERNEL|__GFP_DMA,img_buff[3].order);
	if (img_buff[3].virt_base == (unsigned long)NULL)
	{
		printk("error3\n");
		goto error3;
	}
	img_buff[3].phy_base = __virt_to_phys(img_buff[3].virt_base);

	*CIPRCLRSA1 = img_buff[0].phy_base;
	*CIPRCLRSA2 = img_buff[1].phy_base;
	*CIPRCLRSA3 = img_buff[2].phy_base;
	*CIPRCLRSA4 = img_buff[3].phy_base;

	return 0;

error3:
	free_pages(img_buff[2].virt_base,order);
	img_buff[2].phy_base = (unsigned long)NULL;

error2:
	free_pages(img_buff[1].virt_base,order);
	img_buff[1].phy_base = (unsigned long)NULL;

error1:
	free_pages(img_buff[0].virt_base,order);
	img_buff[0].phy_base = (unsigned long)NULL;

error0:
		return -ENOMEM;
}

static void CalculateBurstSize(unsigned int hSize,unsigned int *mainBustrSize,unsigned int *remainedBustSize)
{
	unsigned int tmp;

	tmp = (hSize/4) %16;
	switch(tmp)
	{
		case 0:
			*mainBustrSize = 16;
			*remainedBustSize = 16;
			break;

		case 4:
			*mainBustrSize = 16;
			*remainedBustSize = 4;
			break;

		case 8:
			*mainBustrSize = 16;
			*remainedBustSize = 8;
			break;	
		default:
			tmp = (hSize/4)%8;
			switch(tmp)
			{
				case 0:
				*mainBustrSize = 8;
				*remainedBustSize = 8;
				break;	

				case 4:
				*mainBustrSize = 8;
				*remainedBustSize = 4;
				break;	

				defalut:
					*mainBustrSize = 4;
					tmp = (hSize/4)%4;
					*remainedBustSize = (tmp)?tmp:4;
					break;
			}
			break;
	}

}


static void camif_get_scaler_factor(u32 src,u32 tar,u32 *ratio,u32 *shift)
{
	if (src >= 64 *tar) {return;}
	else if (src >= 32*tar) {*ratio =32;*shift = 5;}
	else if (src >= 16*tar) {*ratio =16;*shift = 4;}
	else if (src >= 8*tar) {*ratio =8;*shift = 3;}
	else if (src >= 4*tar) {*ratio =4;*shift = 2;}
	else if (src >= 2*tar) {*ratio =2;*shift = 1;}
	else {*ratio = 1;*shift =0;}
}

static void cmos_ov7740_calculate_scaler_info(void)
{
	unsigned int sx,sy,tx,ty;

	sx = SRC_Width;
	sy = SRC_Height;
	tx = TargetHsize_Pr;
	ty = TargetVsize_Pr;

	printk("%s :SRC_in(%d, %d),Target_out("%d,%d")\n",__func__,sx,sy,tx,ty);

	camif_get_scaler_factor(sx, tx, &sc.PreHorRatio,&sc.H_Shift);
	camif_get_scaler_factor(sy, ty, &sc.PreVerRatio,&sc.V_Shift);

	sc.PreDstWidth = sx / sc.PreHorRatio;
	sc.PreDstHeight = sy/sc.PreVerRatio;

	sc.MainHorRatio = (sx << 8) / (tx << sc.H_Shift);
	sc.MAinVerRatio = (sy << 8) / (ty << sc.V_Shift);

	sc.SHfactor     = 10 - (sc.H_Shift + sc.V_Shift);
	sc.ScaleUpDown  = (tx >= sx)?1:0;

}

static int cmos_ov7740_vidioc_streamon(struct file *file,void *priv,enum v4l2_buf_type i)
{
	unsigned int Main_burst,Remained_burst;

	*CISRCFMT |= (0 << 30) | (0 <<29)| (CAM_SRC_HSIZE << 16)| (CAM_ORDER_CbYCry << 14)|(CAM_SRC_VSIZE <<0);
	
	*CIWDOFST |= (1 <<30)|(0xf << 12);
	*CIWDOFST |= (1 <<31)| (WinHorOfst << 16)|(WinVerOfst <<0);
	SRC_Width  =  CAM_SRC_HSIZE - 2 *WinHorOfst;
	SRC_Height =  CAM_SRC_VSIZE - 2 *WinVerOfst;

	*CIGCTRL |= (1<<29)| (0 << 27)| (0 <<26)| (0<<25)| (0 <<24);
	CalculateBurstSize(bytesperline,&Main_burst,&Remained_burst);
	*CIPRCTRL = (Main_burst << 19) | (Remained_burst << 14) | (0 << 2);
	cmos_ov7740_calculate_scaler_info();
	*CIPRSCPRERATIO = (sc.SHfactor << 28) | (sc.PreHorRatio << 16) | (sc.PreVerRatio << 0);
	*CIPRSCPREDST   = (sc.PreDstWidth << 16) | (sc.PreDstHeight << 0);
	*CIPRSCCTRL     |= (1 <<31)| (sc.ScaleUpDown << 28) | (sc.MainHorRatio << 16) | (sc.MAinVerRatio <<0); 
	*CIPRTAREA      = TargetHsize_Pr * TargetVsize_Pr;

	*CIIMGCPT = (1 << 31) | (1 <<29);
	*CIPRSCCTRL |= (1 << 15);

	return 0;
	
}

static int cmos_ov7740_vidioc_streamoff(struct file *file,void *priv,enum v4l2_buf_type t)
{
	*CIPRSCCTRL &= ~(1 <<15);
	*CIIMGCPT   &= ~((1 <<31) | (1 <<29));
	return 0;
}

static const struct v4l2_ioctl_ops cmos_ov7740_ioctl_ops = {
		.vidioc_querycap           = cmos_ov7740_vidioc_querycap,
		.vidoc_enum_fmt_vid_cap    = cmos_ov7740_vidioc_enum_fmt_vid_cap,
		.vidioc_g_fmt_vid_cap      = cmos_ov7740_vidioc_g_fmt_vid_cap,
		.vidioc_try_fmt_vid_cap    = cmos_ov7740_vidioc_try_fmt_vid_cap,
		.vidioc_s_fmt_vid_cap      = cmos_ov7740_vidioc_s_fmt_vid_cap,
		.vidioc_reqbufs            = cmos_ov7740_vidioc_reqbufs,
		.vidioc_streamon           = cmos_ov7740_vidioc_streamon,
		.vidioc_streamoff          = cmos_ov7740_vidioc_streamoff,

};

static int cmos_ov7740_open(struct file *file)
{
	return 0;
}


static int cmos_ov7740_close(struct file *file)
{
	return 0;
}

static ssize_t cmos_ov7740_read(struct file *filep,char __user *buf,size_t count,loff_t *pos)
{
	size_t end;
	int i;

	end = min_t(size_t,buf_size,count);

	wait_event_interruptible(cam_wait_queue,ev_cam);

	for (i=0;i <4;i++)
	{
		if (copy_to_user(buf, (void *)img_buff[i].virt_base,end))
			return -EFAULT;
	}

	ev_cam =0;

	return end;
	
}


static const struct v4l2_file_operations cmos_ov7740_fops = {
		.owner           = THIS_MODULE,
		.open            = cmos_ov7740_open,
		.release         = cmos_ov7740_close,
		.unlocked_ioctl  = video_ioctl2,
		.read            = cmos_ov7740_read,
	
};

static void cmos_ov7740_release(struct video_device *vdev)
{
	unsigned int order;

	order = get_order(buf_size);

	free_pages(img_buff[0].virt_base,order);
	img_buff[0].phy_base = (unsigned long)NULL;
	free_pages(img_buff[1].virt_base,order);
	img_buff[1].phy_base = (unsigned long)NULL;
	free_pages(img_buff[2].virt_base,order);
	img_buff[2].phy_base = (unsigned long)NULL;
	free_pages(img_buff[3].virt_base,order);
	img_buff[3].phy_base = (unsigned long)NULL;
	
}


static struct video_device cmos_ov7740_vdev = {
	.fops       =   &cmos_ov7740_fops,
	.ioctl_ops 	=   &cmos_ov7740_ioctl_ops,
	.release    =  cmos_ov7740_release,
	.name       =  "cmos_ov7740",
};

static void cmos_ov7740_gpio_cfg(void)
{
	*GPJCON = 0x2aaaaaa;
	*GPJDAT = 0;
	*GPJUP  = 0;
}

static void cmos_ov7740_camif_reset(void)
{
	*CISRCFMT |= (1 <<31);
	*CIGCTRL  |= (1 <<31);
	mdelay(10);
	*CIGCTRL &= ~(1<<31);
	mdelay(10);
}

static void cmos_ov7740_clk_cfg(void)
{
	struct clk *camif_clk;
	struct clk *camif_upll_clk;

	camif_clk = clk_get(NULL,"camif");
	if(!camif_clk || IS_ERR(camif_clk))
	{
			printk(KERN_INFO "failed to get CAMIF clock source\n");
	}
	clk_enable(camif_clk);

	camif_upll_clk = clk_get(NULL,"camif-upll");
	clk_set_rate(camif_upll_clk,240000000);
	mdelay(100);
}

static void cmos_ov7740_reset(void)
{
	*CIGCTRL |= (1 <<30);
	mdelay(30);
	*CIGCTRL &= ~(1 <<30);
	mdelay(30);
	*CIGCTRL |= (1 <<30);
	mdelay(30);

}


static void cmos_ov7740_init(void)
{
	unsigned int mid;
	int i;

	mid = i2c_smbus_read_byte_data(cmos_ov7740_client,0x0a) << 8;
	mid |= i2c_smbus_read_byte_data(cmos_ov7740_client, 0x0b);
	printk("manufacture ID = 0x%4x\n",mid);

	for (i=0;i < OV7740_INIT_REGS_SIZE;i++)
	{
		i2c_smbus_write_byte_data(cmos_ov7740_client, ov7740_setting_30fps_VGA_640_480[i].regaddr, ov7740_setting_30fps_VGA_640_480[i].value);
		mdelay(2);
	}
}

static int __devinit cmos_ov7740_probe(struct i2c_client *client,const struct i2c_device_id *id)

{
	printk("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);

	GPJCON = ioremap(0x560000d0,4);
	GPJDAT = ioremap(0x560000d4,4);
	GPJUP = ioremap(0x560000d8,4);

	CISRCFMT   = ioremap(0x4F00000,4);
	CIWDOFST   = ioremap(0x4F00004,4);
	CIGCTRL    = ioremap(0x4F00008,4);
	CIPRCLRSA1 = ioremap(0x4F0006C,4);
	CIPRCLRSA2  = ioremap(0x4F00070,4);	
	CIPRCLRSA3  = ioremap(0x4F00074,4);
	CIPRCLRSA4  = ioremap(0x4F00078,4);
	CIPRTRGFMT  = ioremap(0x4F0007C,4);
	CIPRCTRL    = ioremap(0x4F00080,4);
	CIPRSCPRERATIO = ioremap(0x4F000084, 4);
	CIPRSCPREDST = ioremap(0x4F000088, 4);
	CIPRSCCTRL = ioremap(0x4F00008C, 4);
	CIPRTAREA = ioremap(0x4F000090, 4);
	CIIMGCPT = ioremap(0x4F0000A0, 4);

	SRCPND = ioremap(0X4A000000, 4);
	INTPND = ioremap(0X4A000010, 4);
	SUBSRCPND = ioremap(0X4A000018, 4);

	cmos_ov7740_gpio_cfg();
	cmos_ov7740_camif_reset();
	cmos_ov7740_clk_cfg();
	cmos_ov7740_reset();
	cmos_ov7740_client = client;
	cmos_ov7740_init();

	if (request_irq(IRQ_S3C2440_CAM_C,cmos_ov7740_camif_irq_c,IRQF_DISABLED,"CAM_C",NULL))
		{
			printk("%s:request_irq failed\n",__func__);
		}

	
	if (request_irq(IRQ_S3C2440_CAM_P,cmos_ov7740_camif_irq_p,IRQF_DISABLED,"CAM_P",NULL))
		{
			printk("%s:request_irq failed\n",__func__);
		}

	return 0;
	
}

static int __deveixt cmos_ov7740_remove(struct i2c_client *client)
{
	printk("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
	iounmap(GPJCON);
	iounmap(GPJDAT);
	iounmap(GPJUP);

	iounmap(CISRCFMT);
	iounmap(CIWDOFST);
	iounmap(CIGCTRL);
	iounmap(CIPRCLRSA1);
	iounmap(CIPRCLRSA2);
	iounmap(CIPRCLRSA3);
	iounmap(CIPRCLRSA4);
	iounmap(CIPRTRGFMT);
	iounmap(CIPRCTRL);
	iounmap(CIPRSCPRERATIO);
	iounmap(CIPRSCPREDST);
	iounmap(CIPRSCCTRL);
	iounmap(CIPRTAREA);
	iounmap(CIIMGCPT);
	
	iounmap(SRCPND);
	iounmap(INTPND);
	iounmap(SUBSRCPND);

	free_irq(IRQ_S3C2440_CAM_C,NULL);
	free_irq(IRQ_S3C2440_CAM_P,NULL);
	video_unregister_device(&cmos_ov7740_vdev);
	return 0;
}

static const struct i2c_device_id cmos_ov7740_id_table[] = {
		{"cmos_ov7740",0},
		{}
};

static struct i2c_driver cmos_ov7740_driver = {
	.driver = {
		.name  = "cmos_ov7740",
		.owner = THIS_MODULE,	
	},
	.probe  = cmos_ov7740_probe,
	.remove = __devexit_p(cmos_ov7740_remove),
	.id_table = cmos_ov7740_id_table
};

static int cmos_ov7740_drv_init(void)
{
	i2c_add_driver(&cmos_ov7740_driver);
	return 0;
}

static void cmos_ov7740_drv_exit(void)
{
	i2c_del_driver(&cmos_ov7740_driver);
}

module_init(cmos_ov7740_drv_init);
module_init(cmos_ov7740_drv_exit);
MODULE_LICENES("GPL");



