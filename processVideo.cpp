/**
*  @file processVideo.cpp
 * @author William Ruan, Amber Rosevear
 * @date November 28th, 2018
*/

#include "processVideo.h"

/**
  * @param frame: Holds the current frame of the video being examined.
*/
Mat frame;
/**
  * @param fgMaskMOG2: The mask for the current frame without the moving object being added to the background model
*/
Mat fgMaskMOG2;
/**
  * @param background: The current model of what the background looks like without the objects in it.
*/
Mat background;
/**
  * @param pMOG2: The object for the background subtraction algorithm to use
*/
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
 * Author: William Ruan
 */	
processvideo:: ~processvideo(){
}

/*
 * Seperates and removes moving object from video file
 * Author: William Ruan
 * 
 */	
 
void processvideo::process(){

	// Creates seperate windows
	namedWindow("Original File"); 
  namedWindow("Moving Object");
  namedWindow("Background");
  
    // Loads video
	VideoCapture capture(vidFile);
 
	if(!capture.isOpened()){
        cerr << "Cannot open file: " << vidFile << endl;
        exit(EXIT_FAILURE);
   } // End uf statement for error in video file name.
    
    // Continues parsing through video unless user quits
    while ( (char) keyboard != 27 ){
    
		if(!capture.read(frame)) {
   
			break;
        }
        // Extracts moving image and background
        pMOG2->apply(frame, fgMaskMOG2);
        pMOG2->getBackgroundImage(background);
        // Displays original file, moving object, and background
        imshow("Original File", frame);
        imshow("Moving Object", fgMaskMOG2);
        imshow("Background", background);
        keyboard = waitKey(1);
	}
 
	// Releases video from memory and closes windows
 
   cout << "Video has finished playing. \n Press enter to quit." << endl;
 
   capture.release();
 
   while (cin.get() != '\n');

   
  destroyAllWindows();
   

} // End function process

