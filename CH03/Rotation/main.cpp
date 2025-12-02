#include "opencv2/opencv.hpp"

using namespace cv;

int main( int argc, char** argv )
{
    // Read the source file
    Mat src;
    src = imread(argv[1]);

    // Apply the rotation
    Mat dst;
    Mat M = getRotationMatrix2D(Point2f(src.cols/2,src.rows/2),45,1);
    warpAffine(src,dst,M,src.size());

    // Show the results
    namedWindow( " ORIGINAL ", WINDOW_AUTOSIZE );
    imshow( " ORIGINAL ", src );
    namedWindow( " ROTATED ", WINDOW_AUTOSIZE );
    imshow( " ROTATED ", dst );

    waitKey();
    return 0;
}
