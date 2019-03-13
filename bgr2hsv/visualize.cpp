#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <chrono>

int main(int argc, char *argv[])
{
    cv::Mat img(1080, 3888, CV_8UC3, cv::Scalar(0));
    if (argc > 1)
    {
        img = cv::imread(argv[1]);
    }
    cv::Mat mat = img.clone();
    cv::namedWindow("Display", CV_WINDOW_NORMAL);
    for(int frame = 0; ; frame++)
    {
        auto start = std::chrono::system_clock::now();
        double ss = std::chrono::duration<double>(start.time_since_epoch()).count();
        {
            double a = ss / M_PI * 0.4;
            double sin_a = sin(a);
            double cos_a = cos(a);
            cv::Size s = mat.size();
            cv::Point rp(s.width * (0.5 - 0.3 * sin_a), s.height * (0.5 - 0.3 * cos_a));
            cv::circle(mat, rp, 15, cv::Scalar(0, 0, 255), -1);

            cv::Point gp(s.width * (0.5 - 0.2 * cos_a), s.height * (0.5 - 0.2 * sin_a));
            cv::circle(mat, gp, 25, cv::Scalar(0, 255, 0), -1);

            cv::Point bp(s.width * (0.5 - 0.45 * cos_a), s.height * (0.5));
            cv::circle(mat, bp, 30, cv::Scalar(255, 0, 0), -1);

            cv::Point wp(s.width * (0.5), s.height * (0.5 - 0.45 * sin_a));
            cv::circle(mat, wp, 30, cv::Scalar(255, 255, 255), -1);

            cv::imshow("Display", mat);
            mat = img.clone();
        }
        auto end = std::chrono::system_clock::now();
        double ee = std::chrono::duration<double>(end.time_since_epoch()).count();
        std::cout.precision(17);
        std::cout << "[" << frame << "]\t[" <<  ee << "]\t[" << ss << "]\t[" << ee - ss << "]" << std::endl;
        
        if (cv::waitKey(1) == 'q')
        {
            break;
        }
    }

    return 0;
}