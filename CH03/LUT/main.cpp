#include "opencv2/opencv.hpp"

using namespace cv;

int main( int argc, char** argv )
{
    // Read the source file
    Mat src;
    src = imread(argv[1]);

    // Create the LUT
    uchar * M = (uchar*)malloc(256*sizeof(uchar));
    for(int i=0; i<256; i++){
        M[i] = i*0.5;
    }
    Mat lut(1, 256, CV_8UC1, M);

    // Apply the LUT
    Mat dst;
    LUT(src,lut,dst);

    // Show the results
    namedWindow( " ORIGINAL ", WINDOW_AUTOSIZE );
    imshow( " ORIGINAL ", src );
    namedWindow( " LUT ", WINDOW_AUTOSIZE );
    imshow( " LUT ", dst );

    waitKey();
    return 0;
}
