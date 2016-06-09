#include <stdio.h>
#include <math.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace cv;
using namespace std;


int main(int argc, char* argv[]){
	CascadeClassifier car_cascade;
	namedWindow("Result");	//To show resulatnt image in this window.
	namedWindow("Crop");	//To show cropped image in this window.

	//	if(!face_cascade.load("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml")){
//	if(!face_cascade.load("/home/rohit/Desktop/NoPlate/BackSubst/result/cascade.xml")){
//      if(!face_cascade.load("/home/rohit/Desktop/NoPlate/result_haar/cascade.xml")){
	if(!car_cascade.load(argv[2])){
		cout<< " Error while loading cascade file for face" << endl;
		return 1;
	}


	VideoCapture capture(argv[1]);
	if (!capture.isOpened()) {
		cout<<"Error while opening camera"<<endl;
		return 1;
	}
	//	capture.set(CV_CAP_PROP_BUFFERSIZE, 500);
	Mat src_img, gray_img, resize_src_img;

	//	capture>>src_img;

	vector<Rect> cars;
	bool count = true;
	Rect crop;	//To create resize the grabbed faces and store the result  in this variable.
	int CarCount = 0;
	char imageToSave[50];	
	string folderName = "Cars_Plates";
	string folderRemoveCommand = "rm -rf" + folderName;
	system(folderRemoveCommand.c_str());	//Remove the folder if already present
	string folderCreateCommand = "mkdir " + folderName;
	system(folderCreateCommand.c_str());	//Create the folder if not present.


	while(capture.isOpened()){
capture.read(src_img);
//src_img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
//{
		//for(;;){
		//              capture.retrieve(src_img);
		//                capture>>src_img;
		//              bool gsuccess = capture.grab();
		//              capture.retrive(src_img);

		//                bool bSuccess = capture.read(src_img); // read a new frame from video
		//                if (!bSuccess) //if not success, break loop
		//                {
		//                        cout << "Cannot read the frame from video file" << endl;
		//                        break;
		//                }

		//              iwaitKey(5);
//		clock_t begin = clock();
#if 1
		//if(count){
		//clock_t begin = clock();
cout<<"width "<< src_img.size().width << endl;
cout<<"height "<< src_img.size().height << endl;
//		if(src_img.size().width/2 > 600 && src_img.size().height/2 > 350)
//		{
//		resize(src_img, resize_src_img, Size(src_img.size().width/1, src_img.size().height/1) );
//		}
//		else
//		{
//		resize(src_img, resize_src_img, Size(src_img.size().width/1, src_img.size().height/1) );
//		}

		cvtColor(src_img,gray_img,CV_BGR2GRAY);
		equalizeHist(gray_img,gray_img);
		//              face_cascade.detectMultiScale(gray_img, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, cvSize(0,0), cvSize(500,500));
		car_cascade.detectMultiScale(gray_img, cars, 1.11, 2, 0 | CASCADE_SCALE_IMAGE, Size(0,0));

		for(int i = 0; i<cars.size(); i++){




//                if((cars[i].width + 95) <= src_img.size().width)
//                        cars[i].width +=95;
//                else if((cars[i].width + 85) <= src_img.size().width)
//                        cars[i].width +=85;
//                else if((cars[i].width + 75) <= src_img.size().width)
//                        cars[i].width +=75;
		if((cars[i].width + 65) <= src_img.size().width- 20)
                	cars[i].width +=65;
		else if((cars[i].width + 55) <= src_img.size().width-20)
			cars[i].width +=55;
                else if((cars[i].width + 45) <= src_img.size().width-20)
                        cars[i].width +=45;
                else if((cars[i].width + 35) <= src_img.size().width-20)
                        cars[i].width +=35;
                else if((cars[i].width + 25) <= src_img.size().width-20)
                        cars[i].width +=25;
                else if((cars[i].width + 15) <= src_img.size().width -20)
                        cars[i].width +=15;


		if((cars[i].height + 20) <= src_img.size().height)
			cars[i].height +=20;
                else if((cars[i].height + 15) <= src_img.size().height)
                        cars[i].height +=15;
                else if((cars[i].height + 10) <= src_img.size().height)
                        cars[i].height +=10;
                else if((cars[i].height + 5) <= src_img.size().height)
                        cars[i].height += 5;


			Point pt1(cars[i].x + cars[i].width, cars[i].y+cars[i].height);
			Point pt2(cars[i].x, cars[i].y);

//			Mat faceROI = gray_img(faces[i]);
//			if(!faces.empty()){
//
//				//To grab faces and store in separate jpg files.
//				if((faces[i].y - 20) >= 0)
//					faces[i].y -= 20;
//
//				faces[i].width +=20;
//				faces[i].height+=20;
//
//				//Grab faces in sepaate matrix
//				Mat crop_img = src_img(cars[i]);
//
//				imshow("Crop", src_img(cars[i]));
//				//Write in jpg file grabbed face

if(cars[i].x <= (src_img.size().width - cars[i].width) && cars[i].y <= (src_img.size().height - cars[i].height))
{
				imshow("Crop", src_img(cars[i]));
				CarCount +=1;
				sprintf(imageToSave,"%s//car_plate_%d.jpg",folderName.c_str(),CarCount);
				imwrite(imageToSave, src_img(cars[i]));
}
//
//
//
				//                if(!eyes.empty())i
				//To show the rectangle on face
				rectangle(src_img, pt1, pt2, Scalar(0,255,0),2, 8, 0);
	//		}
		}
#endif
		if(!src_img.empty())
			imshow("Result", src_img);

		waitKey(1);
		//	int c = waitKey(30);
		//	if((char)c == 37)
		//	break;
	}						

	//destroy GUI windows
	destroyAllWindows();

	//delete capture object
	capture.release();
//                waitKey(0);
	return 0;	
	}
