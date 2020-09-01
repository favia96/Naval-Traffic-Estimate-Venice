/*
* bg.cpp
*
*  Created on: 7 May 2018
*
*/

#include "stdafx.h"
#include "bg.h"

void  bg_train(Mat img, Mat* back)
{
	static int ctr = 1;
	double a = 0.5;

	if (ctr == 1)
	{
		printf("Initial bg storage..\n");
		img.copyTo(*back);
	}
	else
	{
		printf("Averaging bg.\n");
		*back = *back*a + img * (1 - a);
	}

	ctr++;

}


void bg_update(Mat img, Mat* back, Mat mask, double a)
{
	//printf("Incremental bg update..\n");

	//non selective
	*back = *back*(1 - a) + img * a;

	//	for(int r=0;r<img.rows;r++)
	//		for(int c=0;c<img.cols;c++)
	//		if(mask.at<int>(r,c)==1)
	//			back.at<int>(r,c) = back.at<int>(r,c)*(1-a)+img.at<int>(r,c)*a;

}

