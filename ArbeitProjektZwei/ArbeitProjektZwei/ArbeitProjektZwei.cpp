// ArbeitProjektZwei.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main2() {

	// Create a VideoCapture object and open the input file
	// If the input is the web camera, pass 0 instead of the video file name
	VideoCapture cap("..\\..\\..\\..\\GP010065.MP4");

	// Check if camera opened successfully
	if (!cap.isOpened()) {
		cerr << "Error opening video stream or file" << endl;
		return -1;
	}

	while (1) {
		Mat frame;
		// Capture frame-by-frame
		cap >> frame;
		// If the frame is empty, break immediately
		if (!frame.empty()) {
			//break;
			// Display the resulting frame
			imshow("Frame", frame);
		}

		// Press  ESC on keyboard to exit
		char c = (char)waitKey(25);
		if (c == 27)
			break;
	}

	// When everything done, release the video capture object
	cap.release();

	// Closes all the frames
	destroyAllWindows();

	return 0;
}