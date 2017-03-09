#ifndef _RGB_CONVERTOR_H_
#define _RGB_CONVERTOR_H_

#include "stdafx.h"
#include <memory>

class C_RGB_CONVERTOR
{
public:
	C_RGB_CONVERTOR(){};
	~C_RGB_CONVERTOR(){};

public:
    static void RGB2GrayMatlab(double* gray, const int sizeOfPixel, const char* imageData);
	static void RGB2GrayInPhotoShop(double* gray, const int sizeOfPixel, const char* imageData);
	static void RGB2GrayAverage(double* gray, const int sizeOfPixel, const char* imageData);

    static void Rgb2Hsv(double R, double G, double B, double& H, double& S, double& V);
};
#endif