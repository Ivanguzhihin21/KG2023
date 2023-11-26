#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Import IMG
Mat img;
Mat imgGray,mask;
int leftx = 0;
int rightx = 0;
int j = 0;
int midx = 80;
int main(){
		VideoCapture cap(2);
	    cap.set(CAP_PROP_FRAME_WIDTH, 160);
        cap.set(CAP_PROP_FRAME_HEIGHT, 120);




char c;
while(c != 27){
	int treshold = 48;
	cap.read(img);
    warpAffine(img, img, getRotationMatrix2D(Point(80,60), 180, 1), Size(160, 120));
	cvtColor(img,imgGray,COLOR_BGR2GRAY);
	bool a = 1;
	
	j = midx;
	while(a){
	
    if(j > 158){

	a = 0;
	}else if(imgGray.at<uchar>(106,j) > treshold){
			leftx = j;
	a = 0;
	j++;
   
}else{
	j++;
		line(imgGray,Point(j,110),Point(j,110), 254,2);
}
}
a = 1;
j = midx;
	while(a){
    if(imgGray.at<uchar>(106,j) > treshold){
	rightx = j;
	a = 0;
	j--;
	}else if(j > 0){
		j--;
		line(imgGray,Point(j,110),Point(j,110), 254,2);
}else{
	a = 0;
	
}
}

a = 1;
cout << leftx << endl;
cout << rightx << endl;
if(40 < (rightx + leftx)/2 < 120){
	
midx = (rightx + leftx)/2;

}else{midx = 80;}
circle(imgGray,Point( midx , 114), 6, 255, -1);

	imshow("Image HSV",imgGray);
	c = waitKey(1);

	
}
return 0;
}
