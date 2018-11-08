#include<ros/ros.h>
#include <vector>
#include <stdio.h>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


//--------------------------------【createAlphaMat( )函数】--------------------------------
//		描述：创建带alpha通道的Mat
//-------------------------------------------------------------------------------------------------
void createAlphaMat(Mat &mat)
{
	for(int i = 0; i < mat.rows; ++i) {
		for(int j = 0; j < mat.cols; ++j) {
			Vec4b&rgba = mat.at<Vec4b>(i, j);
			rgba[0]= UCHAR_MAX;
			rgba[1]= saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);
			rgba[2]= saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);
			rgba[3]= saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
		}
	}
}



//-----------------------------------【ShowHelpText( )函数】----------------------------------
//          描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n\t\t\t非常感谢购买《OpenCV3编程入门》一书！\n");
	printf("\n\n\t\t\t此为本书OpenCV3版的第15个配套示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}

double division(int a, int b)
{
   if( b == 0 )
   {
      throw "Division by zero condition!";
   }
   return (a/b);
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "a15_Use_imwrite");
    
    //创建带alpha通道的Mat
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);

	ShowHelpText();

	vector<int> compression_params;//保存int类型元素的vector
	//此句代码的OpenCV2版为compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	//此句代码的OpenCV3版为：
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);//16
	compression_params.push_back(9);

	int x = 50;
	int y = 0;
	double z = 0;
	try {
		z = division(x, y);
    	cout << z << endl;
	}
	catch (const char* msg) {
    	cerr << msg << endl;
	}	
	
	//显示图片
	try{
		imwrite("透明Alpha值图.png", mat, compression_params);
		imshow("生成的png图",mat);
		//fprintf(stdout,"PNG图片文件的alpha数据保存完毕~\n可以在工程目录下查看由imwrite函数生成的图片\n");
		cout << "PNG图片文件的alpha存完啦~\n可在工程目录下看由imwrite函数生成的图片啦\n" << endl;
		waitKey(5000);//5s
	}
	catch(runtime_error& ex) {
		//fprintf(stderr,"图像转换成PNG格式发生错误：%s\n", ex.what());
		cout << "图像转换成PNG格式发生错误啦：%s\n"<< ex.what() << endl;
		return 1;
	}

	return 0;
}