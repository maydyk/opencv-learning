#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/videostab.hpp>


using namespace std;
using namespace cv;
using namespace cv::videostab;

// Work around deleted GoodFeaturesToTrackDetector 
typedef GFTTDetector GoodFeaturesToTrackDetector;

void processing(Ptr<IFrameSource> stabilizedFrames, string outputPath);

int main(int argc, const char **argv)
{
    Ptr<IFrameSource> stabilizedFrames;
    try
    {
        // 1-Prepare the input video and check it
        string inputPath;
        string outputPath;
        if (argc > 1)
            inputPath = argv[1];
        else
            inputPath = "cube4.avi";

        if (argc > 2)
            outputPath = argv[2];
        else
            outputPath = "cube4_stabilized.avi";

        Ptr<VideoFileSource> source = makePtr<VideoFileSource>(inputPath);
        cout << "frame count (rough): " << source->count() << endl;


        // 2-Prepare the motion estimator
        // first, prepare the motion the estimation builder, RANSAC L2
        double min_inlier_ratio = 0.1;
        Ptr<MotionEstimatorRansacL2> est = makePtr<MotionEstimatorRansacL2>(MM_AFFINE);
        RansacParams ransac = est->ransacParams();
        ransac.size = 3;
        ransac.thresh = 5;
        ransac.eps = 0.5;
        est->setRansacParams(ransac);
        est->setMinInlierRatio(min_inlier_ratio);

        // second, create a feature detector
        int nkps = 1000;
        Ptr<GoodFeaturesToTrackDetector> feature_detector = GoodFeaturesToTrackDetector::create(nkps);

        // third, create the motion estimator
        Ptr<KeypointBasedMotionEstimator> motionEstBuilder = makePtr<KeypointBasedMotionEstimator>(est);
        motionEstBuilder->setDetector(feature_detector);
        Ptr<IOutlierRejector> outlierRejector = makePtr<NullOutlierRejector>();
        motionEstBuilder->setOutlierRejector(outlierRejector);


        // 3-Prepare the stabilizer
        StabilizerBase *stabilizer = 0;

        // first, prepare the one or two pass stabilizer
        bool isTwoPass = 1;
        int radius_pass = 15;
        if (isTwoPass)
        {
            // with a two pass stabilizer
            bool est_trim = true;

            TwoPassStabilizer *twoPassStabilizer = new TwoPassStabilizer();
            twoPassStabilizer->setEstimateTrimRatio(est_trim);
            twoPassStabilizer->setMotionStabilizer(makePtr<GaussianMotionFilter>(radius_pass));

            stabilizer = twoPassStabilizer;
        }
        else
        {
            // with an one pass stabilizer
            OnePassStabilizer *onePassStabilizer = new OnePassStabilizer();
            onePassStabilizer->setMotionFilter(makePtr<GaussianMotionFilter>(radius_pass));

            stabilizer = onePassStabilizer;
        }

        // second, set up the parameters
        int radius = 15;
        double trim_ratio = 0.1;
        bool incl_constr = false;
        stabilizer->setFrameSource(source);
        stabilizer->setMotionEstimator(motionEstBuilder);
        stabilizer->setRadius(radius);
        stabilizer->setTrimRatio(trim_ratio);
        stabilizer->setCorrectionForInclusion(incl_constr);
        stabilizer->setBorderMode(BORDER_REPLICATE);


        // cast stabilizer to simple frame source interface to read stabilized frames
        stabilizedFrames.reset(dynamic_cast<IFrameSource*>(stabilizer));


        // 4-Processing the stabilized frames. The results are showed and saved.
        processing(stabilizedFrames, outputPath);
    }
    catch (const exception &e)
    {
        cout << "error: " << e.what() << endl;
        stabilizedFrames.release();
        return -1;
    }
    stabilizedFrames.release();
    return 0;
}


void processing(Ptr<IFrameSource> stabilizedFrames, string outputPath)
{
    VideoWriter writer;
    Mat stabilizedFrame;
    int nframes = 0;
    double outputFps = 25;

    // for each stabilized frame
    while (!(stabilizedFrame = stabilizedFrames->nextFrame()).empty())
    {
        nframes++;

        // init writer (once) and save stabilized frame
        if (!outputPath.empty())
        {
            if (!writer.isOpened())
                writer.open(outputPath, VideoWriter::fourcc('X','V','I','D'),
                            outputFps, stabilizedFrame.size());
            writer << stabilizedFrame;
        }

        imshow("stabilizedFrame", stabilizedFrame);
        char key = static_cast<char>(waitKey(3));
        if (key == 27)
        {
            cout << endl;
            break;
        }

    }
    cout << "processed frames: " << nframes << endl;
    cout << "finished " << endl;
}
