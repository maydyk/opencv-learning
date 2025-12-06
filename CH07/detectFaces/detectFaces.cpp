#include "opencv2/core/core.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
using namespace cv::ocl;

int main(int argc, char * argv[])
{
    // 1- Set the initial parameters
    // Vector to store the faces
    vector<Rect> faces;
    CascadeClassifier face_cascade;
    String face_cascade_name = "haarcascade_frontalface_alt.xml";
    int face_size = 30;
    double scale_factor = 1.1;
    int min_neighbours = 2;

    // 2- Load the file xml to use the classifier
    if (!face_cascade.load(face_cascade_name))
    {
        cout << "Cannot load the face xml!" << endl;
        return -1;
    }

    namedWindow("Video Capture");

    // 3- Select between the CPU or GPU processing
    const char* fileName = nullptr;
    if (argc < 2)
    {
        cout << "./detectFaces [CPU/GPU | C/G]" << endl;
        cout << "Trying to use GPU..." << endl;
        setUseOpenCL(true);
    }
    else
    {
        cout << "./detectFaces trying to use " << argv[1] << endl;
        if(argv[1][0] == 'C')
            // Trying to use the CPU processing
            setUseOpenCL(false);
        else
            // Trying to use the GPU processing
            setUseOpenCL(true);

        fileName = argv[2];
    }

    Ptr<VideoCapture> cap;
    UMat frame, frameGray;
    bool finish = false;

    if (fileName) {
        cap = new VideoCapture(fileName);
    } else {
        cap = new VideoCapture(0);
    }

    if (!cap->isOpened()) {
        cout << "Cannot open the camera or file." << endl;
        return -1;
    }



    Rect r;
    double start_time, finish_time, start_total_time, finish_total_time;
    int counter = 0;


    // 4- Detect the faces for each image capture
    start_total_time = getTickCount();
    while (!finish)
    {
        start_time = getTickCount();
        *cap >> frame;
        if (frame.empty())
        {
            cout << "No capture frame --> finish" << endl;
            break;
        }

        cvtColor(frame, frameGray, COLOR_BGR2GRAY);
        equalizeHist(frameGray,frameGray);

        // Detect the faces
        face_cascade.detectMultiScale(frameGray, faces, scale_factor, min_neighbours, 0|CASCADE_SCALE_IMAGE, Size(face_size,face_size));

        // For each detected face
        for (int f = 0; f < faces.size(); f++)
        {
            r = faces[f];
            // Draw a rectangle over the face
            rectangle(frame, Point(r.x, r.y), Point(r.x + r.width, r.y + r.height), Scalar(0,255,0), 3);
        }

        // Show the results
        imshow("Video Capture",frame);

        // Calculate the time processing
        finish_time = getTickCount();
        cout << "Time per frame: " << (finish_time - start_time)/getTickFrequency() << " secs" << endl;

        counter++;



        // Press Esc key to finish
        if(waitKey(1) == 27) finish = true;
    }

    finish_total_time = getTickCount();
    cout << "Average time per frame: " << ((finish_total_time - start_total_time)/getTickFrequency())/counter << " secs" << endl;

    return 0;
}

