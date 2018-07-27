#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
//#include <opencv2/contrib/contrib.hpp>
//#incldue <highgui.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include<vector>
using namespace std;
using namespace cv;
using namespace face;


static void read_csv(const string& filename, vector<Mat>& images,
    vector<int>& labels, char separator = ';') {
std::ifstream file(filename.c_str(), ifstream::in);
if (!file) {
    string error_message =
            "No valid input file was given, please check the given filename.";
    // CV_Error(CV_StsBadArg, error_message);
}
string line, path, classlabel;
while (getline(file, line)) {
    stringstream liness(line);
    getline(liness, path, separator);
    getline(liness, classlabel);
    if (!path.empty() && !classlabel.empty()) {
        images.push_back(imread(path, 0));
        labels.push_back(atoi(classlabel.c_str()));
    }
}}

int main() {
String face_cascade_name = "face.xml";
String csvPath = "/home/longnhkse60984/csv.ext";
String eye_cascade_name = "haarcascade_eye.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";
vector<Mat> images;
vector<int> labels;
try {
    read_csv(csvPath, images, labels);
} catch (cv::Exception& e) {
    cerr << "Error opening file \"" << csvPath << "\". Reason: " << e.msg
            << endl;
    // nothing more we can do
    exit(1);
}
int im_width = images[0].cols;
int im_height = images[0].rows;
// Create a FaceRecognizer and train it on the given images:
Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
model->train(images, labels);
//CascadeClassifier haar_cascade;
face_cascade.load(face_cascade_name);
Mat frame = imread("aaa.jpg");
Mat original = frame.clone();
vector<Rect> faces;
Mat frame_gray;

cvtColor(original, frame_gray, COLOR_BGR2GRAY);
equalizeHist(frame_gray, frame_gray);

//-- Detect faces
face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2,
        CASCADE_FIND_BIGGEST_OBJECT | CASCADE_DO_ROUGH_SEARCH,
        Size(30, 30));
Mat face = frame_gray(faces[0]);
Mat face_resized;
resize(face, face_resized, Size(im_width,im_height),1.0,1.0,INTER_CUBIC);
int prediction = model->predict(face_resized);
cout << prediction;
// That's it for learning the Face Recognition model. You now
// need to create the classifier for the task of Face Detection.
// We are going to use the haar cascade you have specified in the
// command line arguments:
//
waitKey(0);
return 0;}
