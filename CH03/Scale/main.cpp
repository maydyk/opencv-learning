
#include "opencv2/opencv.hpp"

using namespace cv;

int main( int argc, char** argv )
{
    // Read the source file
    Mat src;
    src = imread(argv[1]);

    // Apply the scale
    Mat dst;
    resize(src, dst, Size(0,0), 0.5, 0.5);

    // Show the results
    namedWindow( " ORIGINAL ", WINDOW_AUTOSIZE );
    imshow( " ORIGINAL ", src );
    namedWindow( " SCALED ", WINDOW_AUTOSIZE );
    imshow( " SCALED ", dst );

    waitKey();
    return 0;
}
