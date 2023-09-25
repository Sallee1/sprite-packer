#include <opencv2/opencv.hpp>
#include <filesystem>
#include "cvMatPacker.h"

namespace fs = std::filesystem;

int main()
{
    //设定控制台的编码为UTF8
    system("chcp 65001");

    //图像拼接器单例
    auto matPacker = cvMatPacker::getInstance();
    /*
    //读取城市图像
    std::vector<cv::Mat> cityImgs;
    fs::path cityRootPath = "citys";
    for (auto iter : fs::directory_iterator(cityRootPath))
    {
        cityImgs.push_back(cv::imread(iter.path().string()));
    }
    //获取图像拼接器的单例，并拼接城市地图

    matPacker->setMats(cityImgs);
    matPacker->pack(2000, 5000);
    */

    //读取洞穴图像
    std::vector<cv::Mat> caveImgs;
    fs::path cavesRootPath = "caves";
    for (auto iter : fs::directory_iterator(cavesRootPath))
    {
        caveImgs.push_back(cv::imread(iter.path().string(), cv::IMREAD_UNCHANGED));
    }
    //拼接洞穴地图
    matPacker->setMats(caveImgs);
    matPacker->setVertical();
    matPacker->pack(10000, 2000);
    return 0;
}