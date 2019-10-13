#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include "stdint.h"
#include <vector>
#include "math.h"

using namespace std;
using namespace cv;
int main()
{
	Mat img3 = imread("C:/Users/ASUS/Pictures/anhden.PNG");
	IplImage* abc= cvLoadImage("C:/Users/ASUS/Pictures/anhden.PNG");
	//Draw elipse
	ellipse(img3, RotatedRect(Point(800,250),Size(100,160),45),Scalar(255,255,255), -1);
	ellipse(img3, RotatedRect(Point(800, 400), Size(80, 100), -45), Scalar(255, 255, 255), -1);
	//Draw circle
	circle(img3, CvPoint(800, 80), 70, Scalar(255, 255, 255),-1);
	circle(img3, CvPoint(400, 400), 70, Scalar(255, 255, 255), -1);
	//Draw rectangle and squares
	rectangle(img3, CvPoint(10, 10), CvPoint(100, 100), Scalar(255, 255, 255), -1);
	rectangle(img3, CvPoint(230, 10), CvPoint(430, 100), Scalar(255, 255, 255), -1);
	//Draw triangle
	Point Triangle_points[1][3];
	Triangle_points[1][0] = Point(10, 150);
	Triangle_points[1][1] = Point(10, 250);
	Triangle_points[1][2] = Point(200, 250);
	const Point* ppt3[] = { Triangle_points[1] };
	int npt3[] = { 3 };
	fillPoly(img3, ppt3, npt3,1, Scalar(255, 255, 255), 8);
	//Draw quadrilateral
	Point quadrilateral_points[1][4];
	quadrilateral_points[0][0] = Point(570, 10);
	quadrilateral_points[0][1] = Point(600, 40);
	quadrilateral_points[0][2] = Point(700, 70);
	quadrilateral_points[0][3] = Point(550, 100);
	const Point* ppt4[] = { quadrilateral_points[0] };
	int npt4[] = { 4 };
	fillPoly(img3, ppt4, npt4, 1, Scalar(255, 255, 255), 8);
	//Draw Pentagon
	Point Pentagon_points[1][5];
	Pentagon_points[0][0] = Point(250, 150);
	Pentagon_points[0][1] = Point(350, 150);
	Pentagon_points[0][2] = Point(400, 250);
	Pentagon_points[0][3] = Point(320, 350);
	Pentagon_points[0][4] = Point(250, 350);
	const Point* ppt5[] = { Pentagon_points[0] };
	int npt5[] = { 5 };
	fillPoly(img3, ppt5, npt5, 1, Scalar(255, 255, 255), 8);
	//Draw Hexagon
	Point Hexagon_points[1][6];
	Hexagon_points[0][0] = Point(450, 150);
	Hexagon_points[0][1] = Point(550, 150);
	Hexagon_points[0][2] = Point(600, 250);
	Hexagon_points[0][3] = Point(650, 280);
	Hexagon_points[0][4] = Point(530, 350);
	Hexagon_points[0][5] = Point(470, 350);
	const Point* ppt6[1] = { Hexagon_points[0] };
	int npt6[] = { 6 };
	fillPoly(img3, ppt6, npt6, 1, Scalar(255, 255, 255), 8);
	imshow("Raw", img3); //show the original image

	IplImage* img = cvCloneImage(&(IplImage)img3);
	///converting the original image into grayscale
	IplImage* imgGrayScale = cvCreateImage(cvGetSize(img), 8, 1);//depth = uint8, 1 channel
	cvCvtColor(img, imgGrayScale, CV_BGR2GRAY);
	//thresholding the grayscale image to get better results 
	cvThreshold(imgGrayScale, imgGrayScale, 128, 255, CV_THRESH_BINARY);

	//detec circle
	//vector<Vec3f> circles;
	//Mat imgGrayScale_temp = cvarrToMat(imgGrayScale);
	//HoughCircles(imgGrayScale_temp, circles, CV_HOUGH_GRADIENT, 1, imgGrayScale_temp.rows / 8, 100, 20, 0, 0);
	//// Loop over all detected circles and outline them on the original image
	//if (circles.size() == 0) std::exit(-1);
	//for (size_t current_circle = 0; current_circle < circles.size(); ++current_circle)
	//{
	//	Point center(std::round(circles[current_circle][0]), std::round(circles[current_circle][1]));
	//	int radius = std::round(circles[current_circle][2]);
	//	cvCircle(img, center, radius, cv::Scalar(0, 0, 255), 3);
	//	Mat img5 = cvarrToMat(img);
	//	putText(img5, "Circle", center, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 0), 2);
	//}

	//Preparing detecpolygon
	CvSeq* contours;  //hold the pointer to a contour in the memory block 
	CvSeq* result;   //hold sequence of points of a contour
	CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours
												   //finding all contours in the image 
	cvFindContours(imgGrayScale, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	//iterating through each contour

	while (contours)
	{
		
		//obtain a sequence of points of contour, pointed by the variable 'contour'
		result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
		//if there are 3  vertices  in the contour(It should be a triangle) 
		if (result->total == 3)
		{
			//iterating through each point
			CvPoint *pt[3];
			for (int i = 0; i<3; i++)
			{
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}
			//drawing lines around the triangle
			cvLine(img, *pt[0], *pt[1], cvScalar(255, 0, 0), 4);
			cvLine(img, *pt[1], *pt[2], cvScalar(255, 0, 0), 4);
			cvLine(img, *pt[2], *pt[0], cvScalar(255, 0, 0), 4);
			//Add text
			Mat img2 = cvarrToMat(img);
			putText(img2, "Triangle", *pt[0], FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 0));
		}

		//if there are 4 vertices in the contour(It should be a quadrilateral) 
		else if (result->total == 4)
		{
			//iterating through each point 
			CvPoint *pt[4];
			for (int i = 0; i<4; i++)
			{
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}
			//drawing lines around the quadrilateral 
			cvLine(img, *pt[0], *pt[1], cvScalar(0, 255, 0), 4);
			cvLine(img, *pt[1], *pt[2], cvScalar(0, 255, 0), 4);
			cvLine(img, *pt[2], *pt[3], cvScalar(0, 255, 0), 4);
			cvLine(img, *pt[3], *pt[0], cvScalar(0, 255, 0), 4);
			double dx1 = pt[1]->x - pt[0]->x;//vector0->x
			double dy1 = pt[1]->y - pt[0]->y;//vector0->y
			double dx2 = pt[2]->x - pt[1]->x;//vector1->x
			double dy2 = pt[2]->y - pt[1]->y;//vector1->y
			double a = sqrt(dx1*dx1 + dy1*dy1);
			double b = sqrt(dx2*dx2 + dy2*dy2);
			double tichvohuong = dx1*dy1 + dx2*dy2;
			if (tichvohuong == 0)
			{
				if (a == b)
				{
					Mat img2 = cvarrToMat(img);
					putText(img2, "square", *pt[2], FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0));
				}
				else
				{
					Mat img2 = cvarrToMat(img);
					putText(img2, "rectangle", *pt[2], FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0));
				}
			}
			else
			{
				Mat img2 = cvarrToMat(img);
				putText(img2, "quadrilateral", *pt[2], FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0));
			}
		}

		//if there are 5 vertices in the contour
		else if (result->total == 5)
		{
			//iterating through each point 
			CvPoint *pt[5];
			for (int i = 0; i<5; i++)
			{
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}
			//drawing lines around the quadrilateral 
			cvLine(img, *pt[0], *pt[1], cvScalar(39, 127, 255), 4);
			cvLine(img, *pt[1], *pt[2], cvScalar(39, 127, 255), 4);
			cvLine(img, *pt[2], *pt[3], cvScalar(39, 127, 255), 4);
			cvLine(img, *pt[3], *pt[4], cvScalar(39, 127, 255), 4);
			cvLine(img, *pt[4], *pt[0], cvScalar(39, 127, 255), 4);

			Mat img2 = cvarrToMat(img);
			putText(img2, "Pentagon", *pt[4], FONT_HERSHEY_PLAIN, 1, Scalar(39, 127, 255));
		}

		//if there are 6 vertices in the contour
		else if (result->total == 6)
		{
			//iterating through each point 
			CvPoint *pt[6];
			for (int i = 0; i<6; i++)
			{
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}
			//drawing lines around the quadrilateral 
			cvLine(img, *pt[0], *pt[1], cvScalar(234, 217, 153), 4);
			cvLine(img, *pt[1], *pt[2], cvScalar(234, 217, 153), 4);
			cvLine(img, *pt[2], *pt[3], cvScalar(234, 217, 153), 4);
			cvLine(img, *pt[3], *pt[4], cvScalar(234, 217, 153), 4);
			cvLine(img, *pt[4], *pt[5], cvScalar(234, 217, 153), 4);
			cvLine(img, *pt[5], *pt[0], cvScalar(234, 217, 153), 4);

			Mat img2 = cvarrToMat(img);
			putText(img2, "Hexagon", *pt[5], FONT_HERSHEY_PLAIN, 1, Scalar(234, 217, 153));
		}

		//if there are 7  vertices  in the contour(It should be a heptagon) 
		else if (result->total == 7)
		{
			//iterating through each point 
			CvPoint *pt[7];
			for (int i = 0; i<7; i++) {
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}
			//drawing lines around the heptagon 
			cvLine(img, *pt[0], *pt[1], cvScalar(0, 0, 255), 4);
			cvLine(img, *pt[1], *pt[2], cvScalar(0, 0, 255), 4);
			cvLine(img, *pt[2], *pt[3], cvScalar(0, 0, 255), 4);
			cvLine(img, *pt[3], *pt[4], cvScalar(0, 0, 255), 4);
			cvLine(img, *pt[4], *pt[5], cvScalar(0, 0, 255), 4);
			cvLine(img, *pt[5], *pt[6], cvScalar(0, 0, 255), 4);
			cvLine(img, *pt[6], *pt[0], cvScalar(0, 0, 255), 4);

			Mat img2 = cvarrToMat(img);
			putText(img2, "heptagon", *pt[6], FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
		}
		else if(result->total>7)
		{
			RotatedRect box = cvFitEllipse2(result);
			if (box.size.height != box.size.width)
			{
				cvEllipse(img, box.center, box.size*0.5f, box.angle, 0, 360, Scalar(0, 255, 0), 4);
				Mat img2 = cvarrToMat(img);
				putText(img2, "Ellipse", box.center, FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
			}
			else
			{
				cvCircle(img, box.center, box.size.width*0.5f, Scalar(255, 0, 0), 4);
				Mat img2 = cvarrToMat(img);
				putText(img2, "Circle", box.center, FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
			}
		}
		//obtain the next contour
		contours = contours->h_next;
	}
	//show the image in which identified shapes are marked 
	cvNamedWindow("Tracked");
	cvShowImage("Tracked", img);
	cvWaitKey(0); //wait for a key press
				  //cleaning up 
	cvDestroyAllWindows();
	cvReleaseMemStorage(&storage);
	cvReleaseImage(&img);
	cvReleaseImage(&imgGrayScale);
	return 0;
}






