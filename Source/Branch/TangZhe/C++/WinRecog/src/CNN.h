#ifndef _CNN_H_
#define _CNN_H_

#include "DataLoading.h"
#include "CNNLayers.h"

class C_CNN
{
	C_CNN();
	~C_CNN();

public:
    static void CNNSetup(C_DataList &data_i, C_CNN_Layers &net_o);
    static void CNNTrain(C_DataList &data_i, C_CNN_Layers &net_o, Opts &opts_i);

private:
    static C_CNN_Layers CNNff(C_CNN_Layers &net, C_DataList &data_i);
   // static C_CNN_Layers CNNbp(C_CNN_Layers &net, C_DataList &data_i);
};
#endif