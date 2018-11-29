/**
*  @file processImages.cpp
 * @author William Ruan, Jinhwi Kim, Amber Rosevear, Hamza Bana, Nathan Dinatale 
 * 
 * Functions for processing the provided images.
 * @date November 28th, 2018
*/

#include "processImages.h"

/**
  * @param imageSeq: An array of Mat objects. Contains the images passed to the program by the user.
*/

Mat *imageSeq;

/**
  * @param  numOfImages: The number of images the user provided to the program.
*/
int numOfImages;

 /*
 *    Takes every image, in the order provides, and inserts it into a Mat array. Each image can then be accessed by its index.
 */

processImages::processImages(char** files, int numOfFiles){

	numOfImages = numOfFiles; // Set the global variable to be the correct value.
	imageSeq = new Mat[numOfFiles-1]; // Initialise the array that will hold the images.

	//Accept series of images from argument
	for(int i = 1; i < numOfImages; i++){
		char* imageName = files[i]; // Name the images after their file names
 		imageSeq[i-1] = imread( imageName, IMREAD_COLOR );
		if(!imageSeq[i-1].data ){
   			cout << "No image data \n " << endl;
 		}
		//Display the image
		namedWindow( imageName, WINDOW_AUTOSIZE );
		imshow( imageName, imageSeq[i-1] );
	} // End for loop
} // End function processImages

processImages::~processImages(){
}

 /*
 * First locates each pixel that changes value between the provided images. If a pixel changes value, that means * it moved. The value of those same pixels is found, and are used to replace the object. 
 * Uses both the private functions to work. 
 */

void processImages::process(){

	vector< vector<int> > changedPixel; // Will contain the vectors that change between images.
	
	for(int i = 0; i < numOfImages-2; i++){
		SearchForChange(imageSeq[i],imageSeq[i+1],&changedPixel);
	}	// End for loop for checking for changed vectors.

	Vec3b pixelValue;

  /* 
  * Loop through and replace every single pixel that changes with the most accurate representation of its         * background.
  */

	for(int i = 0; i < changedPixel.size(); i++){
		imageSeq[0].at<Vec3b>(changedPixel[i][0],changedPixel[i][1]) = FindBackgroundPixel(changedPixel[i],imageSeq,numOfImages);
	} // End for loop for checking image

	namedWindow( "final", WINDOW_AUTOSIZE ); // Display the final background constructed
	imshow( "final", imageSeq[0] );

	waitKey(0); // Wait for user input
} // End function process

  /*
 *    
 *    Compares the current vector with the following image's vector i nthe same location for differences.
 */

int processImages::SearchForChange(Mat& I1, Mat& I2, vector< vector<int> > *cp){

	vector<int> pixel; // Will contain the current pixel
	
	for(int i=0; i<I1.rows; i++){ // Check each row
 
		for(int j=0; j<I1.cols; j++){ // Check each column within the current row
   
			if(abs(I2.at<Vec3b>(i,j)[0]-I1.at<Vec3b>(i,j)[0])>TOLERATION_VAL_S){ // Difference is less than tolerance value
				pixel.push_back(i); // Add the value at i to pixel
				pixel.push_back(j); // Add value at j to pixel
				cp->push_back(pixel); // Put the pixel into cp
				pixel.clear(); // Clear pixel for the next loop
			}
			else if(abs(I2.at<Vec3b>(i,j)[1]-I1.at<Vec3b>(i,j)[1])>TOLERATION_VAL_S){
				pixel.push_back(i);
				pixel.push_back(j);
				cp->push_back(pixel);
				pixel.clear();
			}
			else if(abs(I2.at<Vec3b>(i,j)[2]-I1.at<Vec3b>(i,j)[2])>TOLERATION_VAL_S){
				pixel.push_back(i);
				pixel.push_back(j);
				cp->push_back(pixel);
				pixel.clear();
			}
      
		} // End for loop for going through each column
   
	} // End for loop for going through each row

	return 0;
} // End function SearchForChange

  /*  
 *    Takes the vector identified as containing the moving object. Iterates through each of the passed images and checks their contents at that vector. Uses whichever value is common across the most images. 
 */

Vec3b processImages::FindBackgroundPixel(vector<int> p, Mat* images, int numOfImages){

	Vec3b option1; // Possible return 1
	Vec3b option2; // Possible return 2
	Vec3b current; // Being compared

	int counter1 = 0; // How many times the difference is less than the threshold
	int counter2 = 0;
	
	option1 = images[0].at<Vec3b>(p[0],p[1]); // The original value

	bool opt2 = false;
	
	for(int i = 1; i < numOfImages-1; i++){
		current = images[i].at<Vec3b>(p[0],p[1]);

		if(abs(option1[0]-current[0])<TOLERATION_VAL_F && abs(option1[1]-current[1])<TOLERATION_VAL_F && abs(option1[2]-current[2])<TOLERATION_VAL_F){ //Comparing the pixel values against the threshold
			counter1 ++;
		}
		else if(opt2 && abs(option2[0]-current[0])<TOLERATION_VAL_F && abs(option2[1]-current[1])<TOLERATION_VAL_F && abs(option2[2]-current[2])<TOLERATION_VAL_F){
			counter2 ++;
		}	
		else{
			option2 = current; // There was no differences
			opt2 = true;
		}	
	} // End for loop for background comparison checks

	if(counter1 >= counter2){ // Return the option with the highest counter
		return option1;
	}
	else{
		return option2;
	}
} // End function FindBackgroundPixel
