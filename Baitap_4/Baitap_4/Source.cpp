#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int p1, p2;
Mat dice, canny;

void on_trackbar(int, void*) {
//	Canny(dice, canny, p1, p2);
	threshold(dice, canny, p1, p2, THRESH_BINARY | THRESH_OTSU);
	imshow("canny", canny);
}

int main(int argc, const char** argv)
{
	Mat dice_blur, dice_gray;
	vector<KeyPoint> keypoints, keypoints_1;
	dice = imread("C:/Users/ASUS/Desktop/OpenCv_project/Baitap_4/dice_5.jpg", 0);
	resize(dice, dice, Size(500, 500));
	medianBlur(dice, dice_blur,(3,3));
	threshold(dice_blur, canny, 255, 400, THRESH_BINARY);
	imshow("canny", canny);
	p1 = 100;
	p2 = 200;
	createTrackbar("p1", "canny", &p1, 1000, on_trackbar);
	createTrackbar("p2", "canny", &p2, 1000, on_trackbar);
	waitKey();
	
	//Setting detector parameters
	SimpleBlobDetector::Params params;
	params.filterByCircularity = true;
	params.filterByArea = true;
	params.minArea = 10.0f;
	params.maxArea =1000.0f;

	//Creating a detector object
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	vector<vector<Point> > diceContours;
	vector<Vec4i> diceHierarchy;
	findContours(canny, diceContours, diceHierarchy, CV_RETR_TREE, CHAIN_APPROX_SIMPLE);

	printf("so contours: %d \n", diceContours.size());
	//iterate over dice contours
	for (size_t i = 0; i < diceContours.size(); i++) 
	{
		double diceContourArea = contourArea(diceContours[i]);
		printf("vung contour: %f \n", diceContourArea);

		if (diceContourArea > 1000 && diceContourArea < 4500)
		{
			// Find dices of image with the rectangle shape
			Rect r = boundingRect(diceContours[i]);

			// Find number of dots in a defined dice
			Mat temp = dice_blur(r);
			detector->detect(temp, keypoints);
			int nrOfBlobs = keypoints.size();

			// Draw dots of a dice
			detector->detect(dice_blur, keypoints_1);
			int nrOfBlobs_1 = keypoints_1.size();
			drawKeypoints(dice, keypoints_1, dice, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);	

			//text only appears if at least 1 blob is detected
			if (nrOfBlobs >0) {
				// ouput debug info
				ostringstream diceText;
				diceText << " " << nrOfBlobs;
				// draw value
				putText(dice, diceText.str(), Point(r.x, r.y + r.height + 20), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar::all(255), 1, 8);				
			}
		
			rectangle(dice, r.tl(), r.br(), Scalar(0, 255, 0), 2);			
		}
	}
	imshow("dice", dice);

	waitKey();

	return 0;
}