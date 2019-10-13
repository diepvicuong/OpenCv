//#include <opencv2\opencv.hpp>
//#include <vector>
//#include <sstream>
//#include <string>
//#include <iostream>
//#include <vector>
//#include <math.h>
//#include "LightColor.h"
//using namespace cv;
//using namespace std;
//
////default capture width and height
//const int FRAME_WIDTH = 640;
//const int FRAME_HEIGHT = 360;
////max number of objects to be detected in frame
//const int MAX_OBJECTS = 50;
////minimum and maximum object area
//const int MIN_OBJECT_AREA = 20 * 20;
//const double MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
//
////to draw traffic light.
//#define COLOR_RED Scalar(0,0,255)
//#define COLOR_GREEN Scalar(0,255,0)
//#define COLOR_YELLOW Scalar(60,255,255)
//
////draw traffic light after detection.
//void drawTrafficLights(Mat &targetImg, LightState lightState);
////to call draw location function.
//void draw_locations(Mat & img, const vector< Rect > & locations, Mat HSV);
//
////link video and xml.
//#define VIDEO_FILE_NAME "C:\\Users\\ASUS\\Desktop\\OpenCv_project\\BTL_Nhom_4\\video\\test_light.mp4"
//#define CASCADE_FILE_NAME "C:\\Users\\ASUS\\Desktop\\OpenCv_project\\BTL_Nhom_4\\xml\\myhaar.xml"
//
////main
//int main()
//{
//	VideoCapture cap(VIDEO_FILE_NAME);
//	Mat mFrame, mGray;
//	CascadeClassifier classifier;
//	vector<Rect> detect;
//
//	classifier.load(CASCADE_FILE_NAME);
//	cap.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
//	cap.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
//
//	int count = 1;
//	while (1)
//	{	
//		cap >> mFrame;
//		// repeat video.
//		if (mFrame.empty())
//		{
//			cap.open(VIDEO_FILE_NAME);
//			cap >> mFrame;
//		}
//
//	//	run interleaved.
//		Mat hsv_image;
//		if (count >= 1)
//		{
//			
//			cvtColor(mFrame, hsv_image, COLOR_BGR2HSV);
//	//		 Apply the classifier to the frame
//			cvtColor(mFrame, mGray, COLOR_BGR2GRAY);
//			equalizeHist(mGray, mGray);
//	//		call detection.
//			classifier.detectMultiScale(mGray, detect, 1.5 , 3, 0 ,Size(10,10));
//	//		call draw function.
//			draw_locations(mFrame, detect, hsv_image);		
//			count = 0;
//		}
//
//		imshow("result", mFrame);
//		count++;
//		// Press  ESC on keyboard to exit
//		char c = (char)waitKey(1);
//		if (c == 27)
//			break;
//	}
//	return 0;
//}
//
//void drawTrafficLights(Mat &targetImg, LightState lightState) {
//	switch (lightState) {
//	case GREEN:
//		putText(targetImg, "Green Light", Point(420, 25), FONT_HERSHEY_PLAIN, 2, COLOR_GREEN, 2);
//		circle(targetImg, Point(520, 40), 15, COLOR_GREEN, -1);
//		break;
//	case YELLOW:
//		putText(targetImg, "Yellow Light", Point(420, 25), FONT_HERSHEY_PLAIN, 2, COLOR_YELLOW, 2);
//		circle(targetImg, Point(528, 40), 15, COLOR_YELLOW, -1);
//		break;
//	case RED:
//		putText(targetImg, "Red Light", Point(450, 25), FONT_HERSHEY_PLAIN, 2, COLOR_RED, 2);
//		circle(targetImg, Point(515, 40), 15, COLOR_RED, -1);
//		break;
//	case NON_COLOR:
//		break;
//	}
//}
//
////detect color function.
//vector<LightColor> trackFilteredObject(LightColor theLight) {
//	vector <LightColor> lights;
//
//	Mat temp;
//	theLight.getHueThreshold().copyTo(temp);
////	these two vectors needed for output of findContours
//	vector< vector<Point> > contours;
//	vector<Vec4i> hierarchy;
////	find contours of filtered image using openCV findContours function
//	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
////	use moments method to find our filtered object
//	double refArea = 0;
//	bool objectFound = false;
//	if (hierarchy.size() > 0) {	
//		size_t numObjects = hierarchy.size();
////		if number of objects greater than MAX_OBJECTS we have a noisy filter
//		if (numObjects<MAX_OBJECTS) {
//			for (int index = 0; index >= 0; index = hierarchy[index][0]) {		// lay nhung contour cung 1 lop( ngoai)
//
//				Moments moment = moments((cv::Mat)contours[index]);
//				double area = moment.m00;
//
//	//			if the area is less than 20 px by 20px then it is probably just noise
//	//			if the area is the same as the 2/3 of the image size, probably just a bad filter
//	//			we only want the object with the largest area so we save a reference area each
//	//			iteration and compare it to the area in the next iteration.
//				if (area>MIN_OBJECT_AREA) {
//					LightColor light = theLight;
//
//					light.xPos = moment.m10 / area;
//					light.yPos = moment.m01 / area;
//
//					lights.push_back(light);		// save contours ( light and maybe noises)
//				}
//			}
//			return lights;
//		}
//	}
//}
////check color in detection area.
//bool checkLightPosition(vector< Rect >::const_iterator loc, const vector<LightColor> & lights)
//{
//	vector<LightColor>::const_iterator light = lights.begin();
//	vector<LightColor>::const_iterator light_end = lights.end();
//	
//	for (; light != light_end; ++light)
//	{
//		if (light->xPos > loc->x && light->xPos < loc->x + loc->width
//			&& light->yPos > loc->y && light->yPos < loc->y + loc->height)
//			return true;
//	}
//	return false;
//}
//
////draw detection area after Apply the classifier.
//void draw_locations(Mat & img, const vector< Rect > & locations, Mat HSV)
//{
//	if (!locations.empty())
//	{	
////		create new color.
//		LightColor red(RED, HSV), yellow(YELLOW, HSV), green(GREEN, HSV);
//
////		find color in frame.
//		vector<LightColor> reds = trackFilteredObject(red);
//		vector<LightColor> yellows = trackFilteredObject(yellow);
//		vector<LightColor> greens = trackFilteredObject(green);
//		
////		get detection area
//		vector< Rect >::const_iterator loc = locations.begin();
//		vector< Rect >::const_iterator end = locations.end();
//		for (; loc != end; ++loc)
//		{
////			find the top image.
//			if (loc->y + loc->height <= FRAME_HEIGHT/2)
//			{			
////				check color position to draw traffic light.
//				if (checkLightPosition(loc, reds))
//				{
//					drawTrafficLights(img, RED);
//					rectangle(img, *loc, Scalar(0, 0, 255), 2);
//				}
//				else if (checkLightPosition(loc, yellows))
//				{
//					drawTrafficLights(img, YELLOW);
//					rectangle(img, *loc, Scalar(50,255,255), 2);
//				
//				}
//				else if (checkLightPosition(loc, greens))
//				{
//					drawTrafficLights(img, GREEN);
//					rectangle(img, *loc, Scalar(0,255,0) , 2);
//				}
//			}
//		}
//	}
//}
