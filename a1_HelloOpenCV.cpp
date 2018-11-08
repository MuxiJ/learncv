#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp> 
using namespace cv;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "a1_HelloOpenCV");
    
    //【1】读入一张图片
	// Mat img=imread("/home/muxi/catkin_test/src/learncv/src/cat_image.jpg",-4);
	// // 【2】在窗口中显示载入的图片
	// imshow("【载入的图片】",img);
	// // 【3】等待6000ms后窗口自动关闭
	// waitKey(6000);

	// 【1】读入一张图片，载入图像
	Mat srcImage = imread("/home/muxi/catkin_test/src/learncv/src/cat_image.jpg");
	// 【2】显示载入的图片
	imshow("【原始图】",srcImage);
	// 【3】等待任意按键按下
	waitKey(0);

    return 0;
}