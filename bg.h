/*
* bg.h
*
*  Created on: 7 May 2018
*
*/

#ifndef BG_H_
#define BG_H_

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


void bg_train(Mat img, Mat* bg);
void bg_update(Mat img, Mat* back, Mat mask, double a);


#endif BG_H_