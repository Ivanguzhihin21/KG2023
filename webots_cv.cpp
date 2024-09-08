//OpenCV 4
//color detect
// https://www.youtube.com/watch?v=2FYm3GOonhk
//компиляция:
// создать файл CMakeLists.txt:
/*
cmake_minimum_required(VERSION 2.8)
project( cvcolordetect )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( cvcolordetect cvcolordetect.cpp )
target_link_libraries( cvcolordetect ${OpenCV_LIBS} )
*/
//выполнить команды:
// cmake .
// make

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
int areaSize = 800;
using namespace cv;
using namespace std;

Mat imgHSV, mask;
VideoCapture cap(0);
char c;


int getContours(Mat imgDil, Mat img){
	
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;

findContours(imgDil, contours, hierarchy,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//drawContours(img,contours,-1,Scalar(255,0,255),2);
	
for (int i = 0; i < contours.size(); i++)
{
  int area = contourArea(contours[i]);
   
   vector<vector<Point>> conPoly(contours.size());
   vector<Rect> boundRect(contours.size());
   string objectType;
   
   if (area > areaSize){
	   float peri = arcLength(contours[i], true);
	 approxPolyDP(contours[i], conPoly[i],0.02*peri, true);
	 
	   drawContours(img,conPoly, i ,Scalar(255,0,255),2);
	  
	   
	   boundRect[i] = boundingRect(conPoly[i]);
	   rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5, FILLED);
	   int objCor = (int)conPoly[i].size();
	   if (objCor < 6) {objectType = "1";}
	   else {objectType = "0";}
	   cout << objectType << endl;
}
}
}


int main(){

    Mat img;
    while(c != 27){
	
    cap.read(img);
    
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

cvtColor(img,imgGray,COLOR_BGR2GRAY);
GaussianBlur(imgGray, imgBlur, Size(7,7), 5, 0);
Canny (imgBlur, imgCanny, 5, 35);

Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5));
dilate(imgCanny,imgDil, kernel);


	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	
		Scalar lower(176,150,150);
		Scalar upper(179,255,255);
		
		inRange(imgHSV,lower,upper,mask);
		
		imshow("Image",img);
		imshow("Image HSV",imgHSV);
		imshow("Image Mask",mask);
		getContours(mask, img);

		c = waitKey(1);
	}
    return 0;
}
