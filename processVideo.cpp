/*
 * @author William Ruan
 * @description Implements processVideo class
 * @date November 28th, 2018
*/

#include "processvideo.h"
using namespace std;
using namespace cv;

// Variables
Mat frame;
Mat fgMaskMOG2;
Mat background;
Ptr<BackgroundSubtractor> pMOG2; 

/*
 * Constructor for processVideo object
 * name: William Ruan
 * 
 */	
processvideo::processvideo(char * file){
	pMOG2 = createBackgroundSubtractorMOG2(); 
	vidFile = file;
}

/*
 * Destructor for processVideo object
 * name: William Ruan
 * 
 */	
processvideo:: ~processvideo(){
}

/*
 * Seperates and removes moving object from video file
 * name: William Ruan
 * 
 */	
void processvideo::process(){
	// Creates seperate windows
	namedWindow("Original File");
    namedWindow("Moving Object");
    namedWindow("Background");
    VideoCapture capture;
    std::string file(vidFile);
    // Loads video or camera
    if (file == "capture"){
		VideoCapture capture(0);
		if(!capture.isOpened()){
			cerr << "Cannot access camera" << endl;
			exit(EXIT_FAILURE);
		}
		// Goes through camera unless user quits
		while ((char) keyboard != 27){
			if(!capture.read(frame)) {
				break;
			}
			// Extracts moving image and background
			pMOG2->apply(frame, fgMaskMOG2);
			pMOG2->getBackgroundImage(background);
			// Displays original file, moving object, and background
			imshow("Camera", frame);
			imshow("Moving Object", fgMaskMOG2);
			imshow("Background", background);
			keyboard = waitKey(1);
		}
	}
	else{
		VideoCapture capture(vidFile);
		if(!capture.isOpened()){
			cerr << "Cannot open file: " << vidFile << endl;
			exit(EXIT_FAILURE);
		}
		// Continues parsing through video unless user quits
		while ((char) keyboard != 27){
			if(!capture.read(frame)) {
				break;
			}
			// Extracts moving image and background
			pMOG2->apply(frame, fgMaskMOG2);
			pMOG2->getBackgroundImage(background);
			// Displays original file, moving object./O, and background
			imshow("Original File", frame);
			imshow("Moving Object", fgMaskMOG2);
			imshow("Background", background);
			keyboard = waitKey(1);
		}
	}
	// Releases video from memory and closes windows
	cout << "Video has finished playing." << endl;
	capture.release();
	destroyAllWindows();
}
