// ArbeitProjektZwei.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include <string>

//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>
using namespace cv;
using namespace std;
// Global variables
Mat frame; //current frame
Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method
Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
char keyboard; //input from keyboard
void help();
void processVideo(char* videoFilename);
void help()
{
	cout
		<< "--------------------------------------------------------------------------" << endl
		<< "This program shows how to use background subtraction methods provided by " << endl
		<< " OpenCV. You can process both videos (-vid) and images (-img)." << endl
		<< endl
		<< "Usage:" << endl
		<< "./bg_sub {-vid <video filename>|-img <image filename>}" << endl
		<< "for example: ./bg_sub -vid video.avi" << endl
		<< "or: ./bg_sub -img /data/images/1.png" << endl
		<< "--------------------------------------------------------------------------" << endl
		<< endl;
}
int main(int argc, char* argv[])
{
	//print help information
	help();
	//create GUI windows
	namedWindow("Frame");
	namedWindow("FG Mask MOG 2");
	//create Background Subtractor objects
	pMOG2 = createBackgroundSubtractorMOG2(); //MOG2 approach
	if (strcmp("-vid", "-vid") == 0) {
		//input data coming from a video
		processVideo("..\\..\\..\\..\\GP010065.MP4");
	}
	//destroy GUI windows
	destroyAllWindows();
	return EXIT_SUCCESS;
}
void processVideo(char* videoFilename) {
	//create the capture object
	VideoCapture capture(videoFilename);
	if (!capture.isOpened()) {
		//error in opening the video input
		cerr << "Unable to open video file: " << videoFilename << endl;
		exit(EXIT_FAILURE);
	}
	//read input data. ESC or 'q' for quitting
	keyboard = 0;
	while (keyboard != 'q' && keyboard != 27) {
		//read the current frame
		if (!capture.read(frame)) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			continue;
			//exit(EXIT_FAILURE);
		}
		//update the background model
		pMOG2->apply(frame, fgMaskMOG2);
		//get the frame number and write it on the current frame
		stringstream ss;
		rectangle(frame, cv::Point(10, 2), cv::Point(100, 20),
			cv::Scalar(255, 255, 255), -1);
		ss << capture.get(CAP_PROP_POS_FRAMES);
		string frameNumberString = ss.str();
		putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
			FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
		//show the current frame and the fg masks
		imshow("Frame", frame);
		imshow("FG Mask MOG 2", fgMaskMOG2);
		//get the input from the keyboard
		keyboard = (char)waitKey(30);
	}
	//delete capture object
	capture.release();
}