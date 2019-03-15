#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <chrono>

const int max_value_H = 360 / 2;
const int max_value = 255;
const cv::String window_capture_name = "Video";
const cv::String window_detection_name = "Object";
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;

static void on_low_H_thresh_trackbar(int, void *)
{
    low_H = std::min(high_H - 1, low_H);
    cv::setTrackbarPos("Low H", window_detection_name, low_H);
}
static void on_high_H_thresh_trackbar(int, void *)
{
    high_H = std::max(high_H, low_H + 1);
    cv::setTrackbarPos("High H", window_detection_name, high_H);
}
static void on_low_S_thresh_trackbar(int, void *)
{
    low_S = std::min(high_S - 1, low_S);
    cv::setTrackbarPos("Low S", window_detection_name, low_S);
}
static void on_high_S_thresh_trackbar(int, void *)
{
    high_S = std::max(high_S, low_S + 1);
    cv::setTrackbarPos("High S", window_detection_name, high_S);
}
static void on_low_V_thresh_trackbar(int, void *)
{
    low_V = std::min(high_V - 1, low_V);
    cv::setTrackbarPos("Low V", window_detection_name, low_V);
}
static void on_high_V_thresh_trackbar(int, void *)
{
    high_V = std::max(high_V, low_V + 1);
    cv::setTrackbarPos("High V", window_detection_name, high_V);
}

int main(int argc, char *argv[])
{
    cv::VideoCapture cap(argc > 1 ? atoi(argv[1]) : 0);
    cv::namedWindow(window_capture_name, cv::WINDOW_NORMAL);
    cv::namedWindow(window_detection_name, cv::WINDOW_NORMAL);
    cv::createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
    cv::createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
    cv::createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
    cv::createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
    cv::createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
    cv::createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
    cv::Mat frame, frame_HSV, frame_threshold;
    //frame = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    while (true)
    {
        cap >> frame;
        if (frame.empty())
        {
            break;
        }

        {
            auto start = std::chrono::system_clock::now();
            double ss = std::chrono::duration<double>(start.time_since_epoch()).count();
            double a = ss / M_PI;
            double sin_a = sin(a);
            double cos_a = cos(a);
            cv::Size s = frame.size();
            cv::Point rp(s.width * (0.5 - 0.3 * sin_a), s.height * (0.5 - 0.3 * cos_a));
            cv::circle(frame, rp, 15, cv::Scalar(0, 0, 255), -1);
            cv::Point gp(s.width * (0.5 - 0.2 * cos_a), s.height * (0.5 - 0.2 * sin_a));
            cv::circle(frame, gp, 25, cv::Scalar(0, 255, 0), -1);
            cv::Point bp(s.width * (0.5 - 0.45 * cos_a), s.height * (0.5));
            cv::circle(frame, bp, 30, cv::Scalar(255, 0, 0), -1);
            cv::Point wp(s.width * (0.5), s.height * (0.5 - 0.45 * sin_a));
            cv::circle(frame, wp, 30, cv::Scalar(255, 255, 255), -1);
            auto end = std::chrono::system_clock::now();
            double ee = std::chrono::duration<double>(end.time_since_epoch()).count();
        }

        cv::cvtColor(frame, frame_HSV, cv::COLOR_BGR2HSV);
        cv::inRange(frame_HSV, cv::Scalar(low_H, low_S, low_V), cv::Scalar(high_H, high_S, high_V), frame_threshold);

        cv::imshow(window_capture_name, frame);
        cv::imshow(window_detection_name, frame_threshold);
        if (cv::waitKey(30) == 'q')
        {
            break;
        }
    }
    return 0;
}