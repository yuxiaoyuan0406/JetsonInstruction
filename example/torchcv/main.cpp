#include <iostream>
#include <memory>
#include <string>
// #include <stdio.h>
// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
// torch
#include <torch/torch.h>
#include <torch/script.h>

// using namespace std;
// using namespace cv;

std::string gstreamer_pipeline(int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method)
{
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

int main()
{
    int capture_width = 1280;
    int capture_height = 720;
    int display_width = 1280;
    int display_height = 720;
    int framerate = 60;
    int flip_method = 0;

    std::string pipeline = gstreamer_pipeline(capture_width,
                                              capture_height,
                                              display_width,
                                              display_height,
                                              framerate,
                                              flip_method);
    std::cout << "Using pipeline: \n\t" << pipeline << std::endl;

    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened())
    {
        std::cerr << "ERROR: Cannot initialize camera capture" << std::endl;
        return 1;
    }

    cv::namedWindow("CSI Camera", cv::WINDOW_AUTOSIZE);
    cv::Mat img;

    std::cout << "Hit esc to exit" << std::endl;
    while (true)
    {
        if (!cap.read(img))
        {
            std::cerr << "ERROR: Capture read error" << std::endl;
            break;
        }

        cv::imshow("CSI Camera", img);
        int keycode = cv::waitKey(30) & 0xff;
        if (keycode == 27)
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
