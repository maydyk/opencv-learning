#include "opencv2/opencv.hpp"

#include "measurement.h"

using namespace std;
using namespace cv;

int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        cout << "./calculateEdgesCPU <image>" << endl;
        return -1;
    }

    Mat cpuFrame = imread(argv[1]);
    Mat cpuBW, cpuBlur, cpuEdges;

    namedWindow("Canny Edges CPU",1);

    auto duration = measure_execution([&cpuFrame, &cpuBW, &cpuBlur, &cpuEdges] {
        cvtColor(cpuFrame, cpuBW, COLOR_BGR2GRAY);
        GaussianBlur(cpuBW, cpuBlur, Size(1,1), 1.5, 1.5);
        Canny(cpuBlur, cpuEdges, 50, 100, 3);
    });

    cout << "Computation on CPU " << std::chrono::duration_cast<std::chrono::milliseconds>(duration) << endl;

    imshow("Canny Edges CPU", cpuEdges);
    waitKey();

    return 0;
}

