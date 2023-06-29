#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>


using namespace std;
using namespace cv;

int main() {

	Mat Img = imread("24.jpg", 0);
	Mat Img1 = imread("24.jpg", 1);
	Mat dst, temp, dst2, otsu;
	double thres = cv::threshold(Img, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);

	//TH1: Cuong do pixel background <= Cuong do pixel foreground
	//bitwise_and(Img1, Img1, temp, dst);

	//TH2: Cuong do pixel background >= Cuong do pixel foreground
	bitwise_not(dst, dst2);
	bitwise_and(Img1, Img1, temp, dst2);

	//double thres = cv::threshold(Img, dst, 0, 255, THRESH_OTSU);
	//thres = 1.2 * thres;
	//cv::threshold(Img, otsu, thres, 255, cv::THRESH_BINARY);
	//bitwise_not(otsu, dst2);
	//bitwise_and(Img1, Img1, temp, dst);

	cout << "Otsu Threshold : " << thres << endl;
	String window_name = "threholded";
	namedWindow(window_name);
	imshow(window_name, temp);
	imwrite("result_24.jpg", temp);
	//imshow(window_name, otsu);
	waitKey(0);
}