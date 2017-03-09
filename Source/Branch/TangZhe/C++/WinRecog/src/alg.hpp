#ifndef _ALG_HPP_
#define _ALG_HPP_

double RandZeroToOne()
{
    return rand() % 100 / (double)101.0;
}

template<typename T>
std::vector<T> Randperm(const int vecSize)
{    
    std::vector<T> vec;
    vec.resize(vecSize);
    int k = vecSize;	//k:未定顺序的元素个数

    for (int i = 0; i < vecSize; i++)
        vec[i] = i + 1;

    for (int i = 0; i < vecSize - 1; i++)
    {
        int j = rand() % k;  //产生0 ~ k-1的随机数j

        T t = vec[j];
        vec[j] = vec[k - 1];
        vec[k - 1] = t;	//将a[j]与“最后一个元素”对换

        k--;
    }

    return vec;
}

template<typename T>
std::vector<T> ComposeVectAccordingToVecIndex(const std::vector<T>& oriVect, std::vector<int>& indexVect)
{
    std::vector<T> vec_o;
    
    for (size_t i = 0; i < indexVect.size(); i++)
    {
        vec_o.push_back(oriVect.at(indexVect.at(i)));
    }
    return vec_o;
}

#endif