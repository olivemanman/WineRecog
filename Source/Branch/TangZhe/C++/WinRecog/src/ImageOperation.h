#ifndef _IMAGE_OPERATION_H_
#define _IMAGE_OPERATION_H_

class C_ImageOperation
{
public:
    C_ImageOperation() {}
    ~C_ImageOperation() {}

public:
    template<class T>
    static void DataResizeRGB2D(T* data_o, T* data_i, const int* sizeOut, const int* sizeIn);
};

//Implementation
template<class T>
void C_ImageOperation::DataResizeRGB2D(T* data_o, T* data_i, const int* sizeOut, const int* sizeIn)
{
    if (!data_i || !sizeOut || !sizeIn)
    {
        throw("wrong in data resize");
    }

    if (!data_o)
    {
        //data_o = shared_ptr<T>(new T(sizeOut[0] * sizeOut[1]));
		T nsize = static_cast<T>(sizeOut[0] * sizeOut[1] * 3);
		data_o = new T(nsize);
    }

    //resize
    int boundaryX = sizeIn[0] - 1;
    int boundaryY = sizeIn[1] - 1;

    float scaleX = static_cast<float>(sizeIn[0]) / static_cast<float>(sizeOut[0]);
    float scaleY = static_cast<float>(sizeIn[1]) / static_cast<float>(sizeOut[1]);

#pragma omp parallel for
    for (int y = 0; y < sizeOut[1]; y++)
    {
        for (int x = 0; x < sizeOut[0]; x++)
        {
            int nearestX = min(static_cast<int>(x*scaleX + 0.5f), boundaryX);
            int nearestY = min(static_cast<int>(y*scaleY + 0.5f), boundaryY);

            if (nearestX >= 0 && nearestX <= boundaryX &&
                nearestY >= 0 && nearestY <= boundaryY)
            {
                int index_o = y*sizeOut[0] + x;
                int index_i = nearestY*sizeIn[0] + nearestX;
                data_o[3 * index_o + 0] = data_i[3 * index_i + 0];
                data_o[3 * index_o + 1] = data_i[3 * index_i + 1];
                data_o[3 * index_o + 2] = data_i[3 * index_i + 2];
            }
        }
    }
    return;
}

#endif