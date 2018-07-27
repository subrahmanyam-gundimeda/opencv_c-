#/bin/bash
g++ -std=c++11  `pkg-config  --cflags --libs opencv` videocapture.h videocapture.cpp main.cpp -o executable_binary    -I /usr/local/include -L /usr/local/lib -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_face -lopencv_contrib -lopencv_imgproc -lopencv_objdetect -lopencv_video
