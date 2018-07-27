/*
 * videocapture.h
 *
 *  Created on: 25-Jul-2018
 *      Author: subrahmanyam
 */

#ifndef POC1_VIDEOCAPTURE_VIDEOCAPTURE_H_
#define POC1_VIDEOCAPTURE_VIDEOCAPTURE_H_

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/video/video.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<highgui.h>
#include<opencv2/videoio.hpp>
//#include<memory>
using namespace std;
using namespace cv;

const string sLogName="/tmp/video.log";

class cLog{

public:
	cLog(){
		oFileHandler.open(sLogName);
		if(!oFileHandler.is_open()){
			cout<<"\n Unable to create a logger file please take care of this first";
		}
		else{
			cout<<"\n Success in logger creation";
			oFileHandler<<".........Successfully created the logger..........";
		}

	}
	~cLog(){

		oFileHandler.close();
	}

	void operator<<(string texttoadd){
		oFileHandler<<endl<<texttoadd;
	}

private:
	ofstream oFileHandler;

};

class cVideoCapture{

public:
	cVideoCapture(int deviceid =0):iCameraID(deviceid){

		VideoDevice = new VideoCapture(iCameraID);
		Logger<<string(" The camera device id is:")+ to_string(iCameraID);
	};
	~cVideoCapture(){
		if(VideoDevice)
			delete VideoDevice;
		VideoFile.release();
		Logger<<"Cleared all memory";
	}
	void h264();
	void RecordVideo();
private:
	int iCameraID;
	VideoCapture *VideoDevice;
	VideoWriter VideoFile;
	cLog Logger;
};


#endif /* POC1_VIDEOCAPTURE_VIDEOCAPTURE_H_ */
