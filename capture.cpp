
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace cv;
using namespace std;

std::string get_tegra_pipeline(int width, int height, int fps, int sensor_id) {
    return "nvcamerasrc sensor-id=(int)" + std::to_string(sensor_id) + "! video/x-raw(memory:NVMM), width=(int)" + std::to_string(width) + ", height=(int)" +
           std::to_string(height) + ", format=(string)I420, framerate=(fraction)" + std::to_string(fps) +
           "/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

int main(int argc, char* arg[])
{
    int id = 0;
    if (argc >= 2)
    {
        std::string num_string = arg[1];
        id = std::stoi(num_string);

        std::cout<<"sensor id = "<<id<<std::endl;
    }
    #if 1
    int WIDTH = 1920;
    int HEIGHT = 1080;
    int FPS = 30;

    // Define the gstream pipeline
    std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS, id);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";

    // Create OpenCV capture object, ensure it works.
    cv::VideoCapture capture(id);
    #else
    VideoCapture capture(id);
    #endif
    Mat frame;
    if (capture.isOpened()) // 判断视频是否成功打开

    {
        while (capture.grab())
        {
            capture >> frame;

            std::cout << "input image size = [" << frame.cols << ", " << frame.rows << "]" << std::endl;

            imshow("读取视频", frame); // 显示当前帧
            waitKey(50);
        }
    }
    waitKey();

    return 0;
}