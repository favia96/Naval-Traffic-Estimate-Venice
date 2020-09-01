/*
* blob.h
*
*  Created on: 7 May 2018
*      Author: Federico Favia e Martin De Pellegrini
*/

#ifndef BLOB_H_
#define BLOB_H_

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

double to_blob(Mat& img_blob, Mat& original) {
	//1^ PARTE SUI BLOB: parametri -> Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

	//change color
	params.filterByColor = 1;
	params.blobColor = 255;

	// Change thresholds
	params.minThreshold = 10;
	params.maxThreshold = 200;

	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 1000;
	params.maxArea = 10000;

	// Filter by Circularity
	params.filterByCircularity = false;
	//params.minCircularity = 0.001;

	// Filter by Convexity
	params.filterByConvexity = false;
	//params.minConvexity = 0.001;

	// Filter by Inertia
	params.filterByInertia = false;
	//params.minInertiaRatio = 0.01;

	//2^ PARTE SUI BLOB -> Set up detector with params
	SimpleBlobDetector detector; //non funziona con opencv 3.4
	//SimpleBlobDetector detector;

	// Detect blobs.
	std::vector<KeyPoint> _keypoints;
	detector.detect(&img_blob, _keypoints);

	// Draw detected blobs as blue circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
	Mat im_with_keypoints;
	drawKeypoints(original, _keypoints, im_with_keypoints, Scalar(255, 0, 0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Show blobs
	imshow("keypoints", im_with_keypoints);

	// n° blob presenti in quel frame
	double g= double(_keypoints.size());
	return g;

}


#endif BLOB_H_