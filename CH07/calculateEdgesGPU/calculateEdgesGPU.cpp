#include "opencv2/opencv.hpp"
#include "opencv2/core/ocl.hpp"

#include "measurement.h"

using namespace std;
using namespace cv;
using namespace cv::ocl;

int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        cout << "./calculateEdgesGPU <image>" << endl;
        return -1;
    }

    setUseOpenCL(true);

    Mat cpuFrame = imread(argv[1]);
    UMat gpuFrame, gpuBW, gpuBlur, gpuEdges;
 
    cpuFrame.copyTo(gpuFrame);

    namedWindow("Canny Edges GPU",1);

    auto duration = measure_execution([&gpuFrame, &gpuBW, &gpuBlur, &gpuEdges] {
        cvtColor(gpuFrame, gpuBW, COLOR_BGR2GRAY);
        GaussianBlur(gpuBW, gpuBlur, Size(1,1), 1.5, 1.5);
        Canny(gpuBlur, gpuEdges, 50, 100, 3);
    });

    cout << "Computation on GPU " << std::chrono::duration_cast<std::chrono::milliseconds>(duration) << endl;

    imshow("Canny Edges GPU", gpuEdges);
    waitKey();

    return 0;
}

