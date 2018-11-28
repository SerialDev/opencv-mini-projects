#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/viz/vizcore.hpp>


int main (  ) {
    std::cout << std::endl << "Hi this is " << __FILE__ << "." << std::endl;

    // Load image in same format as stored 
    const char *fileIn = "../data/test.png";
    const int colorMode = CV_LOAD_IMAGE_UNCHANGED;
    IplImage *img = cvLoadImage( fileIn, colorMode);
    if(img == 0) {
        std::cerr << "ERROR: could not be read:" << fileIn << std::endl ;
        return 1;
    }
    std::cout << "read in image from : " << fileIn << std::endl;
    // create window and move it to upper left corner (0, 0)
    const char *window = "image";
    cvNamedWindow( window, CV_WINDOW_AUTOSIZE);
    cvMoveWindow( window, 0, 0);

    cvShowImage(window, img);

    std::cout << "press any key while image window has focus." << std::endl;
    const int durationInMilliSeconds = 0;
    int key = cvWaitKey( durationInMilliSeconds );
    std::cout << "received key code " << key << std::endl;

    cvReleaseImage(&img);
    cvDestroyWindow(window);
    std::cout << "completed" << __FILE__ << std::endl;
    return 0;
 }


// int main()
// {
//     cv::viz::Viz3d window = cv::viz::Viz3d("Viz demonstration");

//     cv::Point3d min(0.25, 0.0, 0.25);
//     cv::Point3d max(0.75, 0.5, 0.75);

//     cv::viz::WCube cube(min, max, true, cv::viz::Color::blue());
//     cube.setRenderingProperty(cv::viz::LINE_WIDTH, 4.0);

//     window.showWidget("Axis widget", cv::viz::WCoordinateSystem());
//     window.showWidget("Cube widget", cube);

//     while(!window.wasStopped()) {
//         window.spinOnce(1, true);
//     }

//     return 0;
// }
