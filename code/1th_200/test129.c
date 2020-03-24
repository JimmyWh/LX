
static int getNativeWindowFormat(int format)
{
	int nativeFormat = HAL_PIXE_FORMAT_YCbCr_422_I;
	
	switch(format)
	{
		case V4L2_PIX_FMT_YVU420:
			nativeFormat = HAL_PIXE_FORMAT_YV12;
		break;
		
		
	}
	
	return nativeFormat;
}