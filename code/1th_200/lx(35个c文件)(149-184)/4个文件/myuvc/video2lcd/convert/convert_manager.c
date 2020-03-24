
#include <convert_manager.h>
#include "video_manager.h"
#include <config.h>
#include <fonts_manager.h>
#include <string.h>

static PT_VideoConver g_ptVideoConverHead = NULL;

/**********************************************************************
 * 函数名称： RegisterVideoConver
 * 功能描述： 注册"字体模块", 所谓字体模块就是取出字符位图的方法
 * 输入参数： ptVideoConver - 一个结构体,内含"取出字符位图"的操作函数
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  韦东山	      创建
 ***********************************************************************/
int RegisterVideoConver(PT_VideoConver ptVideoConver)
{
	PT_VideoConver ptTmp;

	if (!g_ptVideoConverHead)
	{
		g_ptVideoConverHead   = ptVideoConver;
		ptVideoConver->ptNext = NULL;
	}
	else
	{
		ptTmp = g_ptVideoConverHead;
		while (ptTmp->ptNext)
		{
			ptTmp = ptTmp->ptNext;
		}
		ptTmp->ptNext     = ptVideoConver;
		ptVideoConver->ptNext = NULL;
	}

	return 0;
}


/**********************************************************************
 * 函数名称： ShowVideoConver
 * 功能描述： 显示本程序能支持的"字体模块"
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  韦东山	      创建
 ***********************************************************************/
void ShowVideoConver(void)
{
	int i = 0;
	PT_VideoConver ptTmp = g_ptVideoConverHead;

	while (ptTmp)
	{
		printf("%02d %s\n", i++, ptTmp->name);
		ptTmp = ptTmp->ptNext;
	}
}

/**********************************************************************
 * 函数名称： GetVideoConver
 * 功能描述： 根据名字取出指定的"字体模块"
 * 输入参数： pcName - 名字
 * 输出参数： 无
 * 返 回 值： NULL   - 失败,没有指定的模块, 
 *            非NULL - 字体模块的PT_VideoConver结构体指针
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  韦东山	      创建
 ***********************************************************************/
PT_VideoConver GetVideoConver(char *pcName)
{
	PT_VideoConver ptTmp = g_ptVideoConverHead;
	
	while (ptTmp)
	{
		if (strcmp(ptTmp->name, pcName) == 0)
		{
			return ptTmp;
		}
		ptTmp = ptTmp->ptNext;
	}
	return NULL;
}


/**********************************************************************
 * 函数名称： FontsInit
 * 功能描述： 调用各个字体模块的初始化函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  韦东山	      创建
 ***********************************************************************/
int VideoConvertInit(void)
{
	int iError;

	iError = Yuv2RgbInit();
	iError |= Mjpeg2RgbInit();
	iError |= Rgb2RgbInit();
	
	return iError;
}





