#include "CNNLayers.h"

C_Net::C_Net()
{

}

C_Net::C_Net(const std::string name)
{
	m_name = name; 
}

C_Net::C_Net(const Dimen dim, const std::string name)
{
    m_net.resize(dim.GetTotalSize());
    m_dim = dim;
	m_name = name;
}

void C_Net::Push1D(const double v)
{
	m_net.push_back(v);
    int v2 = m_dim.GetValue(0) + 1;
	m_dim.SetValue(0, v2);
}

void C_Net::SetNet(const Dimen dim)
{
    m_net.resize(dim.GetTotalSize());
    m_dim = dim;
}
Dimen C_Net::GetNetDim()
{
	return m_dim;
}

void C_Net::SetValue(const double v, const Coord index)
{
    int dim = static_cast<int>(m_dim.GetDimension());
	int dimenIn = static_cast<int>(index.GetDimension());

	if (dimenIn != dim)
	{
		throw("wrong dim");
	}

	if (dim == 1)
	{
		m_net[index.GetTotalSize()] = v;
		return;
	}

	int tmpIndex = 0;
	for (int i = dimenIn-1; i > 0; i--)
	{
        int dimCount = 1;
        for (int j = i-1; j >= 0; j--)
        {
            dimCount *= m_dim.GetValue(j);
        }
        tmpIndex += index.GetValue(i)*dimCount;
    }
    tmpIndex += index.GetValue(0);

	m_net[tmpIndex] = v;
}

double C_Net::GetValue(const Coord index)
{
	int dim = static_cast<int>(m_dim.GetDimension());
	int tmpIndex = 0;
    for (int i = dim - 1; i > 0; i--)
    {
        int dimCount = 1;
        for (int j = i - 1; j >= 0; j--)
        {
            dimCount *= m_dim.GetValue(j);
        }
        tmpIndex += index.GetValue(i)*dimCount;
    }
    tmpIndex += index.GetValue(0);

	return m_net[tmpIndex];
}

C_Layer::C_Layer()
{

}

C_Layer::C_Layer(const std::string name)
{
    m_name = name;
}

C_Layer::~C_Layer()
{

}

// e_LayerType C_Layer::LayerType()
// {
//     return m_type;
// }

std::string C_Layer::LayerName()
{
    return m_name;
}

std::vector<C_Net> C_Layer::LayerNets()
{
    return m_nets;
}

std::vector<std::pair<double, std::string>> C_Layer::Param()
{
    return m_params;
}

C_Net* C_Layer::GetNet(const int i)
{
    return &m_nets.at(i);
}

C_Net* C_Layer::GetNet(const string name)
{
    for (size_t i = 0; i < m_nets.size(); i++)
    {
        if (m_nets.at(i).Name().compare(name) == 0)
        {
            return &m_nets.at(i);
        }
    }
    return nullptr;
}

void C_Layer::PushNet(const Dimen dimen, const string name)
{
    C_Net net(dimen, name);
    m_nets.push_back(net);
}

void C_Layer::SetNetValue(const double v, const Coord index, const string name)
{
     C_Net* net = this->GetNet(name);
     net->SetValue(v, index);
    //this->m_nets[0].SetValue(v, index);
}

double C_Layer::GetParam(const std::string name)
{
    for (size_t i = 0; i < m_params.size(); i++)
    {
        if (m_params.at(i).second.compare(name) == 0)
        {
            return m_params.at(i).first;
        }
    }

    return -1.0;
}

void C_Layer::PushParam(const std::pair<double, std::string>& param)
{
    m_params.push_back(param);
}

void C_Layer::SetName(const std::string name)
{
    m_name = name;
}

// void C_Layer::SetType(const e_LayerType type)
// {
//     m_type = type;
// }

int C_CNN_Layers::LayersNum()
{
	return static_cast<int>(layers.size());
}

void C_CNN_Layers::PushLayer(C_Layer layer_i)
{
	layers.push_back(layer_i);
}

C_CNN_Layers& C_CNN_Layers::operator = (C_CNN_Layers obj_i)
{
    this->layers = obj_i.layers;
    return *this;
}