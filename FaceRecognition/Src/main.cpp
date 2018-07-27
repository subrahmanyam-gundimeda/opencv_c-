/*
 * main.cpp

 *
 *  Created on: 25-Jul-2018
 *      Author: subrahmanyam
 */

#include "facedetect.h"

int main(int argc, const char *argv[]) {

	cFaceRecognizer FaceRecog;

	try {
		FaceRecog.read_csv();
	} catch (cv::Exception& e) {
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		exit(1);
	}


	//Ptr<face::FaceRecognizer> model = /*LBPHFaceRecognizer::create(); //*/ /*FisherFaceRecognizer */EigenFaceRecognizer::create();
//	model->train(images, labels);

	FaceRecog.model->setLabelInfo(0,"Subbu");

	//update_images_santosh(images, labels);
	//model->update(images,labels);
	FaceRecog.model->setLabelInfo(1,"Santosh");

	//update_images_kumari(images, labels);
	//model->update(images,labels);
	FaceRecog.model->setLabelInfo(2,"Kumari");


	//FaceRecog.model->setLabelInfo(3,"Umesh");

FaceRecog.model->setLabelInfo(4,"Suryanshu");


	FaceRecog.train();

	FaceRecog.load_haarcascade();
	FaceRecog.StartStreamingFromVideoDevice();
	return 0;
}


