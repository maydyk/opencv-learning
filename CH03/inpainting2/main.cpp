
#include "opencv2/opencv.hpp"

using namespace cv;

int main( int argc, char** argv )
{
    // Read the source file
    Mat src;
    src = imread(argv[1]);

    // Create the mask
    Mat mask;
    cvtColor(src, mask, COLOR_RGB2GRAY);
    threshold(mask, mask, 235, 255, THRESH_BINARY);

    // Apply the inpainting algorithms
    Mat dst, dst2;
    inpaint(src, mask, dst, 10, INPAINT_TELEA);
    inpaint(src, mask, dst2, 10, INPAINT_NS);

    // Show the results
    namedWindow( " ORIGINAL ", WINDOW_AUTOSIZE );
    imshow( " ORIGINAL ", src );
    namedWindow( " MASK ", WINDOW_AUTOSIZE );
    imshow( " MASK ", mask );
    namedWindow(" INPAINT_TELEA ", WINDOW_AUTOSIZE );
    imshow( " INPAINT_TELEA ", dst );
    namedWindow(" INPAINT_NS ", WINDOW_AUTOSIZE );
    imshow( " INPAINT_NS ", dst2 );

    waitKey();
    return 0;
}
