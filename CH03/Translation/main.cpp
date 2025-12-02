
#include "opencv2/opencv.hpp"

using namespace cv;

int main( int argc, char** argv )
{
    // Read the source file
    Mat src;
    src = imread(argv[1]);

    // Apply translation
    Mat dst;
    Mat M = (Mat_<double>(2,3) << 1, 0, 200, 0, 1, 150);
    warpAffine(src,dst,M,src.size());

    // Show the results
    namedWindow( " ORIGINAL ", WINDOW_AUTOSIZE );
    imshow( " ORIGINAL ", src );
    namedWindow( " TRANSLATED ", WINDOW_AUTOSIZE );
    imshow( " TRANSLATED ", dst );

    waitKey();
    return 0;
}
