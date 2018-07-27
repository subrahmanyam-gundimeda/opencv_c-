/*
 * facedetect.h
 *
 *  Created on: 25-Jul-2018
 *      Author: subrahmanyam
 */

#ifndef SRC_FACEDETECT_H_
#define SRC_FACEDETECT_H_


#include <iostream>
#include <fstream>
#include <sstream>
#include<map>
#include <opencv2/face.hpp>
#include <opencv2/objdetect.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/video/video.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<cv.h>
#include<highgui.h>

#include "Logger.h"

using namespace cv;
using namespace cv::face;
using namespace std;

// Get the path to your CSV:
const string fn_haar = string("../database_xml/haarcascade_frontalface_default.xml");
const string fn_csv = string("../faces/list.csv");



class cFaceRecognizer{

public:
	cFaceRecognizer(int CameraID=0):iCameraID(CameraID),sHaarCascadexml(fn_haar),sCSVFile(fn_csv),bVideoEnabled(true){
		model =  LBPHFaceRecognizer::create(); //*/  /* EigenFaceRecognizer*/FisherFaceRecognizer::create();

		remove("../Video_output/output.mp4");
		myLogger.open("/tmp/facerecognizer.log");

		if(bVideoEnabled){
			bVideoEnabled =VideoFile.open("../Video_output/outputx.mp4",VideoWriter::fourcc('H','2','6','4'),10,Size(1280,720));
			//myLogger<<"\n Status is \t::"<<to_string(bVideoEnabled );
		}
	};
	~cFaceRecognizer(){

		if(bVideoEnabled){
			VideoFile.release();
		}
	};
	void read_csv();
	int getWidth();
	int getHeight();
	void load_haarcascade();
	void train();
	void StartStreamingFromVideoDevice();
	Ptr<face::FaceRecognizer> model;
	void VideoSave();
private:
	int iCameraID;
	string sHaarCascadexml;
	string sCSVFile;
	vector<Mat> images;
	vector<int> labels;
	CascadeClassifier haar_cascade;

	VideoWriter VideoFile;
	bool bVideoEnabled;
	cLogger myLogger;
};



#endif /* SRC_FACEDETECT_H_ */
