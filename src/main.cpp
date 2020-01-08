#include <iostream>
#include <opencv2/opencv.hpp>

#include "image_enhancement.h"

void MyTimeOutput(const std::string& str, const clock_t& start_time, const clock_t& end_time)
{
    std::cout << str << (double)(end_time - start_time) / CLOCKS_PER_SEC << "s" << std::endl;
    return;
}

void MyTimeOutput(const std::string& str, const clock_t& time)
{
    std::cout << str << (double)(time) / CLOCKS_PER_SEC << "s" << std::endl;
    return;
}


int main(int argc, char** argv)
{
    cv::Mat src = cv::imread(argv[1], 1);

    if (src.empty()) {
        std::cout << "Can't read image file." << std::endl;
        return -1;
    }

    clock_t start_time, end_time;

    start_time = clock();
    cv::Mat LDR_dst;
    LDR(src, LDR_dst);
    end_time = clock();
    MyTimeOutput("LDR处理时间: ", start_time, end_time);

    start_time = clock();
    cv::Mat Ying_dst;
    Ying_2017_CAIP(src, Ying_dst);
    end_time = clock();
    MyTimeOutput("Ying处理时间: ", start_time, end_time);

    start_time = clock();
    cv::Mat CEusingLuminanceAdaptation_dst;
    CEusingLuminanceAdaptation(src, CEusingLuminanceAdaptation_dst);
    end_time = clock();
    MyTimeOutput("CEusingLuminanceAdaptation处理时间: ", start_time, end_time);

    start_time = clock();
    cv::Mat adaptiveImageEnhancement_dst;
    adaptiveImageEnhancement(src, adaptiveImageEnhancement_dst);
    end_time = clock();
    MyTimeOutput("adaptiveImageEnhancement处理时间: ", start_time, end_time);   

    cv::imshow("src", src);
    cv::imshow("LDR_dst", LDR_dst);
    cv::imshow("Ying_dst", Ying_dst);
    cv::imshow("CEusingLuminanceAdaptation_dst", CEusingLuminanceAdaptation_dst);
    cv::imshow("adaptiveImageEnhancement_dst", adaptiveImageEnhancement_dst);
	
    cv::waitKey();
    return 0;
}