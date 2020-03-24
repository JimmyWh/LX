
#include <convert_manager.h>
#include "video_manager.h"
#include <config.h>
#include <fonts_manager.h>
#include <string.h>

static PT_VideoConver g_ptVideoConverHead = NULL;

/**********************************************************************
 * �������ƣ� RegisterVideoConver
 * ���������� ע��"����ģ��", ��ν����ģ�����ȡ���ַ�λͼ�ķ���
 * ��������� ptVideoConver - һ���ṹ��,�ں�"ȡ���ַ�λͼ"�Ĳ�������
 * ��������� ��
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
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
 * �������ƣ� ShowVideoConver
 * ���������� ��ʾ��������֧�ֵ�"����ģ��"
 * ��������� ��
 * ��������� ��
 * �� �� ֵ�� ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
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
 * �������ƣ� GetVideoConver
 * ���������� ��������ȡ��ָ����"����ģ��"
 * ��������� pcName - ����
 * ��������� ��
 * �� �� ֵ�� NULL   - ʧ��,û��ָ����ģ��, 
 *            ��NULL - ����ģ���PT_VideoConver�ṹ��ָ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
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
 * �������ƣ� FontsInit
 * ���������� ���ø�������ģ��ĳ�ʼ������
 * ��������� ��
 * ��������� ��
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
int VideoConvertInit(void)
{
	int iError;

	iError = Yuv2RgbInit();
	iError |= Mjpeg2RgbInit();
	iError |= Rgb2RgbInit();
	
	return iError;
}





