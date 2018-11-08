#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
#define WINDOW_NAME "【滑动条的创建&线性混合示例】"        //为窗口标题定义的宏 

//-----------------------------------【全局变量声明部分】--------------------------------------
//		描述：全局变量声明
//-----------------------------------------------------------------------------------------------
const int g_nMaxAlphaValue = 100;//Alpha值的最大值
int g_nAlphaValueSlider;//滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;

//声明存储图像的变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

//-----------------------------------【on_Trackbar( )函数】--------------------------------
//		描述：响应滑动条的回调函数
//------------------------------------------------------------------------------------------
void on_Trackbar( int, void* )
{
	ROS_INFO("on_Trackbar()");
	//求出当前alpha值相对于最大值的比例
	g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue ;
	//则beta值为1减去alpha值
	g_dBetaValue = ( 1.0 - g_dAlphaValue );

	//根据alpha和beta值进行线性混合
	addWeighted( g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

	//显示效果图
	imshow( WINDOW_NAME, g_dstImage );
}

//-----------------------------【ShowHelpText( )函数】--------------------------------------
//		描述：输出帮助信息
//-------------------------------------------------------------------------------------------------
//-----------------------------------【ShowHelpText( )函数】----------------------------------
//		描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t非常感谢购买《OpenCV3编程入门》一书！\n");
	printf("\n\n\t\t\t此为本书OpenCV3版的第17个配套示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}

//--------------------------------------【main( )函数】-----------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始执行
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{

	ros::init(argc, argv, "a17_CreateTrackerbar");
    //显示帮助信息
	ShowHelpText();

	//加载图像 (两图像的尺寸需相同)
	g_srcImage1 = imread("/home/muxi/catkin_test/src/learncv/src/1.jpg");
	g_srcImage2 = imread("/home/muxi/catkin_test/src/learncv/src/2.jpg");
	if( !g_srcImage1.data ) { printf("读取第一幅图片错误，请确定目录下是否有imread函数指定图片存在~！ \n"); return -1; }
	if( !g_srcImage2.data ) { printf("读取第二幅图片错误，请确定目录下是否有imread函数指定图片存在~！\n"); return -1; }

	//设置滑动条初值为70
	g_nAlphaValueSlider = 70;

	//创建窗体
	namedWindow(WINDOW_NAME, 1);

	//在创建的窗体中创建一个滑动条控件
	char TrackbarName[50];
	sprintf( TrackbarName, "透明值 %d", g_nMaxAlphaValue );

	createTrackbar( TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar );

	//结果在回调函数中显示
	on_Trackbar( g_nAlphaValueSlider, 0 );

	//按任意键退出
	waitKey(0);

	return 0;
}