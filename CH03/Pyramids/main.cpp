
#include "opencv2/opencv.hpp"

using namespace cv;

int main( int argc, char** argv )
{
    // Read the source file
    Mat src;
    src = imread("fruits.jpg");

    // Apply two times pyrDown
    Mat dst, dst2;
    pyrDown(src, dst);
    pyrDown(dst, dst2);

    // Show the results
    namedWindow( " ORIGINAL ", WINDOW_AUTOSIZE );
    imshow( " ORIGINAL ", src );
    namedWindow( " 1st PYRDOWN ", WINDOW_AUTOSIZE );
    imshow( " 1st PYRDOWN ", dst );
    namedWindow( " 2st PYRDOWN ", WINDOW_AUTOSIZE );
    imshow( " 2st PYRDOWN ", dst2 );

    // Apply two times pyrUp
    pyrUp(dst2, dst);
    pyrUp(dst, src);

    // Show the results
    namedWindow( " NEW ORIGINAL ", WINDOW_AUTOSIZE );
    imshow( " NEW ORIGINAL ", dst2 );
    namedWindow( " 1st PYRUP ", WINDOW_AUTOSIZE );
    imshow( " 1st PYRUP ", dst );
    namedWindow( " 2st PYRUP ", WINDOW_AUTOSIZE );
    imshow( " 2st PYRUP ", src );

    waitKey();
    return 0;
}
