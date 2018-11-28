
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/viz/vizcore.hpp>

IplImage *loadAndShowImage (const char *filename,
    const int isColor,
    const char *window,
    const int x, const int y) {
    // Load image from file
    IplImage *img = cvLoadImage( filename, isColor);
    if (img == 0 ){
        std::cerr << "ERROR: could not load image from:  " << std::endl << filename << std::endl;
        return 0;
    }
    std::cout << "read in image from : " << std::endl << filename << std::endl;

    cvNamedWindow(window, CV_WINDOW_AUTOSIZE );
    cvMoveWindow( window, x, y );
    cvShowImage( window, img );

    return img;
}

const char *getFilename (int argn, char *arg[], const int  ix, const char *file) {
    if(argn <= ix ){
        return file;
    } else {
        return arg[ix];
    }
}

void saveModImage(const char *fileIn, IplImage *img){
    const unsigned maxFileOut = 1024;
    char fileOut[maxFileOut];
    sprintf(fileOut,"%s_out.jpg",fileIn);

    int errorCode = 0;
    if ( cvSaveImage( fileOut, img ) != 1) {
        std::cerr << "Error: while writing image: " << fileOut << std::endl;
        errorCode = 1;
    } else {
        std::cout << "wrote image to " << fileOut << std::endl;
    }
}

IplImage *convertImage(IplImage *img ){
    std::cout << "showing image with 3-channels..." << std::endl;

    // create an image of the same size and depth  but only one channel
    const int tx = 0.1 * img->width;
    const int ty = 0.1 * img->height;

    cvSetImageROI(img, cvRect( tx,ty, 8*tx, 8*ty));
    IplImage *imgGray = cvCreateImage(cvGetSize(img),img->depth,1);

    // convert color image to grayscale
    const int conversionMode = CV_RGB2GRAY;
    cvCvtColor(img, imgGray, conversionMode);
    cvResetImageROI(img);

    // create a window and show grayscale image
    const char *window2 = "grayscale";
    cvNamedWindow(window2, CV_WINDOW_AUTOSIZE);
    cvMoveWindow( window2, 450, 0);
    cvShowImage( window2, imgGray );
    std::cout << "showing image in grayscale..." << std::endl;

}

int main ( int argn, char *argv[]  ) {
    std::cout << std::endl << "Hi this is " << __FILE__ << "." << std::endl;
    const char *window = "image";
    const char *fileImg = getFilename(argn,argv,1,"../data/test.png");

    IplImage *img = loadAndShowImage(fileImg,CV_LOAD_IMAGE_UNCHANGED,window,0,0);
    // IplImage *img = loadAndShowImage(fileImg,CV_LOAD_IMAGE_GRAYSCALE,window,0,0);


    std::cout << "read in image from: " << fileImg << std::endl;


    IplImage *imgGray = convertImage( img );

    std::cout << "press any key while image window has focus." << std::endl;
    const int durationInMilliSeconds = 0;
    int key = cvWaitKey( durationInMilliSeconds );
    std::cout << "received key code " << key << std::endl;


    saveModImage("test",img);

    //release memory
    cvReleaseImage(&img);
    // cvReleaseImage(&imgGray);
    cvDestroyWindow(window);
    cvDestroyAllWindows();

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
