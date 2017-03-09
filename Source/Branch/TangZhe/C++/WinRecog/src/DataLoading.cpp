#include "DataLoading.h"
#include "RGBConvertor.h"
#include "ImageOperation.h"
#include <opencv2\highgui\highgui.hpp>

C_DataList::C_DataList()
{
	m_totalLabel = 0;
}

C_DataList::~C_DataList()
{

}

void C_DataList::PushBack(std::pair<C_Data, int>& data_i)
{
	m_grayImages.push_back(data_i);
}

C_Data C_DataList::AtImage(const int i)
{
	return m_grayImages.at(i).first;
}

shared_ptr<DATA_TYPE> C_DataList::AtImagePtr(const int i)
{
	return m_grayImages.at(i).first.m_data;
}

int C_DataList::Label(const int i)
{
	return m_grayImages.at(i).second;
}

int C_DataList::GetTotalLabel()
{
	return m_totalLabel;
}

void C_DataList::SetTotalLabel(const int n)
{
	m_totalLabel = n;
}
int C_DataList::ImageNum()
{
    return static_cast<int>(m_grayImages.size());
}

C_DataList C_DataList::GetSubData(const std::vector<int>& index)
{
    C_DataList data_o;
    data_o.SetTotalLabel(this->m_totalLabel);

    for (int i = 0; i < index.size(); i++)
    {
        data_o.PushBack(this->m_grayImages.at(index.at(i)));
    }
    return data_o;
}

C_DataLoading::C_DataLoading()
{
}

C_DataLoading::~C_DataLoading()
{
}

void C_DataLoading::Loading(
	C_DataList& grayImages_o,
    string folderPath_i,
    const int resizedWidth_i, const int resizedHeight_i)
{
    std::vector<std::pair<string, int>> files;
	int totalLabel_o = 0;
    C_DataLoading::getFiles(files, totalLabel_o, folderPath_i);

    //output images
    C_DataLoading::BatchGrayResize(grayImages_o, files, resizedWidth_i, resizedHeight_i);
	grayImages_o.SetTotalLabel(totalLabel_o);
}

void C_DataLoading::getFiles(std::vector<std::pair<string, int>>& files_o, int& totalLabel_o, string path_i)
{
    //handle
    intptr_t hFile = 0;
    //information
    struct _finddata_t fileinfo;
    string p;
    bool bChnageFolder = true;
    if ((hFile = _findfirst(p.assign(path_i).append("\\*").c_str(), &fileinfo)) != -1)
    {
        int label = -1;
		totalLabel_o = 0;
        do
        {
            //if still has sub folder, continue
            //else, add to vector
            if ((fileinfo.attrib &  _A_SUBDIR))
            {
                label = -1;
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
					getFiles(files_o, totalLabel_o, p.assign(path_i).append("\\").append(fileinfo.name));
                }
            }
            else
            {
                string labelName = p.assign(path_i).append("\\").append("label.txt");
                if (bChnageFolder == true)
                {
                    //find label.txt
					label = FindLabeltxt(labelName, fileinfo, path_i, totalLabel_o);
                }

                string tmpName = p.assign(path_i).append("\\").append(fileinfo.name);

                if (labelName.compare(tmpName) != 0)
                {
                    files_o.push_back(std::make_pair(tmpName, label));
                }
                bChnageFolder = false;
            }
        }
        while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

void C_DataLoading::BatchGrayResize(
	C_DataList& grayImages_o,
    std::vector<std::pair<string, int>>& files_i,
    const int resizedWidth_i, const int resizedHeight_i)
{
    size_t num = files_i.size();

    int sizeX = 0;
    int sizeY = 0;

    bool bResize = false;
    if (resizedWidth_i > 0 && resizedHeight_i > 0)
    {
        sizeX = resizedWidth_i;
        sizeY = resizedHeight_i;
        bResize = true;
    }

#pragma omp parallel for
    for (int i = 0; i < num; i++)
    {
        std::cout << "read image " << i << std::endl;
        IplImage *img = cvLoadImage(files_i[i].first.c_str(), 1);

        if (bResize)
        {
            sizeX = resizedWidth_i;
            sizeY = resizedHeight_i;
        }
        else
        {
            sizeX = img->width;
            sizeY = img->height;
        }

        shared_ptr<double> grayImg(new double[sizeX * sizeY]);

        if (bResize)
        {
            shared_ptr<char> imgOut(new char[sizeX * sizeY * 3]);
            int sizeOut[2] = { sizeX, sizeY };
            int sizeIn[2] = { img->width, img->height };
            C_ImageOperation::DataResizeRGB2D(imgOut.get(), img->imageData, sizeOut, sizeIn);
            C_RGB_CONVERTOR::RGB2GrayMatlab(grayImg.get(), sizeX * sizeY, imgOut.get());
        }
        else
        {
            C_RGB_CONVERTOR::RGB2GrayMatlab(grayImg.get(), sizeX * sizeY, img->imageData);
        }

        for (int j = 0; j < sizeX * sizeY; j++)
        {
            grayImg.get()[j] = (grayImg.get()[j] / 255.0);
        }

		C_Data grayData(grayImg, sizeX, sizeY);
		std::pair<C_Data, int> pushData = std::make_pair(grayData, files_i.at(i).second);
		grayImages_o.PushBack(pushData);

//         {
//             FILE* fp = nullptr;
//             fopen_s(&fp, "D:\\test.raw", "wb+");
//             if (fp)
//             {
//                 fwrite(grayImg.get(), sizeof(double), sizeOut[0] * sizeOut[1], fp);
//                 fclose(fp);
//                 fp = nullptr;
//             }
//         }
    }
    return;
}

int C_DataLoading::ReadLn(FILE *inFile, char* pBuf, const int nBufLen)
{
    char    cIn = '\0';
    int        nPos = 0;
    size_t    nRead = 0;

    while ((nPos < nBufLen) && ((nRead = fread(&cIn, 1, sizeof(char), inFile)) == 1))
    {
        pBuf[nPos++] = cIn;
        if (cIn == '\n') break;
    }
    pBuf[nPos] = 0;
    return nPos;
}

int C_DataLoading::ReadLabeltxt(const string curName, int& totalLabel)
{
    int labelValueCount = 1;
	totalLabel = 0;
    errno_t err;
    FILE* fp = NULL;
	bool bAdd = true;
    if ((err = fopen_s(&fp, curName.c_str(), "rb+")) == 0)
	{
		char szLnBuf[1024];
		bool bEof = false;
        while (!bEof)
        {
            if (ReadLn(fp, szLnBuf, 1024) <= 0)
            {
                fclose(fp);
				return labelValueCount;
			}

            int labelValue = 0;
            sscanf_s(szLnBuf, "%d\n", &labelValue);
			totalLabel++;

            if (labelValue == 1)
            {
				bAdd = true;
                //return labelValueCount;
            }
			else if (bAdd == false)
            {
                labelValueCount++;
            }
        }
    }

    return labelValueCount;
}

int C_DataLoading::FindLabeltxt(
	const string targetName, struct _finddata_t fileinfo, const string path_i, int& totalLabel)
{
    int label = 0;
    string p;
    intptr_t hFileTmp = _findfirst(p.assign(path_i).append("\\*").c_str(), &fileinfo);
    //search in the folder
    {
        struct _finddata_t tmpFileInfo = fileinfo;
        do
        {
            string curName = p.assign(path_i).append("\\").append(tmpFileInfo.name);
            if (curName.compare(targetName) == 0)
            {
                label = ReadLabeltxt(curName, totalLabel);
                return label;
            }
        }
        while (_findnext(hFileTmp, &tmpFileInfo) == 0);
    }
    return -1;
}
