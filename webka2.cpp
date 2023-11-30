#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


Mat img;
Mat imgHSV,mask,imgB;
Mat imgGray;
int leftx = 0;
int rightx = 0;
int j = 0;
int hmin=83, smin=114, vmin=80;
int hmax=97, smax=255, vmax=254;
string objectType;
int sizeSemafor = 500, contours1 = 6;
int midx = 80;

int getContours(Mat imgDil, Mat img1){
	   
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;


findContours(imgDil, contours, hierarchy,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	

return 0;
}


int main(){
		VideoCapture cap(0);
		 cap.set(CAP_PROP_FRAME_WIDTH, 160);
        cap.set(CAP_PROP_FRAME_HEIGHT, 120);
	cap.read(img);
	
	vector<vector<Point>> contours;
vector<Vec4i> hierarchy;



/*namedWindow("Trackbars", (640,200));
createTrackbar("Hue Min", "Trackbars", &hmin, 360);
createTrackbar("Hue Max", "Trackbars", &hmax, 360);
createTrackbar("Saturation Min", "Trackbars", &smin, 255);
createTrackbar("Saturation", "Trackbars", &smax, 255);
createTrackbar("Value Min", "Trackbars", &vmin, 255);
createTrackbar("Value Max", "Trackbars", &vmax, 255);
createTrackbar("Size Min", "Trackbars", &sizeSemafor, 10000);
createTrackbar("Contours", "Trackbars", &contours1, 50); */
char c;
while(c != 27){
	cap.read(img);
	
cvtColor(img,imgHSV,COLOR_BGR2HSV);
	GaussianBlur(imgHSV, imgB, Size(9,9), 5.0);
Scalar lower(hmin, smin, vmin);
Scalar upper(hmax, smax, vmax);
inRange(imgB,lower,upper,mask);

	findContours(mask, contours, hierarchy,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++)
{
  int area = contourArea(contours[i]);
   
   vector<vector<Point>> conPoly(contours.size());
   vector<Rect> boundRect(contours.size());

   
   if (area > sizeSemafor){
	 float peri = arcLength(contours[i], true);
	 approxPolyDP(contours[i], conPoly[i],0.02*peri, true);
	 
	   drawContours(mask, conPoly, i ,Scalar(255,0,255),2);
	   
	   boundRect[i] = boundingRect(conPoly[i]);
	   int objCor = (int)conPoly[i].size();

	   if (objCor > contours1) {
		   c = 27;
		   }  
	   
	   drawContours(mask,conPoly, i ,Scalar(255,0,255),2);
	   rectangle(mask, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5, FILLED);
	   putText(mask, objectType,{ boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 69, 255), 5);
   }
}


	waitKey(1);
	

}
	

while(1){
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
}else{
        a = 0;

}
}

a = 1;
cout << midx << endl;
if(40 < (rightx + leftx)/2 < 120){

midx = (rightx + leftx)/2;

}else{midx = 80;}
circle(imgGray,Point( midx , 114), 6, 255, -1);


      

}
return 0;
}
