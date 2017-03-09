#ifndef _CNN_LAYER_H_
#define _CNN_LAYER_H_

#include <vector>
#include "Common.h"

using namespace std;
enum e_LayerType
{
	e_input = 0,
	e_convolution = 1,
	e_scale = 2,
    e_ffb = 3,
    e_ffw = 4,

	e_basic = 100
};

//////////////////////////////////////////////////////////////////////////
class C_Net //can be any dimension
{
public:
	C_Net();
	C_Net(const std::string name);
	C_Net(const Dimen dim, const std::string name);
	~C_Net(){}

	void Push1D(const double v);

    void SetNet(const Dimen dim);
	Dimen GetNetDim();

    void SetValue(const double v, const Coord index);
	double GetValue(const Coord index);

	string Name(){ return m_name; }

private:
	std::vector<double> m_net;
	Dimen m_dim;
	std::string m_name;
};

class C_Layer
{
public:
    C_Layer();
    explicit C_Layer(const std::string name);
    ~C_Layer();

    //get original members
    //e_LayerType LayerType();
    std::string LayerName();
    std::vector<C_Net> LayerNets();
    std::vector<std::pair<double, std::string>> Param();

    //nets
    C_Net* GetNet(const int i);
    C_Net* GetNet(const string name);
    void PushNet(const Dimen dimen, const string name);
    void SetNetValue(const double v, const Coord index, const string name);

    //parameters
    double GetParam(const std::string name);
    void PushParam(const std::pair<double, std::string>& param);

    //name
    void SetName(const std::string name);

//     //type
//     void SetType(const e_LayerType type);

private:
   // e_LayerType m_type;
    std::string m_name;
    std::vector<C_Net> m_nets;
    std::vector<std::pair<double, std::string>> m_params;
};

//////////////////////////////////////////////////////////////////////////
class C_CNN_Layers
{
public:
	C_CNN_Layers(){}
	~C_CNN_Layers(){}

public:
	int LayersNum();
    void PushLayer(C_Layer layer_i);

    C_CNN_Layers& operator = (C_CNN_Layers obj_i);

public:
    std::vector<C_Layer> layers;
};

#endif