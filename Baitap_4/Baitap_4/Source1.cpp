// std lib
#include <iostream>
#include <sstream>

// OpenCV
#include <opencv2/core.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

int countPips(cv::Mat dice) {

	// resize
	cv::resize(dice, dice, cv::Size(150, 150));

	// convert to grayscale
	cvtColor(dice, dice, CV_BGR2GRAY);

	// threshold
	cv::threshold(dice, dice, 150, 255, cv::THRESH_BINARY | CV_THRESH_OTSU);

	// show
	cv::namedWindow("processed", true);
	cv::imshow("processed", dice);


	// floodfill
	cv::floodFill(dice, cv::Point(0, 0), cv::Scalar(255));
	cv::floodFill(dice, cv::Point(0, 149), cv::Scalar(255));
	cv::floodFill(dice, cv::Point(149, 0), cv::Scalar(255));
	cv::floodFill(dice, cv::Point(149, 149), cv::Scalar(255));

	// search for blobs
	cv::SimpleBlobDetector::Params params;

	// filter by interia defines how elongated a shape is.
	params.filterByInertia = true;
	params.minInertiaRatio = 0.5;

	// will hold our keyponts
	std::vector<cv::KeyPoint> keypoints;

	// create new blob detector with our parameters
	cv::Ptr<cv::SimpleBlobDetector> blobDetector = cv::SimpleBlobDetector::create(params);

	// detect blobs
	blobDetector->detect(dice, keypoints);


	// return number of pips
	return keypoints.size();
}

int main(int argc, char** argv)
{
	// open window frame
	cv::namedWindow("frame", true);

	// open the default camera
	cv::VideoCapture cap(0);

	// check if we succesfully opened the camera stream
	if (!cap.isOpened()) {
		return -1;
	}

	//// set camera properties
	//cap.set(CV_CAP_PROP_FRAME_WIDTH, 1024);
	//cap.set(CV_CAP_PROP_FRAME_HEIGHT, 768);

	////  take single frame (without dices) and convert it to grayscale
	////  to use when removing the background
	//cv::Mat backgroundFrame;
	//cap >> backgroundFrame;
	//cvtColor(backgroundFrame, backgroundFrame, CV_BGR2GRAY);

	//// will hold our frame
	//cv::Mat frame;
	//cv::Mat unprocessFrame;


	//std::cout << "Took Frame, Press Any Key To Continue";
	//if (cv::waitKey(30) >= 0) {
	//	std::cout << "Continuing";
	//}

	//for (;;)
	//{
	//	// retrieve frame from camera
	//	cap >> frame;

	//	// hold unprocessed framed
	//	unprocessFrame = frame.clone();

	//	// convert to grayscale
	//	cvtColor(frame, frame, CV_BGR2GRAY);

	//	// remove background
	//	cv::absdiff(frame, backgroundFrame, frame);

	//	// threshold
	//	cv::threshold(frame, frame, 150, 255, cv::THRESH_BINARY | CV_THRESH_OTSU);

	//	// applying canny edge filter
	//	cv::Canny(frame, frame, 2, 2 * 2, 3, false);

	//	// detect dice shapes
	//	std::vector<std::vector<cv::Point> > diceContours;
	//	std::vector<cv::Vec4i> diceHierarchy;
	//	cv::findContours(frame.clone(), diceContours, diceHierarchy, CV_RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	//	// iterate over dice contours
	//	for (int i = 0; i < diceContours.size(); i++) {

	//		// get contour area
	//		double diceContourArea = cv::contourArea(diceContours[i]);

	//		// filter contours based on our dice size
	//		if (diceContourArea > 2000 && diceContourArea < 3500) {

	//			// get bounding rect
	//			cv::Rect diceBoundsRect = cv::boundingRect(cv::Mat(diceContours[i]));

	//			// set dice roi
	//			cv::Mat diceROI = unprocessFrame(diceBoundsRect);

	//			// count number of pips
	//			int numberOfPips = countPips(diceROI);

	//			if (numberOfPips > 0) {
	//				std::cout << "Pips Exist";
	//				std::cout << numberOfPips;
	//				// ouput debug info
	//				std::ostringstream diceText;
	//				diceText << "val: " << numberOfPips;

	//				// draw value
	//				cv::putText(unprocessFrame, diceText.str(),
	//					cv::Point(diceBoundsRect.x, diceBoundsRect.y + diceBoundsRect.height + 20),
	//					cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar::all(255), 1, 8
	//					);

	//				// draw bounding rect
	//				cv::Scalar color = cv::Scalar(0, 153, 255);
	//				cv::rectangle(unprocessFrame, diceBoundsRect.tl(), diceBoundsRect.br(), color, 2, 8, 0);

	//				// show
	//				cv::imshow("frame", unprocessFrame);
	//			}

	//		}

	//	}
	//	// on key press exit
	//	if (cv::waitKey(30) >= 0) break;
	//}
}