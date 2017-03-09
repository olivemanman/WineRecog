
#include "stdafx.h"
#include <math.h>
#include <memory>
#include "RGBConvertor.h"

//Gray = R*0.299 + G*0.587 + B*0.114
void C_RGB_CONVERTOR::RGB2GrayMatlab(double* gray, const int sizeOfPixel, const char* imageData)
{
	for (int i = 0; i < sizeOfPixel; i++)
	{
        unsigned char b = (unsigned char)imageData[3 * i + 0];
        unsigned char g = (unsigned char)imageData[3 * i + 1];
        unsigned char r = (unsigned char)imageData[3 * i + 2];
		gray[i] = r * 0.2989 + g * 0.5870 + b * 0.1140;
	}
}

//Adobephotoshop: Gray = (R^2.2 * 0.2973 + G^2.2 * 0.6274 + B^2.2 * 0.0753)^(1/2.2)
void C_RGB_CONVERTOR::RGB2GrayInPhotoShop(double* gray, const int sizeOfPixel, const char* imageData)
{
	for (int i = 0; i < sizeOfPixel; i++)
	{
		unsigned char b = imageData[3 * i + 0];
		unsigned char g = imageData[3 * i + 1];
		unsigned char r = imageData[3 * i + 2];
		gray[i] = pow((pow(r, 2.2) * 0.2973 + pow(g, 2.2) * 0.6274 + pow(b, 2.2) * 0.0753), 1 / 2.2);
	}
}

//gray = (r + g + b) / 3
void C_RGB_CONVERTOR::RGB2GrayAverage(double* gray, const int sizeOfPixel, const char* imageData)
{
	for (int i = 0; i < sizeOfPixel; i++)
	{
		unsigned char b = imageData[3 * i + 0];
		unsigned char g = imageData[3 * i + 1];
		unsigned char r = imageData[3 * i + 2];
		gray[i] = (b + g + r) / 3;
	}
}

void C_RGB_CONVERTOR::Rgb2Hsv(double R, double G, double B, double& H, double& S, double& V)
{
    // r,g,b values are from 0 to 1  
    // h = [0,360], s = [0,1], v = [0,1]  
    // if s == 0, then h = -1 (undefined)  
    double min = 0.0, max = 0.0, delta = 0.0, tmp = 0.0;
    tmp = R > G ? G : R;
    min = tmp > B ? B : tmp;
    tmp = R > G ? R : G;
    max = tmp > B ? tmp : B;
    V = max; // v  
    delta = max - min;
    if (max != 0.0)
        S = delta / max; // s  
    else
    {
        // r = g = b = 0 // s = 0, v is undefined  
        S = 0.0;
        H = 0.0;
        return;
    }
    if (delta == 0.0)
    {
        H = 0.0;
        return;
    }
    else if (R == max)
    {
        if (G >= B)
            H = (G - B) / delta; // between yellow & magenta  
        else
            H = (G - B) / delta + 6.0;
    }
    else if (G == max)
        H = 2.0 + (B - R) / delta; // between cyan & yellow  
    else if (B == max)
        H = 4.0 + (R - G) / delta; // between magenta & cyan  
    H *= 60.0; // degrees  
}