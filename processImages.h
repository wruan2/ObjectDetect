/**
*  @file processImages.h
 * @author William Ruan, Jinhwi Kim, Amber Rosevear, Hamza Bana, Nathan Dinatale
 * @date November 28th, 2018
 *
*/

#ifndef IMAGE_PROCESS_HEAD
#define IMAGE_PROCESS_HEAD

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/**
 * @param  TOLERATION_VAL_S: The largest acceptable difference between two pixels when searching for changes.
*/

const int TOLERATION_VAL_S = 5;

/**
 * @param  TOLERATION_VAL_F: The largest acceptable difference between tweo background pixels when comparing for
*/
const int TOLERATION_VAL_F = 15;

/**
*  @brief Defines the functions to be performed in order to find the moving object from a series of images.
*  @author Jinhwi Kim 
*
*  Each images is seen by the program as an array of pixels. The pulic functions are for intializing the process, placing all the images into the containment array for further processing. From that array, each image is considered to be an array of pixels. The searching functions compare very pixel against the pixel value in the same position in the previous images. 
*   Essentially, the functionality is going through the entire image and finding when pixel calues changes (and object moved), and when they don't (background).
*  
*/

class processImages{

	public:
 
 /**
 *    @param char**: The name of the file
 *    @param int: The number of files provided
 *    @brief Puts the provided images into an array.
 *    
 *    Takes every image, in the order provides, and inserts it into a Mat array. Each image can then be accessed by its index.
 */
		processImages(char**, int);
		~processImages();
  
 /**
 *    @brief Finds the pixels representing the moving object, and then what they contain when they show the background.
 *    
 * First locates each pixel that changes value between the provided images. If a pixel changes value, that means it moved. The value of those same pixels is found, and are used to replace the object. 
 * Uses both the private functions to work. 
 */
		void process();
	private:
 
  /**
 *    @param Mat&: The image currently being examined
 *    @param Mat&: The image next in the sequence.
 *    @param vector< vector<int>: The pixel to be changed.
 *    @brief Checks every pixel to see if it changed between the current and the following.
 *    @returns 0 when sucessful. 
 *    
 *    Iterates through each row and column of the image, and checks if the difference between the current image's and the following image's value are below the tolerance threshold. If they are, change the pixel. If not, leave it alone.
 */
		int SearchForChange(Mat&, Mat&, vector< vector<int> >*);
   
  /**
 *    @param vector<int>: The vector containing pixel values
 *    @param Mat*: A pointer to the array containing all the input
 *    @param int: The number of provided images.
 *    @brief Finds the value of a pixel contained at the vector, and returns it.
 *    @returns The discovered vector.
 *    
 *    Takes the vector identified as containing the moving object. Iterates through each of the passed images and checks their contents at that vector. Uses whichever value is common across the most images. 
 *    Has two options for returning the value, depending on how accurate the results are. The one with a higher count is used. 
 */
		Vec3b FindBackgroundPixel(vector<int>, Mat* , int); 
};

#endif
