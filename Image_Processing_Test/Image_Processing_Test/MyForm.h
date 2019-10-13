#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

namespace Image_Processing_Test {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace std;
	using namespace cv;
	IplImage* img = NULL;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(42, 65);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(42, 23);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(398, 261);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		img = cvLoadImage("C:/Users/ASUS/Pictures/baitap3.PNG");
		IplImage* imgGrayScale = cvCreateImage(cvGetSize(img), 8, 1);
		cvCvtColor(img, imgGrayScale, COLOR_BGR2GRAY);	
		cvThreshold(imgGrayScale, imgGrayScale, 127, 255, CV_THRESH_BINARY_INV);
		CvSeq* contours;
		CvSeq* result;
		CvMemStorage* storage = cvCreateMemStorage(0);
		cvFindContours(imgGrayScale, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	//	cvDrawContours(img, contours, Scalar(255,0,0), Scalar(0, 0, 255), 1, 2);
		
		while (contours)
		{
			//obtain a sequence of points of contour, pointed by the variable 'contour'
			result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
				//if there are 3 vertices in the contour(It should be a triangle)
				if (result->total == 3)
				{
					//iterating through each point
					CvPoint *pt[3];
					for (int i = 0;i<3;i++) {
						pt[i] = (CvPoint*)cvGetSeqElem(result, i);
					}
					//drawing lines around the triangle
					//cvPutText(img, "tamgiac", CvPoint(100,100), CV_FONT_HERSHEY_SIMPLEX, CvScalar(0, 0, 255));
					cvLine(img, *pt[0], *pt[1], cvScalar(255, 0, 0), 4);
					cvLine(img, *pt[1], *pt[2], cvScalar(255, 0, 0), 4);
					cvLine(img, *pt[2], *pt[0], cvScalar(255, 0, 0), 4);
					
				}
				//if there are 4 vertices in the contour(It should be a quadrilateral)
				else if (result->total == 4)
			{
				//iterating through each point
				CvPoint *pt[4];
				for (int i = 0;i<4;i++) {
					pt[i] = (CvPoint*)cvGetSeqElem(result, i);
				}
				//drawing lines around the quadrilateral
				cvLine(img, *pt[0], *pt[1], cvScalar(0, 255, 0), 4);
				cvLine(img, *pt[1], *pt[2], cvScalar(0, 255, 0), 4);
				cvLine(img, *pt[2], *pt[3], cvScalar(0, 255, 0), 4);
				cvLine(img, *pt[3], *pt[0], cvScalar(0, 255, 0), 4);
			}
				//if there are 7 vertices in the contour(It should be a heptagon)
				else if (result->total == 7)
			{
				//iterating through each point
				CvPoint *pt[7];
				for (int i = 0;i<7;i++) {
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
			}
				//obtain the next contour
				contours = contours->h_next;
		}
		//show the image in which identified shapes are marked 
		cvPutText(img, "tamgiac", CvPoint(10, 10), CV_FONT_HERSHEY_SIMPLEX, CvScalar(0, 0, 255));
		cvNamedWindow("Tracked");
		cvShowImage("Tracked", img);
		cvWaitKey(0); //wait for a key press
					  //cleaning up
		cvDestroyAllWindows();
		cvReleaseMemStorage(&storage);
		cvReleaseImage(&img);
		cvReleaseImage(&imgGrayScale);
	}
	};
}