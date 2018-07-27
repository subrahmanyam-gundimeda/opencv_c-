#include "videocapture.h"

void cVideoCapture::RecordVideo(){

	int i=0;
	while( true){
		Mat frame;
		*VideoDevice >> frame;
		if(frame.empty()){
			Logger<<"\n Failed to capture an image....";
			return;
		}
		VideoFile<<frame;
		imshow("video",frame);
		char c=(char)waitKey(20);
		if (c == 27){
			Logger<<"\n Esc character is pressed so stopping the video...";
			break;
		}
	}
}
void cVideoCapture::h264(){

	VideoFile.open("output.mp4",VideoWriter::fourcc('H','2','6','4'),/*VideoDevice->get(CAP_PROP_FPS)*/10,Size(1280,720));
	VideoDevice->set(CV_CAP_PROP_FRAME_WIDTH,1280);
	VideoDevice->set(CV_CAP_PROP_FRAME_HEIGHT,720);
	VideoDevice->set(CV_CAP_PROP_GAIN,0);

	if(!VideoDevice->isOpened()){
		Logger<<"\n Failed to connect to the camera.............";
	}
}


