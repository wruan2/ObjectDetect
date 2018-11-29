/*
 * @author William Ruan, Amber Rosevear
 * @description Header file for processVideo
 * @date November 28th, 2018
*/

#ifndef VIDEO_PROCESS_HEAD
#define VIDEO_PROCESS_HEAD

#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

/**
*  @brief Defines the functions to be performed in order to process the provided video file
*  @author William Ruan
*
* The video analysis works by segmenting the video into a foreground and a background. The foreground mask is a map of the moving objects, and in ideal conditions their shadows.
* Since most of the processes are using opencv's functions, this class deals with handling the video before and after processing, rather than  performing the analysis itself.
* it prepares the windows for displaying the results of the procesing, as well as initialising the variables that opencv's functions need.
*  
*/

class processvideo{

	public:

 /**
 *    @param file: The name of the video file.
 *    @brief Creates necessary object and sets global variables for vidFile and pMOG2
 *    
 * Creates a createBackgroundSubtractorMOG2 object, which is one of the more powerful background segmentation algorithms and functions available on opencv. This will be the object on which the processing will be performed.
 * createBackgroundSubtractorMOG2 works by applying masks over and over on the created background, and this new object will contain the background, the foreground, and will eventually show the final image when it's done.
 */
   
		processvideo(char *);
   
 /**
 *    @brief constructor and deconstructor.
 *    Called when initialising or deleting memebers of the class.
 */
   
		~processvideo(); 
   
 /**
 *    @brief Applies the background segmentation algorithm and shows the results.
 *    
 *    Opens the video file, and begins to break it down frame-by-frame. After each frame, the area around the object is added as a mask to the background. When watching in real time, this results i nthe background 
 *    model beginning with a number of shadows, adn the shaodws being removed as the masks cover up more and more of the space the object occupied. The results are displayed on the screen.
 */
   
		void process();
   
	private:
 
  /**
 *    @param keyboard:  The key a user presses. Used for stopping the analysis.
 */
 
		int keyboard;
   
 /**
 *    @param vidFile:  The name of the video file being analysed.
 */
		char * vidFile;
};

#endif

