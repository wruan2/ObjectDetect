To compile:

OpenCV 3.4.3 is required [compiler] sudo apt-get install build-essential [required] sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev Go to https://opencv.org/releases.html for download unzip the downloaded folder in the Downloads directory create a build folder in your workplace directory in the terminal: cd to the folder cmake /home/pi/Downloads/opencv-3.4.3 make sudo make install

Put all the files into a folder In the terminal: cd to folder cmake . make

TESTS WITH MEDIA PROVIDED:

./ObjectDetection swing1.jpg swing2.jpg swing3.jpg swing4.jpg swing5.jpg

./ObjectDetection bike1.jpg bike2.jpg bike3.jpg bike4.jpg bike5.jpg bike6.jpg bike7.jpg

./ObjectDetection campus.AVI

./ObjectDetection highway.AVI

./ObjectDetection intelligentroom.AVI

NOTES:

Two or more images must be provided when comparing images. Otherwise the program will fail.
