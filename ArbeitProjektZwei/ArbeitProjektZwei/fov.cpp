// ArbeitProjektZwei.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	// Aus Matlab: 
	// Focal length (pixels):   [  796.5049 +/- 8.1232      731.2438 +/- 7.5379  ]
	// Principal point(pixels) :[944.3560 + / -4.8782      508.2241 + / -5.0480]
	Mat C = (Mat_<double>(3, 3) << 796.5049, 0, 944.3560,
		0, 731.2438, 508.2241,
		0, 0, 1);

	// Bildgrösse
	cv::Size imageSize(1920, 1080);

	// Aus Sensorspez (IMX117) https://www.sony-semicon.co.jp/products_en/IS/sensor2/products/index.html 
	// 1/2.3'' -> https://en.wikipedia.org/wiki/Image_sensor_format#Table_of_sensor_formats_and_sizes
	double apertureWidth = 6.2;
	double apertureHeight = 4.5;

	// 1.4637518 = 0.00155 (Pixel/mm) * 944.3560 siehe principal point
	// 0.787747355 = 0.00155 (Pixel/mm) * 508.2241 siehe principal point
	cv::Point2d principalPoint(1.4637518, 0.787747355);

	// ???? 1.234582595 = 0.00155 (Pixel/mm) * 796.5049 siehe principal point
	double focalLength = 1.234582595;

	// = focal length x / focal length y
	double aspectRatio = 796.5049 / 731.2438;

	// Output 
	double fieldOfViewX;
	double fieldOfViewY;
	cv::calibrationMatrixValues(C, imageSize, apertureWidth, apertureHeight, fieldOfViewX, fieldOfViewY, focalLength, principalPoint, aspectRatio);
	cout << "fieldOfViewX: " << fieldOfViewX << " degree" << endl;
	cout << "fieldOfViewY: " << fieldOfViewY << " degree" << endl;
	cout << "focalLength: " << focalLength << " mm" << endl;

	double fovx = 2 * atan(1920 / (2 * 796.5049)) * 180.0 / CV_PI;
	double fovy = 2 * atan(1080 / (2 * 731.2438)) * 180.0 / CV_PI;
	cout << "fovx: " << fovx << " degree" << endl;
	cout << "fovy: " << fovy << " degree" << endl;

	return 0;
}