// WinRecog.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include "DataLoading.h"
#include "CNN.h"
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;
int _tmain()
{
    //get images and label
    string train_folder = "..\\..\\..\\..\\..\\..\\..\\Data\\02Data";
    string test_folder = "..\\..\\..\\..\\..\\..\\..\\Data\\02Data";
    const int resizedWidth = 32;
    const int resizedHeight = 32;

	C_DataList trainImages;
	C_DataList testImages;
	C_DataLoading::Loading(trainImages, train_folder, resizedWidth, resizedHeight);
	C_DataLoading::Loading(testImages, test_folder, resizedWidth, resizedHeight);
	
	//CNN layers
    C_Layer layer_1("i");
    C_Layer layer_2("c");
    layer_2.PushParam(std::make_pair(6.0, "outputmaps"));
    layer_2.PushParam(std::make_pair(5.0, "kernelsize"));
    C_Layer layer_3("s");
    layer_3.PushParam(std::make_pair(2.0, "scale"));
    C_Layer layer_4("c");
    layer_4.PushParam(std::make_pair(12.0, "outputmaps"));
    layer_4.PushParam(std::make_pair(5.0, "kernelsize"));
    C_Layer layer_5("s");
    layer_5.PushParam(std::make_pair(2.0, "scale"));

	C_CNN_Layers cnn_model;
	cnn_model.PushLayer(layer_1);
	cnn_model.PushLayer(layer_2);
	cnn_model.PushLayer(layer_3);
	cnn_model.PushLayer(layer_4);
	cnn_model.PushLayer(layer_5);

	//setput
	C_CNN::CNNSetup(trainImages, cnn_model);

    //train
    Opts opts;
    opts.falpha = 1.0;
    opts.batchsize = 8;
    opts.numepochs = 200;

    C_CNN::CNNTrain(trainImages, cnn_model, opts);
    return 0;
}

