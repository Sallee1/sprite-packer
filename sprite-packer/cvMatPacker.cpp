#include "cvMatPacker.h"
cvMatPacker* cvMatPacker::instance = nullptr;


void cvMatPacker::setHorizontal()
{
    isVertical = false;
}

void cvMatPacker::setVertical()
{
    isVertical = true;
}

cvMatPacker* cvMatPacker::getInstance()
{
    if (instance == nullptr)
        instance = new cvMatPacker;
    return instance;
}

void cvMatPacker::setMats(std::vector<cv::Mat> mats)
{
    m_aMats = mats;
}

cv::Mat cvMatPacker::pack(int width, int height)
{
    if (!isVertical)
        return __pack(width, height);
    //垂直模式，稍微变通一下
    else
    {
        for (auto& mat : m_aMats)
        {
            cv::flip(mat, mat, 1);
            cv::rotate(mat, mat, cv::ROTATE_90_COUNTERCLOCKWISE);
        }
        __pack(height, width);
        auto res = m_output;
        cv::rotate(res, res, cv::ROTATE_90_CLOCKWISE);
        cv::flip(res, res, 1);
        return res;
    }
}

cv::Mat cvMatPacker::__pack(int width, int height)
{
    //构造输入格式
    std::vector <std::vector<int>> input_param;
    for (int i = 0; i < m_aMats.size(); i++)
    {
        input_param.emplace_back(std::vector<int>{m_aMats[i].cols, m_aMats[i].rows, i});
    }
    //调用CBlockLayout类拼接
    CBlockLayout layout;

    layout.Rank(input_param);
    layout.Fit(width, height, input_param);

    //显示拼接结果
    m_output = cv::Mat::zeros(height, width, CV_8UC4);
    for (int i = 0; i < m_aMats.size(); i++)
    {
        int xPos = layout.getX(i);
        int yPos = layout.getY(i);
        if (xPos < 0)continue;
        cv::Mat mat = m_aMats[i];
        mat.copyTo(m_output(cv::Rect(xPos, yPos, mat.cols, mat.rows)));
    }
    //cv::imshow("res", res);
    return m_output;
}
