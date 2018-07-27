#include<iostream>
#include<unistd.h>
#include<fstream>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/video/video.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<cv.h>
#include<highgui.h>

using namespace std;
using namespace cv;

const string sLogName="/tmp/snapshot.log";

class cLog{

public:
	cLog(string logname="/tmp/snapshot.log"){
		oFileHandler.open(sLogName);
		if(!oFileHandler.is_open()){
			cout<<"\n Unable to create a logger file please take care of this first";
		}
		else{
			cout<<"\n Success in logger creation";
		}

	}
	~cLog(){

		oFileHandler.close();
	}

	void operator<<(string texttoadd){
	  oFileHandler<<texttoadd;
	}

private:
	ofstream oFileHandler;

};

cLog Logger;

bool crosscheckargs(int argc){
if(argc != 3){
 	cout<<"\n Please follow the syntax::\t \"filename\" \"personame number_of_pics_to_be_taken\"";
	return false;
}
	return true;
}

int main(int argc, char* argv[]){
	
	if(crosscheckargs(argc) == false){
		return -1;
	}

	VideoCapture *VideoDevice = new VideoCapture(0);
	VideoDevice->set(CV_CAP_PROP_FRAME_WIDTH,1280);
	VideoDevice->set(CV_CAP_PROP_FRAME_HEIGHT,720);
	VideoDevice->set(CV_CAP_PROP_GAIN,0);
	if(!VideoDevice->isOpened()){
		cout<<"\n Failed to connect to the camera :-(";
	}
	int i =0;
	int num_of_pics = atoi(argv[2]);

	while( i++<num_of_pics ){
		Mat frame;
		*VideoDevice >> frame;
		if(frame.empty()){
			cout<<"\n Failed to capture an image.. :-(";
			return -1;
		}
		string name = string(argv[1]);
		name += std::to_string(i);
		name += ".jpg";
		imwrite(name,frame);
		//sleep(2);
	}
	VideoDevice->release();
	return 0;
}
