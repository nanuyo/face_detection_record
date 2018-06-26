/* 

 DETECT DIFFERENT BODY PARTS USING HAAR-LIKE FEATURES

 AUTHOR: PRATEEK JOSHI

*/

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

#include "detectBodyParts.h"

using namespace std;
using namespace cv;

#define ENABLE_FACE_DETECTION 1
#define ENABLE_EYE_DETECTION 0
#define ENABLE_EAR_DETECTION 0
#define ENABLE_MOUTH_DETECTION 0
#define ENABLE_NOSE_DETECTION 0
#define ENABLE_SMILE_DETECTION 0
#define ENABLE_LOWERBODY_DETECTION 0
#define ENABLE_UPPERBODY_DETECTION 0
#define ENABLE_FULLBODY_DETECTION 0

int main( int argc, const char** argv )
{
	//char* gst = "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)I420, framerate=(fraction)120/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)I420 ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
	
    VideoCapture capture(0); // capture video from CSI camera
	//VideoCapture capture2(1); // capture video from webcam
    Mat frame, prevFrame, frame2;
    
    // Default resolution of the frame is obtained.The default resolution is system dependent.
    int frame_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);

            // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
    VideoWriter video("outcpp.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height));


    while( true )
    {
        // Capture the current frame from the input video stream
        capture >> frame;
		//capture2 >> frame2;
        
        // Downsample the input frame for faster processing
        float downsampleFactor = 0.5;
        resize(frame, frame, Size(), downsampleFactor, downsampleFactor, INTER_NEAREST);
        


        // Apply the classifier to the frame depending on the enabled macros
        if( !frame.empty() )
        {
        	// Write the frame into the file 'outcpp.avi'
        	    video.write(frame);

            if(ENABLE_FACE_DETECTION) detectFace(frame);
            if(ENABLE_EYE_DETECTION) detectEyes(frame);
            if(ENABLE_EAR_DETECTION) detectEars(frame);
            if(ENABLE_MOUTH_DETECTION) detectMouth(frame);
            if(ENABLE_NOSE_DETECTION) detectNose(frame);
            if(ENABLE_SMILE_DETECTION) detectSmile(frame);
            if(ENABLE_LOWERBODY_DETECTION) detectLowerBody(frame);
            if(ENABLE_UPPERBODY_DETECTION) detectUpperBody(frame);
            if(ENABLE_FULLBODY_DETECTION) detectFullBody(frame);
        }
        
        else
        {
            cout << "No captured frame. Stopping!" << endl;
            break;
        }
        
	/*	if( !frame2.empty() )
        {
            if(ENABLE_FACE_DETECTION) detectFace2(frame2);
            
        }
        
        else
        {
            cout << "No captured frame. Stopping!" << endl;
            break;
        }*/
        
        int c = waitKey(10);
        if( (char)c == 27 ) { break; }
    }
    
    capture.release();
    
    return 0;
}

