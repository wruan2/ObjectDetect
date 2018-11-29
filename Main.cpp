/*
 * @author William Ruan, Jinhwi Kim, Amber Rosevear, Hamza Bana, Nathan Dinatale
 * @description Main class for ObjectDetection
 * @date November 28th, 2018
*/

#include "processVideo.h"
#include "processImages.h"

using namespace std;

/*
*  Main function takes in arguments passed when the program is initialised. 
*  When there are more than 2 arguments, then applies image processing.
*  When there is only two, applies video analysis. 
*  Otherwise, throw an error.
*
*/

int main(int argc, char* argv[])
{
	// For video files
	if(argc == 2){
		processvideo video(argv[1]);
    	video.process();
	}
	
	// For image files
	else if(argc > 2){
		processImages images(argv, argc);
		images.process();
	}
	
	// Invalid input
	else{
		cerr <<"Incorrect Input." << endl;
        cerr <<"Please try again." <<endl;
        return EXIT_FAILURE;
	}
} // End function main

