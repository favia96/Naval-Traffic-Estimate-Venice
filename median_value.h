/*
* median_value.h
*
*  Created on: 7 May 2018
*      Author: Federico Favia e Martin De Pellegrini
*/

#ifndef MEDIAN_VALUE_H_
#define MEDIAN_VALUE_H_

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double median_value(vector<double> _v) {
	double median;
	sort(_v.begin(), _v.end());
	int l = int(_v.size());
	int mid = l / 2;
	if ((_v.size()) % 2 != 0) {
		median = _v[mid];
	}
	else {
		median = (_v[mid - 1] + _v[mid]) / 2;

	}
	return median;
}

#endif MEDIAN_VALUE_H_