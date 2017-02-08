//�̹��� ����, �Ӽ�
/*
#include <opencv\cv.h>
#include <opencv\highgui.h>

int main()
{
	IplImage *srcImage;
	if((srcImage=cvLoadImage("HappyFish.jpg",CV_LOAD_IMAGE_GRAYSCALE))==NULL)
		return -1;

	printf("colorModel  =%s\n", srcImage->colorModel);
	printf("channelSeq  =%s\n", srcImage->channelSeq);
	printf("image pixel size  =%d x %d \n", srcImage->width,srcImage->height);
	printf("# of channel  =%d \n",srcImage->nChannels);
	printf("depth  =%d\n",srcImage->depth);
	
	//cvNamedWindow("HappyFish", CV_WINDOW_AUTOSIZE);
	cvShowImage("HappyFish", srcImage);
	cvWaitKey(0);
	//cvSaveImage("HappyFish.bmp", srcImage);
	cvDestroyAllWindows();
	//cvReleaseImage(&srcImage);
	return 0;

}
*/
//===================================================================================
//���� ���
/*
#include <opencv\cv.h>
#include <opencv\highgui.h>

void main()
{
	IplImage* frame;
	CvCapture* video = cvCaptureFromFile("Center_goryeong2_1_7_3.avi"); // ������ ���� �ҷ�����

	cvNamedWindow("video",0);

	while(1)
	{
		cvGrabFrame(video); // ���������� ���� �ϳ��ϳ��� �������� ��µ� ���
		frame=cvRetrieveFrame(video,0); // Grab���� ���� �����Ӻ��� ������ ����
//		cvQueryFrame(video);

		if(!frame)
			break;

		cvShowImage("video",frame);

		if (cvWaitKey(10)>=0)
			break;
	}
		cvReleaseCapture(&video);
		cvDestroyWindow("Video");
}
*/
//===========================================================================
// �������, ������ �Ӽ� ����
/*
//#include <stdio.h>
#include <opencv\cv.h>
#include <opencv\highgui.h>

int main()
{
	IplImage* frame;
	int width;
	int height;
	double fps;
	int nTotalFrame;
	int fourcc;
	char *ptr;
	char chKey;

	CvCapture* capture = cvCaptureFromFile("Center_goryeong2_1_7_3.avi");
	if(!capture)
	{
		printf("the video file was not found");
		return 0;
	}

	width = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);       // ���� �������� ����ũ��
	height = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);     // ����ũ��
	fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);                       // ������ �ӵ�
	nTotalFrame = (int) cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);  // �ڵ��� 4����
	fourcc = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FOURCC);

	printf("fps = %f, frame_size = (%d, %d)\n", fps , width, height);
	printf("nTotalFrame = %d\n", nTotalFrame);
	ptr = (char *)&fourcc;
	printf("fourcc = %c%c%c%c\n", ptr[0], ptr[1], ptr[2], ptr[3]);

//	cvNamedWindow("video frame", CV_WINDOW_AUTOSIZE); // CV_WINDOW_AUTOSIZE �϶� ���� ©��
	cvNamedWindow("video frame", 0); // ��©��
	
	while(1)
//	for(;;)
	{
//		frame = cvGrabFrame(capture);
//		frame = cvRetrieveFrame(capture);
		frame = cvQueryFrame(capture);  // ���������� capture�� ���� ���� �������� ���, ������ Ǯ� ���� �����͸� ��ȯ.
                                                // Grab, Retrieve �Լ��� ��� ������ ����� ����.
		if(!frame)
		{
			break;
		}
		cvShowImage("video frame", frame);

		chKey = cvWaitKey(10);
		if(chKey == 27)
		{
			break;
		}
	}	

	cvDestroyAllWindows();
	cvReleaseCapture(&capture);
	return 0;
}
*/
//===========================================================================
// �̹��� ��ǥ
/*
#include <opencv\cv.h>
#include <opencv\highgui.h>
//#include <opencv2\imgproc\imgproc.hpp>

void mouse(int event, int x, int y, int flags, void* userdata )
{
	if (event == CV_EVENT_LBUTTONDOWN) // ���콺 ��Ŭ��
	{
//		cout << " ��ǥ = ("<< x <<", "<< y <<")" << endl;
		printf("��ǥ = (%d, %d)", x, y);
	}
}

int main()
{
	IplImage *srcImage = cvLoadImage("HappyFish.jpg",1);
	cvShowImage("HappyFish",srcImage);
	cvSetMouseCallback("HappyFish",mouse, NULL);
	cvWaitKey(0);
}
*/
//===========================================================================
// �̹��� ROI ���� 1.
/*
#include <opencv\cv.h>
#include <opencv\highgui.h>

int main()
{

	IplImage *dstImage;
	IplImage *srcImage;
	if((srcImage = cvLoadImage("HappyFish.jpg",1))== NULL)
		return -1;

	//IplImage *dstImage;
	dstImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, 3);

	cvSet(dstImage, cvScalarAll(255), 0); // dstImage ��� �� ����
//	cvSet(dstImage, CV_RGB(0,0,255),0);

//	cvRectangle(srcImage, cvPoint(0, srcImage->height/2), cvPoint(srcImage->width/2-1, srcImage->height-1), CV_RGB(0,0,255), 2);
	cvRectangle(srcImage, cvPoint(0, srcImage->height/2), cvPoint(srcImage->width/2-1, srcImage->height-1), cvScalar(0,0,255), 2, 8);//, 0); // �簢�� ����, ��, �β� ����

	cvSetImageROI(srcImage, cvRect(0, srcImage->height/2, srcImage->width/2, srcImage->height));
	cvSetImageROI(dstImage, cvRect(0, 0, srcImage->width/2, srcImage->height/2));

	cvSetImageCOI(srcImage, 0); // ���� ä�� ����(0:��� ä��, 1: ù��° ä��, 2: �ι��� ä��)
	cvCopy(srcImage, dstImage, 0);

	cvResetImageROI(srcImage);
	cvResetImageROI(dstImage);
//	cvSetImageCOI(srcImage, 0);

//	cvNamedWindow("Happy RGB", CV_WINDOW_AUTOSIZE);
	cvShowImage("HappyFish RGB", srcImage);
//	cvNamedWindow("Blue channel", CV_WINDOW_AUTOSIZE);
	cvShowImage("Blue channel", dstImage);
		
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&srcImage);
	cvReleaseImage(&dstImage);
	return 0;
}
*/
//---------------------------------------------------------------------------
// �̹��� ROI ���� 2.
/*
#include <opencv\cv.h>
#include <opencv\highgui.h>

//using namespace cv;

void main ()
{
	IplImage * Img = cvLoadImage ("HappyFish.jpg",1);
	IplImage * Img_copy = (IplImage*)cvClone(Img);
	//IplImage * Img_copy = cvCloneImage(Img);

	cvSetImageROI(Img_copy, cvRect(100,150,140,100));

	cvResetImageROI(Img);

	cvShowImage("Origin", Img);
	cvShowImage("ROI", Img_copy);

	cvWaitKey(0);

	cvReleaseImage(&Img);
	cvReleaseImage(&Img_copy);

	//cvDestroyWindow("Oorigin");
	//cvDestroyWindow("ROI");
	cvDestroyAllWindows();

}
*/
//---------------------------------------------------------------------------

//������ ������ �Ӽ�, ROI
/*
#include <opencv\cv.h>
#include <opencv\highgui.h>

int main()
{
	int i=0;
	int key=0;
	int width;
	int height;
	int TotalFrame;
	double fps;

	IplImage *frame;
	IplImage *dstImage; //
	CvCapture *video = cvCaptureFromFile("Center_goryeong2_1_7_3.avi");
	cvNamedWindow("video",0);
	cvNamedWindow("dstImage",0);

	width = (int) cvGetCaptureProperty(video, CV_CAP_PROP_FRAME_WIDTH);
	height = (int) cvGetCaptureProperty(video, CV_CAP_PROP_FRAME_HEIGHT);
	TotalFrame = (int) cvGetCaptureProperty(video, CV_CAP_PROP_FRAME_COUNT);
	fps = (double) cvGetCaptureProperty(video, CV_CAP_PROP_FPS);

	printf("TotalFrame = %d\n", TotalFrame);
	printf("Frame_size = (%d, %d)\n", width, height);
	printf("fps = %f", fps);

	while(1)
	{
		cvSetCaptureProperty(video, CV_CAP_PROP_POS_FRAMES, i);

		cvGrabFrame(video);
		frame = cvRetrieveFrame(video, 1);

		dstImage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3); //
		cvSet(dstImage, cvScalarAll(0), 0); //

		cvRectangle(frame, cvPoint(frame->width/3, frame->height/2-1), cvPoint(frame->width/2-1, frame->height-1), cvScalar(0,0,255), 2, 8);

		cvSetImageROI(frame, cvRect(frame->width/3, frame->height/3, frame->width/2, frame->height/2));
//		cvSetImageROI(frame, cvRect(100,100,200,200));
		cvSetImageROI(dstImage, cvRect(0, 0, frame->width/2, frame->height/2));

//		cvSetImageCOI(frame, 0);
		cvCopy(frame, dstImage, 0);

		cvResetImageROI(frame);
		cvResetImageROI(dstImage);

		cvShowImage("video", frame);
		cvShowImage("dstImage", dstImage); //

		key = cvWaitKey(0);
		if (!frame)
		{
			break;
		}

		else if (key==49)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	cvReleaseCapture(&video);
//	cvDestroyWindow("video");
	cvDestroyAllWindows();
	//cvReleaseImage(&frame);
	//cvReleaseImage(&dstImage);
}

*/

//===========================================================================
// ���� ���, �Ӽ�, ��ǥ

#include <opencv\cv.h>
#include <opencv\highgui.h>

void mouse(int event, int x, int y, int flags, void* userdata)
{
	if(event == CV_EVENT_LBUTTONDOWN)
	{
		printf("��ǥ = (%d, %d)\n", x, y);
	}
}

int main()
{
	int i=0;
	int key=0;
	int width;
	int height;
	int TotalFrame;
	double fps;

	IplImage *frame;
	IplImage *dstImage; //
	CvCapture *video = cvCaptureFromFile("Center_goryeong2_1_7_3.avi");
	cvNamedWindow("video",0);
	cvNamedWindow("dstImage",0);

	width = (int) cvGetCaptureProperty(video, CV_CAP_PROP_FRAME_WIDTH);
	height = (int) cvGetCaptureProperty(video, CV_CAP_PROP_FRAME_HEIGHT);
	TotalFrame = (int) cvGetCaptureProperty(video, CV_CAP_PROP_FRAME_COUNT);
	fps = (double) cvGetCaptureProperty(video, CV_CAP_PROP_FPS);

	printf("TotalFrame = %d\n", TotalFrame);
	printf("Frame_size = (%d, %d)\n", width, height);
	printf("fps = %f\n", fps);

	while(1)
	{
		cvSetCaptureProperty(video, CV_CAP_PROP_POS_FRAMES, i);

		cvGrabFrame(video);
		frame = cvRetrieveFrame(video, 1);

	//	dstImage = cvCloneImage(frame);
		dstImage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3); //
	//	dstImage = cvCreateImage(cvSize(512,512), IPL_DEPTH_8U, 3);

		cvSet(dstImage, cvScalarAll(0), 0); //

		cvRectangle(frame, cvPoint(frame->width/3, frame->height/3), cvPoint(frame->width/2, frame->height/2), cvScalar(0,0,255,0), 2, 8, 0);

	//	cvSetImageROI(frame, cvRect(frame->width/3, frame->height/3, frame->width/2, frame->height/2));
		cvSetImageROI(frame, cvRect(343, 316, frame->width/3, frame->height/3));
		cvSetImageROI(dstImage, cvRect(0, 0, frame->width/3, frame->height/3));

//		cvSetImageCOI(frame, 0);
		cvCopy(frame, dstImage, 0);

		cvResetImageROI(frame);
		cvResetImageROI(dstImage);

		cvShowImage("video", frame);
		cvSetMouseCallback("video", mouse, NULL);
		cvShowImage("dstImage", dstImage); //

		key = cvWaitKey(0);
		if (!frame)
		{
			break;
		}

		else if (key==49)
		{
			i++;
		}
		else
		{
			break;
		}
	}

	cvReleaseCapture(&video);
//	cvDestroyWindow("video");
	cvDestroyAllWindows();
	//cvReleaseImage(&frame);
	//cvReleaseImage(&dstImage);
}

//================================================================
// �ؽ�Ʈ �о�ͼ� �� ���� ī��Ʈ(��)
/*
//#include <opencv\cv.h>
//#include <opencv\highgui.h>
#include <iostream>
#include <fstream>
//#include <string>
using namespace std;

int main()
{
	fstream file;
//	ifstream file;

	char ch;
//	char ck;
	int a = 0;    // 0
	int b = 0;    // 1
	int c = 0;    // 2
	int line = 1; // �ٹ�ȣ

	file.open ("train_label(Center_goryeong2_1_7_3).txt");

	while (file)
	{
		//file.get(ch);
		ch = file.get();
		//ck = file.get();
		//cout <<ch ;
		//cout << ck ;

		if (ch == 'i')
		{
			cout << line << "::"; //<< ch;
			//ch = file.get();
			line++;
		}
		cout << ch;

		if (ch == ' ')
		{
			ch = file.get();
			if ( ch == '0' )
			{
				a++;
		//		++a;
				cout << ch <<" - ( " << a << " )" ;
			}
			else if ( ch == '1' )
			{
				b++;
		//		++b;
				cout << ch <<" - ( " << b << " ) " ;
			}
			else if ( ch == '2' )
			{
				c++;
		//		++c;
				cout << ch <<" - ( " << c << " ) " ;
			}
		}
	}
	
	file.close();
	cout << endl;
	cout << " 0 : " << a << endl;
	cout << " 1 : " << b << endl;
	cout << " 2 : " << c << endl;
	cout << "lint : " << line-1 << endl;

	return 0;
}
*/

//-----------------------------------------------------------------
// �� ���� ī��Ʈ(��)
/*
#include <algorithm>
#include <fstream>  // NOLINT(readability/streams)
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

std::vector<std::string> &str_split(const std::string &s, char delim, std::vector<std::string> &elems)
{
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim))
  {
      elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> str_split(const std::string &s, char delim) 
{
  std::vector<std::string> elems;
  str_split(s, delim, elems);
  return elems;
}


  std::ifstream infile("./result/train_label(Center_Seonseo-Hyeonpung_4lane-1).txt");
//ifstream infile("train_label(Center_goryeong2_1_7_3).txt");
  std::vector<std::pair<double, double> > ground_truth;
  std::vector<std::string> lines;
  std::string line;
  
  int main()
  {
	  while (std::getline(infile, line)) 
	  {
		  lines.push_back(line);
	  }
	  std::vector<std::string> tokens;

	  int frame = 0;
	  int a = 0;
	  int b = 0;
	  int c = 0;
	  int d = 1;

	  while(1) 
	  {
		  tokens = str_split(lines[frame], ' ');
	  
		  //cout << tokens[0] << endl;
		  //cout << tokens[1] << endl;
		  
		  std::cout<< d << ">>" << " tokens :: " << tokens[1] << std::endl;
		  
		  if (atoi(tokens[1].c_str()) == 0) 
		  {
			  a++;
			  //cout << "0 :: " << a << endl;
			  //cout << "CHECK!!!" << endl;
		  } 
		  else if (atoi(tokens[1].c_str()) == 1) 
		  {
			  b++;
			 //cout << "1 :: " << b << endl;
			 // cout << "CHECK!!!" << endl;
		  } 
		  else if (atoi(tokens[1].c_str()) == 2)
		  {
			  c++;
			  //cout << "2 :: " << c << endl;
			  //cout << "CHECK!!!" << endl;
		  }
		  
//		  else if (!atoi(tokens[1].c_str())
//		  {
//			  d = d-1;
//		  }

		  frame++;
		  d++;
		  
		  cout << " 0 :: " << a << endl;
		  cout << " 1 :: " << b << endl;
		  cout << " 2 :: " << c << endl;
		  cout << " line :: "<< d-1 << endl;
	  }


 }
 */