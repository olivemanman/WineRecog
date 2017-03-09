#include <math.h>
#include <stdlib.h>
#include "CNN.h"
#include "alg.hpp"

C_CNN::C_CNN()
{

}

C_CNN::~C_CNN()
{

}

void C_CNN::CNNSetup(C_DataList &data_i, C_CNN_Layers &net_o)
{
	int inputmaps = 1;

	//get first image2D size
	C_Data initialData = data_i.AtImage(0);
	Size2D mapsize = initialData.m_size;

	for (int l = 0; l < net_o.LayersNum(); l++)
	{
        C_Layer curLayer = net_o.layers[l];

		if (curLayer.LayerName().compare("s") == 0)
		{
            mapsize /= curLayer.GetParam("scale");
            curLayer.PushNet(Dimen(1), "b");
		}

        if (curLayer.LayerName().compare("c") == 0)
		{
            int curKernelSize = static_cast<int>(curLayer.GetParam("kernelsize"));
            int curOutputsMaps = static_cast<int>(curLayer.GetParam("outputmaps"));

			mapsize -= (curKernelSize - 1.0);
            double fan_out = curOutputsMaps*pow(curKernelSize, 2);
			
			//size
			std::vector<int> inputmapsDim;
			inputmapsDim.push_back(curKernelSize);//x1, 
			inputmapsDim.push_back(curKernelSize);//x2, matrix
			inputmapsDim.push_back(inputmaps);//y
			inputmapsDim.push_back(curOutputsMaps);//z

            Dimen curDim;
            curDim.PushValue(curKernelSize);
            curDim.PushValue(curKernelSize);
            curDim.PushValue(inputmaps);
            curDim.PushValue(curOutputsMaps);
            curLayer.PushNet(curDim, "k");

			for (int j = 0; j < curOutputsMaps; j++)
			{
				double fan_in = inputmaps*pow(curKernelSize, 2);

				for (int i = 0; i < inputmaps; i++)
				{

					for (int m = 0; m < curKernelSize; m++)
					{
						for (int n = 0; n < curKernelSize; n++)
						{
                            double v = (RandZeroToOne() - 0.5)*2.0*sqrt(6.0 / (fan_in + fan_out));

                            Coord curIndex;
                            curIndex.PushValue(n);
                            curIndex.PushValue(m);
                            curIndex.PushValue(i);
                            curIndex.PushValue(j);
                            curLayer.SetNetValue(v, curIndex, "k");
						}
					}
				}
			}

			string tmpName2 = "b";
            curLayer.PushNet(Dimen(curOutputsMaps), "b");
			inputmaps = static_cast<int>(curLayer.GetParam("outputmaps"));
		}
	}

	double fvnum = mapsize.x*mapsize.y*inputmaps;
	double onum = data_i.GetTotalLabel();

    C_Layer ffb("ffb");
    Dimen ffb_dim(static_cast<int>(onum));
    ffb.PushNet(ffb_dim, "ffb");

    Dimen ffw_dim(static_cast<int>(fvnum), static_cast<int>(onum));
    C_Layer ffw("ffw");
    ffw.PushNet(ffw_dim, "ffw");

    for (int j = 0; j < ffw_dim.GetValue(1); j++)
    {
        for (int i = 0; i < ffw_dim.GetValue(0); i++)
        {
            Coord coord(i, j);
            double v = (RandZeroToOne() - 0.5) * 2 * sqrt(6.0 / (onum + fvnum));
            ffw.SetNetValue(v, coord, "ffw");
        }
    }

    net_o.PushLayer(ffb);
    net_o.PushLayer(ffw);
}

void C_CNN::CNNTrain(C_DataList &data_i, C_CNN_Layers &net_o, Opts &opts_i)
{
    int m = data_i.ImageNum();
    int numbatches = m / opts_i.batchsize;

    if (numbatches % 1 != 0)
    {
        throw("wrong batch size");
    }

    for (int i = 0; i < opts_i.numepochs; i++)
    {
        std::vector<int> kk = Randperm<int>(m);

        for (int l = 0; l < numbatches; l++)
        {
            int ll = l*opts_i.batchsize;
            
            std::vector<int> kIndexVec;
            for (int i = 0; i < opts_i.batchsize; i++)
            {
                kIndexVec.push_back(i + ll);
            }

            //read x for batch random
            std::vector<int> subKK = ComposeVectAccordingToVecIndex<int>(kk, kIndexVec);

            C_DataList batch_data = data_i.GetSubData(subKK);

            net_o = CNNff(net_o, batch_data);
           // net_o = CNNbp(net_o, batch_data);
        }
    }
}

C_CNN_Layers C_CNN::CNNff(C_CNN_Layers &net, C_DataList &data_i)
{
    int n = net.LayersNum();
    //net.layers{1}.a{1} = x; tangzhe
    int inputmaps = 1;

    for (int ll = 2; ll <= n; ll++)
    {
        int l = ll - 1;

        if (net.layers[l].LayerName().compare("c") == 0)
        { //!!below can probably be handled by insane matrix operations
            for (int jj = 1; jj <= net.layers[l].GetParam("outputmaps"); jj++) // for each output map
            {
                int j = jj - 1;

                Size3D tmpsize1(data_i.AtImage(0).m_size.x, data_i.AtImage(0).m_size.y, data_i.ImageNum());
                Size3D tmpsize2(net.layers[l].GetParam("kernelsize") - 1, net.layers[l].GetParam("kernelsize") - 1, 0);
                Size3D tmpsize = tmpsize1 - tmpsize2;
                shared_ptr<double> z(new double[tmpsize.x * tmpsize.y * tmpsize.z]);

                for (int ii = 1; ii <= inputmaps; ii++)
                {
                    int i = ii - 1;

                }
            }
        }
    }

    return net;
}
