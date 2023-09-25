#pragma once
#include <opencv2/opencv.hpp>
#include "CBlockLayout.h"

class cvMatPacker
{
private:
    cvMatPacker() {};
    static cvMatPacker* instance;
    //输入的图像矩阵列表
    std::vector<cv::Mat> m_aMats;
    //拼接后的rect列表
    std::vector<cv::Rect2i> m_aRects;
    //拼接后的图像
    cv::Mat m_output;
    //树的生长方向
    bool isVertical = false;



public:
    static cvMatPacker* getInstance();

    void setHorizontal();   //设置树的生长方向为水平
    void setVertical();     //设置树的生长方向为垂直
    void setMats(std::vector<cv::Mat> mats);

    cv::Mat pack(int width, int height);
    cv::Mat __pack(int width, int height);
};