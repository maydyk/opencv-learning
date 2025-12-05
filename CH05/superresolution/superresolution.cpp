#include <iostream>
#include <iomanip>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/superres.hpp"
#include "opencv2/superres/optical_flow.hpp"
#include "opencv2/opencv_modules.hpp"

using namespace std;
using namespace cv;
using namespace cv::superres;

static Ptr<DenseOpticalFlowExt> createOptFlow(string name);


int main(int argc, char *argv[])
{
    // 1-Initialize the initial parameters

    // Input and output video
    string inputVideoName;
    string outputVideoName;
    if (argc > 1)
        inputVideoName = argv[1];
    else
        inputVideoName = "tree.avi";

    if (argc > 2)
        outputVideoName = argv[2];
    else
        outputVideoName = "tree_superresolution.avi";

    // Scale factor
    const int scale = 4;

    // Iterations count
    const int iterations = 180;

    // Radius of the temporal search area
    const int temporalAreaRadius =4;

    // Optical flow algorithm
    string optFlow = "farneback";
       // optFlow = "farneback";
       // optFlow = "tvl1";
       // optFlow = "brox";
       // optFlow = "pyrlk";

    // Playback speed ouput
    double outputFps = 25.0;


    // 2- Create an optical flow method
    Ptr<DenseOpticalFlowExt> optical_flow = createOptFlow(optFlow);

    if (optical_flow.empty())
        return -1;


    // 3- Create the superresolution method and set its parameters
    Ptr<SuperResolution> superRes;
    superRes = createSuperResolution_BTVL1();

    superRes->setOpticalFlow(optical_flow);
    superRes->setScale(scale);
    superRes->setIterations(iterations);
    superRes->setTemporalAreaRadius(temporalAreaRadius);

    Ptr<FrameSource> frameSource;
    frameSource = createFrameSource_Video(inputVideoName);

    superRes->setInput(frameSource);

    // Not use the first frame
    Mat frame;
    frameSource->nextFrame(frame);


    // 4- Processing the input video with the superresolution
    // Show the initial options
    cout << "Input                  : " << inputVideoName << " " << frame.size() << endl;
    cout << "Output                 : " << outputVideoName << endl;
    cout << "Playback speed output  : " << outputFps << endl;
    cout << "Scale factor           : " << scale << endl;
    cout << "Iterations             : " << iterations << endl;
    cout << "Temporal radius        : " << temporalAreaRadius << endl;
    cout << "Optical Flow           : " << optFlow << endl;
    cout << endl;

    VideoWriter writer;
    double start_time,finish_time;

    for (int i = 0;; ++i)
    {
        cout << '[' << setw(3) << i << "] : ";
        Mat result;

        // Calculate the processing time
        start_time = getTickCount();
        superRes->nextFrame(result);
        finish_time = getTickCount();
        cout << (finish_time - start_time)/getTickFrequency() << " secs, Size: " << result.size() << endl;

        if (result.empty())
            break;

        // Show the result
        imshow("Super Resolution", result);

        if (waitKey(1000) > 0)
            break;

        // Save the result on output file
        if (!outputVideoName.empty())
        {
            if (!writer.isOpened())
                writer.open(outputVideoName, VideoWriter::fourcc('X', 'V', 'I', 'D'), outputFps, result.size());
            writer << result;
        }
    }
    writer.release();

    return 0;
}

static Ptr<DenseOpticalFlowExt> createOptFlow(string name)
{
    if (name == "farneback")
       return createOptFlow_Farneback();

    else if (name == "tvl1")
        return createOptFlow_DualTVL1();

    else if (name == "brox")
        return createOptFlow_Brox_CUDA();

    else if (name == "pyrlk")
        return createOptFlow_PyrLK_CUDA();

    else
        cerr << "Incorrect Optical Flow algorithm - " << name << endl;

    return Ptr<DenseOpticalFlowExt>();
}
