#define DLL_API extern "C" _declspec(dllexport)
#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

DLL_API void distance(unsigned int* labelImage, unsigned int* distanceImage, int width, int height, int numberoflabel, unsigned int* resultImage);
DLL_API void distance(unsigned int* labelImage, unsigned int* distanceImage, int width, int height, int numberoflabel, unsigned int* resultImage)
{
	Mat image_label(width, height, CV_8UC1, labelImage);
	Mat image_distance(width, height, CV_8UC1, distanceImage);
	Mat newImage(width, height, CV_8UC1, resultImage);

	for (int k = 0; k < numberoflabel; ++k)
	{
		int maxIndex = 0;
		for (int i = 0; i < newImage.rows; ++i)
		{
			uchar* pt_label = image_label.ptr<uchar>(i);
			uchar* pt_distance = image_distance.ptr<uchar>(i);
			for (int j = 0; j < newImage.cols; ++j)
			{
				if (pt_label[j] == k + 1)
				{
					if (pt_distance[j]>maxIndex)
					{
						maxIndex = pt_distance[j];
					}
				}
			}
		}
		for (int i = 0; i < newImage.rows; ++i)
		{
			uchar* pt_label = image_label.ptr<uchar>(i);
			uchar* pt_distance = image_distance.ptr<uchar>(i);
			uchar* pt_result = newImage.ptr<uchar>(i);
			for (int j = 0; j < newImage.cols; ++j)
			{
				if (pt_label[j] == k + 1)
				{
					if (pt_distance[j] == maxIndex || pt_distance[j] == maxIndex - 1 || pt_distance[j] == maxIndex - 2)
					{
						pt_result[j] = 1;
					}
				}
			}
		}
	}
}