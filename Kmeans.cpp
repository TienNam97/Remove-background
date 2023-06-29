#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat K_Means(Mat Input, int K) {
	Mat samples(Input.rows * Input.cols, Input.channels(), CV_32F);
	for (int y = 0; y < Input.rows; y++)
		for (int x = 0; x < Input.cols; x++)
			for (int z = 0; z < Input.channels(); z++)
				if (Input.channels() == 3) {
					samples.at<float>(y + x * Input.rows, z) = Input.at<Vec3b>(y, x)[z];
				}
				else {
					samples.at<float>(y + x * Input.rows, z) = Input.at<uchar>(y, x);
				}

	Mat labels;
	int attempts = 5;
	Mat centers;
	kmeans(samples, K, labels, TermCriteria(TermCriteria::MAX_ITER | TermCriteria::EPS, 1000, 0.001), attempts, KMEANS_PP_CENTERS, centers);


	Mat new_image(Input.size(), Input.type());
	for (int y = 0; y < Input.rows; y++)
		for (int x = 0; x < Input.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x * Input.rows, 0);
			if (Input.channels() == 3) {
				for (int i = 0; i < Input.channels(); i++) {
					new_image.at<Vec3b>(y, x)[i] = centers.at<float>(cluster_idx, i);
				}
			}
			else {
				new_image.at<uchar>(y, x) = centers.at<float>(cluster_idx, 0);
			}
		}
	imshow("clustered image", new_image);
	return new_image;
}

int main() {

	int Clusters = 2;
	Mat Input_Image = imread("24.jpg");
	Mat Clustered_Image = K_Means(Input_Image, Clusters);
	Mat dst, temp, dst2, GrayClus;

	cv::cvtColor(Clustered_Image, GrayClus, cv::COLOR_BGR2GRAY);

	double thres = cv::threshold(GrayClus, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);

	//TH1: Cuong do pixel background <= Cuong do pixel foreground
	//bitwise_and(Input_Image, Input_Image, temp, dst);

	//TH2: Cuong do pixel background >= Cuong do pixel foreground
	bitwise_not(dst, dst2);
	bitwise_and(Input_Image, Input_Image, temp, dst2);

	cout << "Otsu Threshold : " << thres << endl;
	String window_name = "kmeans+threholded";
	namedWindow(window_name);
	imshow(window_name, temp);
	imwrite("result_24_k.jpg", temp);
	waitKey(0);
}