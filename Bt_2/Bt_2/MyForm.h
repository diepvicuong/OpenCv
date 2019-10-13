#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Bt_2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace std;
	using namespace cv;
	Mat src; Mat dst; Mat hsv_image; Mat mask; Mat fin_img;
	IplImage* img = NULL;
//	IplImage* dst;
	IplImage* dst_1; IplImage* dst_2;
	
	
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

	private: System::Windows::Forms::PictureBox^  ptbSource;
	private: System::Windows::Forms::Button^  Find_image;
	private: System::Windows::Forms::PictureBox^  ptbFilter;
	private: System::Windows::Forms::PictureBox^  ptbDetect;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;

	protected:

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
			this->ptbSource = (gcnew System::Windows::Forms::PictureBox());
			this->Find_image = (gcnew System::Windows::Forms::Button());
			this->ptbFilter = (gcnew System::Windows::Forms::PictureBox());
			this->ptbDetect = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbSource))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbFilter))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbDetect))->BeginInit();
			this->SuspendLayout();
			// 
			// ptbSource
			// 
			this->ptbSource->Location = System::Drawing::Point(12, 65);
			this->ptbSource->Name = L"ptbSource";
			this->ptbSource->Size = System::Drawing::Size(312, 286);
			this->ptbSource->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->ptbSource->TabIndex = 1;
			this->ptbSource->TabStop = false;
			// 
			// Find_image
			// 
			this->Find_image->Location = System::Drawing::Point(12, 12);
			this->Find_image->Name = L"Find_image";
			this->Find_image->Size = System::Drawing::Size(69, 34);
			this->Find_image->TabIndex = 0;
			this->Find_image->Text = L"Browser";
			this->Find_image->UseVisualStyleBackColor = true;
			this->Find_image->Click += gcnew System::EventHandler(this, &MyForm::Find_image_Click);
			// 
			// ptbFilter
			// 
			this->ptbFilter->Location = System::Drawing::Point(344, 65);
			this->ptbFilter->Name = L"ptbFilter";
			this->ptbFilter->Size = System::Drawing::Size(321, 286);
			this->ptbFilter->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->ptbFilter->TabIndex = 1;
			this->ptbFilter->TabStop = false;
			// 
			// ptbDetect
			// 
			this->ptbDetect->Location = System::Drawing::Point(691, 65);
			this->ptbDetect->Name = L"ptbDetect";
			this->ptbDetect->Size = System::Drawing::Size(320, 286);
			this->ptbDetect->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->ptbDetect->TabIndex = 1;
			this->ptbDetect->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(472, 367);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(67, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Median Filter";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(124, 367);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(73, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Source Image";
//			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(834, 367);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(80, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Color Detection";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1023, 407);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ptbDetect);
			this->Controls->Add(this->ptbFilter);
			this->Controls->Add(this->ptbSource);
			this->Controls->Add(this->Find_image);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbSource))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbFilter))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbDetect))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: char* ConverString2Char(System::String^ str) {
		char* str2 = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
		return str2;
	}
	private: System::Void Find_image_Click(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ dgOpen = gcnew OpenFileDialog();
		dgOpen->Filter = "Image (*.bmp;*.jpg|*.bmp;*.jpg|All Files (*.* | *.* || ))";
		if (dgOpen->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}
		Bitmap^ bmpSrc = gcnew Bitmap(dgOpen->FileName);
		ptbSource->Image = bmpSrc;
		ptbSource->Refresh();
		src = imread(ConverString2Char(dgOpen->FileName));

		// Remove noise
		medianBlur(src, dst, 9);
		dst_1 = cvCloneImage(&(IplImage)dst);
		// Resize image;
		dst_2 = cvCreateImage(cvSize((int)(dst_1->width*0.5), (int)(dst_1->height*0.5)), dst_1->depth, dst_1->nChannels);
		cvResize(dst_1, dst_2);
		ptbFilter->Image = gcnew System::Drawing::Bitmap(dst_2->width, dst_2->height, dst_2->widthStep, System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) dst_2->imageData);
		ptbFilter->Refresh();

		// Convert input image to HSV		
		cvtColor(dst, hsv_image, COLOR_BGR2HSV);
		// Create mask of blue color
		inRange(hsv_image, Scalar(100, 150, 0), Scalar(140, 255, 255), mask);
		bitwise_and(hsv_image, hsv_image, fin_img, mask);
		cvtColor(fin_img, fin_img, COLOR_HSV2BGR);
		dst_1 = cvCloneImage(&(IplImage)fin_img);
		dst_2 = cvCreateImage(cvSize((int)(dst_1->width*0.5), (int)(dst_1->height*0.5)), dst_1->depth, dst_1->nChannels);
		cvResize(dst_1, dst_2);
		ptbDetect->Image= gcnew System::Drawing::Bitmap(dst_2->width, dst_2->height, dst_2->widthStep, System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) dst_2->imageData);
		ptbDetect->Refresh();
	}
	
};
}
