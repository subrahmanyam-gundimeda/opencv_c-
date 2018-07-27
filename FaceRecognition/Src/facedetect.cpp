#include "facedetect.h"

void cFaceRecognizer::read_csv( )
{
	char separator = ';';
	std::ifstream file(sCSVFile.c_str(), ifstream::in);
	string path_photos = "";

	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		// CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);

		if(!path.empty() && !classlabel.empty()) {
			images.push_back(imread(path,CV_LOAD_IMAGE_GRAYSCALE)); //CV_LOAD_IMAGE_GRAYSCALE
			labels.push_back(atoi(classlabel.c_str()));
		}
	}

}
int cFaceRecognizer::getWidth(){
	return  images[0].cols;
}
int cFaceRecognizer::getHeight(){
	return images[0].rows;
}
void cFaceRecognizer::load_haarcascade(){
	haar_cascade.load(sHaarCascadexml);
}
void cFaceRecognizer::train(){
	model->train(images,labels);
}
void cFaceRecognizer::StartStreamingFromVideoDevice(){

	VideoCapture cap(iCameraID);
	if(!cap.isOpened()) {
		cout<<  "Capture Device ID " << to_string(iCameraID) << "cannot be opened." << endl;
		return;
	}
	cap.set(CV_CAP_PROP_FRAME_WIDTH,1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,720);
	cap.set(CV_CAP_PROP_GAIN,0);
	cout<<"cap.get(CAP_PROP_FPS)::"<<cap.get(CAP_PROP_FPS);
	cap.set(CAP_PROP_FPS,cap.get(CAP_PROP_FPS));
	int im_width = getWidth();
	int im_height =getHeight();

	Mat frame;
	for(;;) {
		cap >> frame;

		Mat original = frame.clone();
		Mat gray;
		cvtColor(original, gray, CV_BGR2GRAY);

		// Find the faces in the frame:
		vector< Rect_<int> > faces;
		haar_cascade.detectMultiScale(original, faces,1.1,3,CV_HAAR_FIND_BIGGEST_OBJECT);//,1.09,3,CV_HAAR_FIND_BIGGEST_OBJECT);
		// At this point you have the position of the faces in
		// faces. Now we'll get the faces, make a prediction and
		// annotate it in the video. Cool or what?
		for(int i = 0; i < faces.size(); i++) {
			// Process face by face:
			Rect face_i = faces[i];
			// Crop the face from the image. So simple with OpenCV C++:
			Mat face = gray(face_i);
			Mat face_resized;

			//cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
			// Now perform the prediction, see how easy that is:
			//int prediction = model->predict(face_resized);
			int predictedLabel = -1;
			double predicted_confidence = 0.0;
			// Get the prediction and associated confidence from the model
			model->predict(face, predictedLabel, predicted_confidence);
			if(predicted_confidence > 50){
				rectangle(original, face_i, CV_RGB(0, 255,0), 1);
				// Create the text we will annotate the box with:
				string box_text = model->getLabelInfo(predictedLabel);;
				// Calculate the position for annotated text (make sure we don't
				// put illegal values in there):
				int pos_x = std::max(face_i.tl().x - 10, 0);
				int pos_y = std::max(face_i.tl().y - 10, 0);
				// And now put it into the image:
				putText(original, box_text, Point(pos_x+5, pos_y+5), FONT_HERSHEY_PLAIN, 1.5, CV_RGB(0,255,0), 1);
			}
		//	std::cout<<"\n The predicted_label returned is: \t"<<predictedLabel;
			//cout<<"The predicted_label returned is: \t"<<to_string(predictedLabel);
//			std::cout<<"\n The predicted_confidence returned is: \t"<<predicted_confidence;


		}
		// Show the result:
		imshow("face_recognizer", original);
		if(bVideoEnabled){
			//VideoFile.write(original);
			VideoFile<<original;
		}
		// And display it:
		char key = (char) waitKey(20);
		// Exit this loop on escape:
		if(key == 27)
			break;
	}
}
void cFaceRecognizer::VideoSave(){

}

