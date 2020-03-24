
#include <config.h>
#include <video_manager.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <poll.h>


//int poll(struct pollfd *fds, nfds_t nfds, int timeout);

static int v4l2GetFrameForReadWrite(PT_VideoDevice ptVideoDevice,
PT_VideoBuf ptVideoBuf);

static int v4l2PutFrameForReadWrite(PT_VideoDevice ptVideoDevice,
	PT_VideoBuf ptVideoBuf);

static T_VideoOpr g_tV4l2VideoOpr;

static int g_aiSupportedFormats[] = 
{
	V4L2_PIX_FMT_YUYV,
	V4L2_PIX_FMT_MJPEG,
	V4L2_PIX_FMT_RGB565};

static int isSupportThisFormat(int iPixelFormat)
{
	int i;
	for (i=0;i < sizeof(g_aiSupportedFormats)/sizeof(g_aiSupportedFormats[0]);i++)
	{
		if (g_aiSupportedFormats[i] == iPixelFormat)
			return 1;
	}
	return 0;

}


static int v4l2InitDevice(char *strDevName,PT_VideoDevice ptVideoDevice)
{
	int iFd;
	int iError,ret;
	struct v4l2_requestbuffers tV4l2ReqBufs;
	struct v4l2_capability tV4l2Cap;
	struct v4l2_format tV4L2Fmt;
	struct v4l2_fmtdesc tFmtDesc;
	struct v4l2_buffer  tV4l2Buf;
	
	int iLcdWidth;
	int iLcdHeigt;
	int iLcdBpp;
	
 	iFd = open(strDevName,O_RDWR);
	if (iFd <0)
	{
		DBG_PRINTF("cannot open %s\n",strDevName);
		return -1;
	}

	ptVideoDevice->iFd = iFd;
	
	iError = ioctl(iFd,VIDIOC_QUERYCAP,&tV4l2Cap);
    memset(&tV4l2Cap, 0, sizeof(struct v4l2_capability));
    iError = ioctl(iFd, VIDIOC_QUERYCAP, &tV4l2Cap);
    if (iError < 0) 
	{
		DBG_PRINTF("Error opening device %s: unable to query device.\n",strDevName);
		goto err_exit;
    }

	if (!(tV4l2Cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
	{
		DBG_PRINTF("%s is not a video capture device\n",strDevName);
		
		goto err_exit;
	}

	if (tV4l2Cap.capabilities & V4L2_CAP_STREAMING) 
	{
		DBG_PRINTF("%s supports streaming i/o \n",strDevName);
	    goto fatal;
	}
	
	if (tV4l2Cap.capabilities & V4L2_CAP_READWRITE) 
	{
	    DBG_PRINTF("%s supports read i/o\n", strDevName);
	    goto fatal;
	}

	////////
	memset(&tFmtDesc, 0, sizeof(tFmtDesc));
	tFmtDesc.index = 0;
	tFmtDesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	while ((iError= ioctl(iFd, VIDIOC_ENUM_FMT, &tFmtDesc)) == 0) 
	{
		if (isSupportThisFormat(tFmtDesc.pixelformat))
		{
			ptVideoDevice->iPixelFormat = tFmtDesc.pixelformat;
			break;
		}	
		tFmtDesc.index++;
	}

	if (!ptVideoDevice->iPixelFormat)
	{
		DBG_PRINTF("%cannot support the format of this device\n");
	    goto fatal;
	}
	
	//set format in

	GetDispResolution(&iLcdWidth,&iLcdHeigt,&iLcdBpp);
	memset(&tV4L2Fmt, 0, sizeof(struct v4l2_format));
    tV4L2Fmt.fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    tV4L2Fmt.fmt.fmt.pix.pixelformat = ptVideoDevice->iPixelFormat;
    tV4L2Fmt.fmt.fmt.pix.width       = iLcdWidth;
    tV4L2Fmt.fmt.fmt.pix.height      = iLcdHeigt;
    tV4L2Fmt.fmt.fmt.pix.field       = V4L2_FIELD_ANY;
    iError= ioctl(iFd, VIDIOC_S_FMT, &tV4L2Fmt);
    if (iError < 0) 
	{
		DBG_PRINTF("Unable to set format\n");
		goto err_exit;
    }
	ptVideoDevice->iWidth  = tV4L2Fmt.fmt.fmt.pix.width;
	ptVideoDevice->iHeight = tV4L2Fmt.fmt.fmt.pix.height;  

	/* request buffers */
    memset(&tV4l2ReqBufs, 0, sizeof(struct v4l2_requestbuffers));
    tV4l2ReqBufs.count  = NB_BUFFER;
    tV4l2ReqBufs.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    tV4l2ReqBufs.memory = V4L2_MEMORY_MMAP;

    iError= ioctl(iFd, VIDIOC_REQBUFS, &tV4l2ReqBufs);
    if (iError < 0) 
	{
		DBG_PRINTF("Unable to allocate buffers\n");
		goto err_exit;
    } 

	ptVideoDevice->iVideoBufCnt = tV4l2ReqBufs.count; 

	if (tV4l2Cap.capabilities & V4L2_CAP_STREAMING)
	{
		/* map the buffers */
	   for (i = 0; i < ptVideoDevice->iVideoBufCnt; i++) 
	   {
			memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
			tV4l2Buf.index    = i;
			tV4l2Buf.type     = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			tV4l2Buf.memory   = V4L2_MEMORY_MMAP;
			iError= ioctl(iFd, VIDIOC_QUERYBUF, &tV4l2Buf);
			if (iError)
			{
			    DBG_PRINTF("Unable to query buffer\n");
			    goto err_exit;
			}
			
			ptVideoDevice->iVideoBufMaxLen = tV4l2Buf.length;
			
			ptVideoDevice->pucVideBuf[i] = mmap(0 /* start anywhere */ ,
					  tV4l2Buf.length, PROT_READ, MAP_SHARED, iFd,
					  tV4l2Buf.m.offset);
			if (ptVideoDevice->pucVideBuf[i] == MAP_FAILED)
			{
			    DBG_PRINTF("Unable to map buffer\n");
			    goto err_exit;
			}
	    }
		 /* Queue the buffers. */
		for (i = 0; i < ptVideoDevice->iVideoBufCnt; i++) 
		{
			memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
			tV4l2Buf.index  = i;
			tV4l2Buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			tV4l2Buf.memory = V4L2_MEMORY_MMAP;
			iError= ioctl(iFd, VIDIOC_QBUF, &tV4l2Buf);
			if (iError) 
			{
			    DBG_PRINTF("Unable to queue buffer.\n");
			    goto err_exit;
			}
	    }
		}
		else if (tV4l2Cap.capabilities & V4L2_CAP_READWRITE)
		{
			g_tV4l2VideoOpr.GetFrame = v4l2GetFrameForReadWrite;
			g_tV4l2VideoOpr.PutFrame = v4l2PutFrameForReadWrite;

			ptVideoDevice->iVideoBufCnt = 1;
			//在程序所能支持的格式里，一个像素最多需要4个字节
			ptVideoDevice->iVideoBufMaxLen = (ptVideoDevice->iWidth * ptVideoDevice->iHeight * 4);
			ptVideoDevice->pucVideBuf[0] = malloc(ptVideoDevice->iVideoBufMaxLen);
			
		}


		
	return 0;
	
err_exit:
	close(iFd);
	retunr -1;
	
}

static int v4l2ExitDevice(PT_VideoDevice ptVideoDevice)
{
	int i;
	for (i = 0; i < ptVideoDevice->iVideoBufCnt; i++) 
	{
		if (ptVideoDevice->pucVideBuf[i])
		{
			munmap(ptVideoDevice->pucVideBuf[i],ptVideoDevice->iVideoBufMaxLen);
			ptVideoDevice->pucVideBuf[i] = NULL;
		}
	}	
	
	close(ptVideoDevice->iFd);
	
	return 0;
}

static int v4l2GetFrameForStreaming(PT_VideoDevice ptVideoDevice,PT_VideoBuf ptVideoBuf)
{
	//poll
	struct pollfd tFds[1];
	int iRet;
	struct v4l2_buffer tV4l2Buf;

	tFds[0].fd       = ptVideoDevice->iFd;
	tFds[0].events   = POLLIN;
	iRet = poll(tFds,1,-1);
	if (iRet <=0)
	{
		DBG_PRINTF("poll error!\n");
		return -1;
	}
	
	memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
    tV4l2Buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    tV4l2Buf.memory = V4L2_MEMORY_MMAP;
    iRet = ioctl(ptVideoDevice->iFd, VIDIOC_DQBUF, &tV4l2Buf);
    if (iRet) 
	{
		DBG_PRINTF("Unable to dequeue buffer.\n");
		return -1;
    }
	ptVideoDevice->iVideoBufCurIndex = tV4l2Buf.index;
	
	ptVideoBuf->iPixelFormat = ptVideoDevice->iPixelFormat;
	ptVideoBuf->tPixelDatas.iWidth      = ptVideoDevice->iWidth;
	ptVideoBuf->tPixelDatas.iHeight     = ptVideoDevice->iHeight;
	ptVideoBuf->tPixelDatas.iBpp =(ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_YUYV)?16:\
							(ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_MJPEG)?:0,\
							(ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_RGB565)?:16;
	ptVideoBuf->tPixelDatas.iLineBytes=ptVideoDevice->iWidth* \
		ptVideoBuf->tPixelDatas.iBpp/8;
	ptVideoBuf->tPixelDatas.iTotalBytes = tV4l2Buf->bytesused;
	ptVideoBuf->tPixelDatas.aucPixelDatas = ptVideoDevice->pucVideBuf[tV4l2Buf.index];
	
	return 0;
}

static int v4l2PutFrameForStreaming(PT_VideoDevice ptVideoDevice,PT_VideoBuf ptVideoBuf)
{
	struct v4l2_buffer tV4l2Buf;
	int iError;
	memset(&tV4l2Buf, 0, sizeof(struct v4l2_buffer));
	tV4l2Buf.index = ptVideoDevice->iVideoBufCurIndex;
	tV4l2Buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	tV4l2Buf.memory = V4L2_MEMORY_MMAP;
	iError = ioctl(ptVideoDevice->iFd, VIDIOC_QBUF, &tV4l2Buf);
	if (iError) {
	    DBG_PRINTF("Unable to queue buffer\n");
	    return -1;
	}
	return 0;
}

static int v4l2GetFrameForReadWrite(PT_VideoDevice ptVideoDevice,PT_VideoBuf ptVideoBuf)
{	
	int iRet;
	iRet  = read(ptVideoDevice->iFd,ptVideoDevice->pucVideBuf[0],
		ptVideoDevice->iVideoBufMaxLen);
	if (iRet < 0)
	{
		return -1;
	}
	ptVideoBuf->iPixelFormat = ptVideoDevice->iPixelFormat;
	ptVideoBuf->tPixelDatas.iWidth		= ptVideoDevice->iWidth;
	ptVideoBuf->tPixelDatas.iHeight 	= ptVideoDevice->iHeight;
	ptVideoBuf->tPixelDatas.iBpp =(ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_YUYV)?16:\
							(ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_MJPEG)?:0,\
							(ptVideoDevice->iPixelFormat == V4L2_PIX_FMT_RGB565)?:16;
	ptVideoBuf->tPixelDatas.iLineBytes=ptVideoDevice->iWidth* \
		ptVideoBuf->tPixelDatas.iBpp/8;
	ptVideoBuf->tPixelDatas.iTotalBytes = iRet;
	ptVideoBuf->tPixelDatas.aucPixelDatas = ptVideoDevice->pucVideBuf[0];
		
	return 0;
}


static int v4l2PutFrameForReadWrite(PT_VideoDevice ptVideoDevice,PT_VideoBuf ptVideoBuf)
{
	
	return 0;
}


static int v4l2StartDevice(PT_VideoDevice ptVideoDevice)
{
	int itype = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int iErro;

    iErro = ioctl(ptVideoDevice->iFd, VIDIOC_STREAMON, &itype);
    if (iErro) {
		DBG_PRINTF("Unable to start capture.\n");
		return -1;
    }
	return 0;
}


static int v4l2StopDevice(PT_VideoDevice ptVideoDevice)
{
	int itype = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int iErro;

    iErro = ioctl(ptVideoDevice->iFd, VIDIOC_STREAMOFF, &itype);
    if (iErro) {
		DBG_PRINTF("Unable to stop capture\n");
		return -1;
    }
	return 0;
}


//构造一个VideoOpr结构体
static T_VideoOpr g_tV4l2VideoOpr ={
	.name        = "v4l2",
    .InitDevice  = v4l2InitDevice,
    .ExitDevice  = v4l2ExitDevice,
    .GetFrame    = v4l2GetFrameForStreaming,
    .PutFrame    = v4l2PutFrameForStreaming,
    .StartDevice = v4l2StartDevice,
    .StopDevice  = v4l2StopDevice,
};

//注册这个结构体
int v4l2Init(void)
{
	return RegisterVideoOpr(&g_tV4l2VideoOpr);

}

