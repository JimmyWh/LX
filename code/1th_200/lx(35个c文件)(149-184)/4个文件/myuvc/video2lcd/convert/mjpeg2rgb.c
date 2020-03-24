

#include <convert_manager.h>



static int isSupportMjpeg2Rgb(int iPixelFormatIn,
					int iPixelFormatOut)
{
	if (iPixelFormatIn != V4L2_PIX_FMT_MJPEG)
		return 0;
	
	if ((iPixelFormatOut != V4L2_PIX_FMT_RGB565) && (iPixelFormatOut != V4L2_PIX_FMT_RGB32))
	{
		return 0;	
	}
	return 1;
}

static int Mjpeg2RgbConvert(PT_FileMap ptFileMap, PT_PixelDatas ptPixelDatas)
{
	struct jpeg_decompress_struct tDInfo;
	//struct jpeg_error_mgr tJErr;
    int iRet;
    int iRowStride;
    unsigned char *aucLineBuffer = NULL;
    unsigned char *pucDest;
	T_MyErrorMgr tJerr;

    fseek(ptFileMap->tFp, 0, SEEK_SET);

	// 分配和初始化一个decompression结构体
	//tDInfo.err = jpeg_std_error(&tJErr);

	tDInfo.err               = jpeg_std_error(&tJerr.pub);
	tJerr.pub.error_exit     = MyErrorExit;

	if(setjmp(tJerr.setjmp_buffer))
	{
		/* 如果程序能运行到这里, 表示JPEG解码出错 */
        jpeg_destroy_decompress(&tDInfo);
        if (aucLineBuffer)
        {
            free(aucLineBuffer);
        }
        if (ptPixelDatas->aucPixelDatas)
        {
            free(ptPixelDatas->aucPixelDatas);
        }
		return -1;
	}

	jpeg_create_decompress(&tDInfo);

	// 用jpeg_read_header获得jpg信息
	jpeg_stdio_src(&tDInfo, ptFileMap->tFp);

    iRet = jpeg_read_header(&tDInfo, TRUE);

	// 设置解压参数,比如放大、缩小
    tDInfo.scale_num = tDInfo.scale_denom = 1;
    
	// 启动解压：jpeg_start_decompress	
	jpeg_start_decompress(&tDInfo);
    
	// 一行的数据长度
	iRowStride = tDInfo.output_width * tDInfo.output_components;
	aucLineBuffer = malloc(iRowStride);

    if (NULL == aucLineBuffer)
    {
        return -1;
    }

	ptPixelDatas->iWidth  = tDInfo.output_width;
	ptPixelDatas->iHeight = tDInfo.output_height;
	//ptPixelDatas->iBpp    = iBpp;
	ptPixelDatas->iLineBytes    = ptPixelDatas->iWidth * ptPixelDatas->iBpp / 8;
    ptPixelDatas->iTotalBytes   = ptPixelDatas->iHeight * ptPixelDatas->iLineBytes;
	ptPixelDatas->aucPixelDatas = malloc(ptPixelDatas->iTotalBytes);
	if (NULL == ptPixelDatas->aucPixelDatas)
	{
		return -1;
	}

    pucDest = ptPixelDatas->aucPixelDatas;

	// 循环调用jpeg_read_scanlines来一行一行地获得解压的数据
	while (tDInfo.output_scanline < tDInfo.output_height) 
	{
        /* 得到一行数据,里面的颜色格式为0xRR, 0xGG, 0xBB */
		(void) jpeg_read_scanlines(&tDInfo, &aucLineBuffer, 1);

		// 转到ptPixelDatas去
		CovertOneLine(ptPixelDatas->iWidth, 24, ptPixelDatas->iBpp, aucLineBuffer, pucDest);
		pucDest += ptPixelDatas->iLineBytes;
	}
	
	free(aucLineBuffer);
	jpeg_finish_decompress(&tDInfo);
	jpeg_destroy_decompress(&tDInfo);

    return 0;
}

static int Mjpeg2RgbConvert(PT_VideoBuf ptVideoBufIn,
				PT_VideoBuf ptVideoBufOut)
{
	return 0;
}

static int Mjpeg2RgbConvertExit(PT_VideoBuf ptVideoBufOut)
{
	return 0;
}


// 构造结构体
static T_VideoConvert g_tMipeg2RgbConvert = {
	.isSupport = isSupportMjpeg2Rgb,
	.Convert   = Mjpeg2RgbConvert,
	.ConvertExit = Mjpeg2RgbConvertExit,

};

//注册
int Mipeg2Yuv2RgbInit(void)
{
	initLut();
	return RegisterVideoConver(&g_tMipeg2RgbConvert);
}



