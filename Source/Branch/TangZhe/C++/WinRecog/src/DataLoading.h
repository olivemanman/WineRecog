#ifndef _DATA_LOADING_
#define _DATA_LOADING_

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <memory>

#include "Common.h"

#define DATA_TYPE double

using namespace std;

class C_Data
{
public:
	C_Data(){}
	C_Data(shared_ptr<DATA_TYPE> data_i, const int width, const int height)
	{
		m_data = data_i;
		m_size.x = width;
		m_size.y = height;
	};

	~C_Data(){};

public:
	shared_ptr<DATA_TYPE> m_data;
	Size2D m_size;
};

class C_DataList
{
public:
	C_DataList();
	~C_DataList();

	void PushBack(std::pair<C_Data, int>& data_i);
	C_Data AtImage(const int i);
	shared_ptr<DATA_TYPE> AtImagePtr(const int i);
	int Label(const int i);
	int GetTotalLabel();
	void SetTotalLabel(const int n);
    int ImageNum();

    C_DataList GetSubData(const std::vector<int>& index);

private:
	std::vector<std::pair<C_Data, int>> m_grayImages;
	int m_totalLabel;
};

class C_DataLoading
{
public:
    C_DataLoading();
    ~C_DataLoading();

    static void Loading(
		C_DataList& grayImages_o,
        string folderPath_i,
        const int resizedWidth_i, const int resizedHeight_i);

	static void getFiles(std::vector<std::pair<string, int>>& files_o, int& totalLabel_o, string path_i);

    static void BatchGrayResize(
		C_DataList& grayImages_o,
        std::vector<std::pair<string, int>>& files_i,
        const int resizedWidth_i, const int resizedHeight_i);

private:
    static int ReadLn(FILE *inFile, char* pBuf, const int nBufLen);

	static int ReadLabeltxt(const string curName, int& totalLabel);

    static int FindLabeltxt(const string targetName, struct _finddata_t fileinfo,
		const string path_i, int& totalLabel);
};

#endif