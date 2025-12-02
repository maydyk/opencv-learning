
#include "opencv2/opencv.hpp"

using namespace cv;

int main( int argc, char** argv )
{
    // Read the source file
    Mat src;
    src = imread(argv[1]);

    // Apply the reflections
    Mat dsth, dstv, dst;
    Mat Mh  = (Mat_<double>(2,3) << -1, 0, src.cols, 0, 1, 0);//Horizontal
    Mat Mv  = (Mat_<double>(2,3) << 1, 0, 0, 0, -1, src.rows);//Vertical
    Mat M  = (Mat_<double>(2,3) << -1, 0, src.cols, 0, -1, src.rows);//H-V
    warpAffine(src,dsth,Mh,src.size());
    warpAffine(src,dstv,Mv,src.size());
    warpAffine(src,dst,M,src.size());

    // Show the results
    namedWindow( " ORIGINAL ", WINDOW_AUTOSIZE );
    imshow( " ORIGINAL ", src );
    namedWindow( " H-REFLECTION ", WINDOW_AUTOSIZE );
    imshow( " H-REFLECTION ", dsth );
    namedWindow( " V-REFLECTION ", WINDOW_AUTOSIZE );
    imshow( " V-REFLECTION ", dstv );
    namedWindow( " REFLECTION ", WINDOW_AUTOSIZE );
    imshow( " REFLECTION ", dst );

    waitKey();
    return 0;
}
