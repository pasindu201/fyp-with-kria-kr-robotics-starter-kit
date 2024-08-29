#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<opencv2/core/core.hpp>
#include<opencv2/videoio.hpp>

#include<System.h>

using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cerr << endl << "Usage: ./mono_phone path_to_vocabulary path_to_settings" << endl;
        return 1;
    }

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR,true);
    float imageScale = SLAM.GetImageScale();

    // Open the video stream
    cv::VideoCapture cap("http://192.168.1.137:8080/video");
    if (!cap.isOpened()) {
        cerr << "Error opening video stream" << endl;
        return -1;
    }

    // Main loop
    cv::Mat im;
    int frame_count = 0;
    double t_start = (double)cv::getTickCount();

    while(true)
    {
        // Read new frame
        cap >> im;
        if(im.empty())
            break;

        frame_count++;
        double tframe = ((double)cv::getTickCount() - t_start)/cv::getTickFrequency();

        if(imageScale != 1.f)
        {
            int width = im.cols * imageScale;
            int height = im.rows * imageScale;
            cv::resize(im, im, cv::Size(width, height));
        }

        // Pass the image to the SLAM system
        SLAM.TrackMonocular(im,tframe);

        // Wait to load the next frame (to simulate the same frame rate as the dataset)
        usleep(33000);  // Assumes 30 fps, adjust if needed
    }

    // Stop all threads
    SLAM.Shutdown();

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");

    return 0;
}