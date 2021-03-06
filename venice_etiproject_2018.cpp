/* venice_etiproject_2018.cpp: definisce il punto di ingresso dell'applicazione console.
* Created on: 7 May 2018
*   Author: Federico Favia e Martin De Pellegrini

*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
//#include <cv.h>
//#include <cxcore.h>
//#include <cvaux.h>
//#include <highgui.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>
#include <fstream>

#include "bg.h"
#include "blob.h"
#include "median_value.h"

using namespace cv;
using namespace std;


int main()
{
	Mat myPicture;
	Mat src;
	Mat bg;

	Mat motion;
	Mat motion_mask;
	Mat modif_motion_mask;

	int nFrames;
	int tc = 0;
	const int training_nr = 20;

	//variables for counting and mobile average algorithm
	int currentFrame;
	double nBlob = 0;
	double totBlob = 0;
	double media = 0;
	int x = 0;
	int fps = 31; //framerate video = tempo di update della media
	int durata_video = 1319; //durata video video input in secondi
	nFrames = fps * durata_video;

	//variables for mobile median algorithm
	vector<double> v;

	//graphs in Matlab
	vector<double> vv;
	ofstream myfile;
	myfile.open("nblob.txt");

	//openvideo
	//VideoCapture cap("MAR05_06_11.00_22min_2x.mp4");
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "cannot open video" << endl;
		return 0;
	}

	tc = 0; //training frame counter
	Mat tmp; //tmp matrix structure

			 //----------------------------MASK----------------------------
	int w, h;
	cap >> src;
	w = src.size().width;
	h = src.size().height;
	cout << w << "  " << h << endl;

	Point corners[1][8];
	corners[0][0] = Point(0,640);
	corners[0][1] = Point(780,640);
	corners[0][2] = Point(900,430);
	corners[0][3] = Point(1020,430);
	corners[0][4] = Point(1062,340);
	corners[0][5] = Point(950,316);
	corners[0][6] = Point(800,316);
	corners[0][7] = Point(719,340);

	const Point* corner_list[1] = {corners[0] };
	int numPoints = 8;
	int numPolygons = 1;
	int line_type = 8;
	Mat mask(h, w, CV_8UC3, Scalar(0,0,0));
	fillPoly(mask, corner_list, &numPoints, numPolygons, Scalar(255, 255, 255), line_type);
	
	for (int i = 0; i < nFrames; i++) {
		currentFrame = i + 1;

		cap >> myPicture;
		bitwise_and(myPicture,mask,tmp); //masking

		cvtColor(tmp, tmp, CV_RGB2GRAY); //scaladigrigi
		GaussianBlur(tmp, tmp, Size(3, 9), 20, 20); //per togliere rumore onde,

		if (tc<training_nr) {
			bg_train(tmp, &bg);
			tc++;
		}
		else {
			//bg subtraction
			absdiff(bg, tmp, motion);

			//mask thresholding
			threshold(motion, motion_mask, 50, 255, THRESH_BINARY);

			//incremental bg update
			bg_update(tmp, &bg, motion_mask, 0.005);

			//filtri morfologici
			/*Mat element_e = getStructuringElement(MORPH_ELLIPSE, Size(15,3), Point(2,2)); //elemento ellisse orizzontale per erodere
			erode(motion_mask, modif_motion_mask, element_e); //erodo
			Mat element_d = getStructuringElement(MORPH_ELLIPSE, Size(45,35), Point(2,2)); //elemento ellisse verticale per dilatare
			dilate(modif_motion_mask, modif_motion_mask, element_d); //dilato in "orizzontale"
			*/
			//filtri morfologici in caso di video velocizzati

			Mat element_e = getStructuringElement(MORPH_ELLIPSE, Size(5, 3), Point(2, 2));
			erode(motion_mask, modif_motion_mask, element_e);
			Mat element_d = getStructuringElement(MORPH_ELLIPSE, Size(20, 20), Point(2, 2));
			dilate(modif_motion_mask, modif_motion_mask, element_d);

			//results display
			//imshow("Motion", motion_mask);
			//imshow("Original", myPicture);
			//imshow("Background", bg);
			//imshow("Modified Motion", modif_motion_mask);

			//Blob tracking and counting algorithm
			nBlob = to_blob(modif_motion_mask, motion_mask); //1st parameter the pic where detect blobs, 2nd on which pic show blobs
																   //cout << "nBlob=" << nBlob << endl;

																   //Mobile Average Algorithm
			totBlob = totBlob + nBlob; //incrementa i blob contati ogni frame

			vv.push_back(nBlob); //inserimento in un vettore per file txt da esportare in matlab per grafici

			if (x == fps) { //output media e mediana ogni fps frame

				media = (totBlob / currentFrame); //media integrale aggiornata al currentframe
				cout << "Contate finora una MEDIA di " << media << " barche dopo " << currentFrame / fps << " sec" << endl;

				v.push_back(nBlob); //inserimento in un vettore per funzione mediana
				cout << "Contate finora una MEDIANA di " << median_value(v) << " barche dopo " << currentFrame / fps << " sec" << endl;

				x = 0; //riaggiorno
			}
			else {
				x++;
			}

			waitKey(30);
		}//end of  if
	}//end of for

	 //Some final result
	cout << "Resume Final Results:" << endl << endl;
	cout << "MEDIA  di " << (totBlob / nFrames) << " barche" << endl; //MEDIA finale
	cout << "MEDIANA di " << median_value(v) << " barche" << endl; //MEDIANA finale

																   //export nBlob vector passing frames
	vector<double>::iterator vi;
	for (vi = vv.begin(); vi != vv.end(); vi++) {
		myfile << *vi << "\n";
	}
	myfile.close();
	
	return 0;
}

