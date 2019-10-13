#define _CRT_SECURE_NO_WARNINGS
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main() {
	cv::Mat im_with_keypoints; std::vector<cv::KeyPoint> keypoints;
	cv::Mat grayImage, camFrame, kernel;
	int morphBNo2 = 2;
	char str[200];
	//Setting detector parameters
	cv::SimpleBlobDetector::Params params;
	params.filterByInertia = true;
	params.minInertiaRatio = 0.5;
	params.filterByCircularity = true;
	params.filterByArea = true;
	params.minArea = 200.0f;
	//Creating a detector object
	cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
	//video capture settings
	cv::VideoCapture cap(0); // open the default camera
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	//checking video stream
	if (!cap.isOpened()) {  // check if we succeeded
		std::cout << ("Failure to open camera") << "\n";
		std::cin.get();
	}
	cv::Mat backgroundFrame;
	cap >> backgroundFrame;
	cvtColor(backgroundFrame, backgroundFrame, CV_BGR2GRAY);
	Mat unprocessedFrame;

	for (;;) {
		// get a new frame from camera
		cap >> camFrame;

		unprocessedFrame = camFrame.clone();
		//converting video to single channel grayscale
		cvtColor(camFrame, grayImage, CV_BGR2GRAY);
		grayImage.convertTo(grayImage, CV_8U);
		//filter noise
		cv::GaussianBlur(grayImage, grayImage, cvSize(5, 5), 0, 0);
		// remove background
		absdiff(grayImage, backgroundFrame, grayImage);
		//apply automatic threshold
		cv::threshold(grayImage, grayImage, 0.0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
		Canny(grayImage, grayImage, 2, 2 * 2);

		std::vector<std::vector<cv::Point> > diceContours;
		std::vector<cv::Vec4i> diceHierarchy;
		cv::findContours(grayImage.clone(), diceContours, diceHierarchy, CV_RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		for (int i = 0; i < diceContours.size(); i++) {
			// get contour area
			double diceContourArea = cv::contourArea(diceContours[i]);

			// filter contours based on our dice size
			if (diceContourArea > 100 && diceContourArea < 400) {

				// get bounding rect
				cv::Rect diceBoundsRect = cv::boundingRect(cv::Mat(diceContours[i]));
				Mat diceROI = unprocessedFrame(diceBoundsRect);
				//blob detection
				detector->detect(grayImage, keypoints);
				int nrOfBlobs = keypoints.size();
				// draw keypoints
				cv::drawKeypoints(camFrame, keypoints, im_with_keypoints, cv::Scalar(0, 0, 255),
					cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
				//text only appears if at least 1 blob is detected
				if (nrOfBlobs > 0) {
					sprintf(str, "total pips: %d ", nrOfBlobs);
					cv::putText(im_with_keypoints, str, cv::Point2f(10, 25), cv::FONT_HERSHEY_PLAIN,
						2, cv::Scalar(0, 255, 255, 255));
				}
					rectangle(im_with_keypoints, diceBoundsRect.tl(), diceBoundsRect.br(), Scalar(0, 153, 255), 2, 8, 0);

				
				imshow("keypoints", im_with_keypoints);
			}
		}

		//hit esc to quit
		if (cv::waitKey(1) == 27)  break;
	}
}