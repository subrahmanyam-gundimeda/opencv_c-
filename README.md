FaceRecognition using opencv with C++ on BeagleboneBlack. 

#opencv_C++
This branch contains the code for identifying the face(face detection), image capturing and face recognition using popular opensource framework OpenCV with version 4.0. The code was written in C++ alone. This has been tested on Ubuntu and ArchLinux and BeagleboneBlack Rev c. The accuracy of Facerecognition is far from best to use in the standards as it mostly depends on angle of picture taken for the sample(train). The algorithm used is LBPH for being independent on light conditions. I hope this tutorials helps for the users who are willing to use my code. 
Note: In order to use the face recognition functionalities then you need to download and compile OpenCV along with other repo Opencv_Contrib module. This has been well covered in OpenCV documentation.
Sometimems `pkg-config  --cflags --libs opencv` won't add all libraries itself so better cross check or add required libraries to the environment variables or append at the compilation explicitly which i have preferred here in compilation.sh for each module.
