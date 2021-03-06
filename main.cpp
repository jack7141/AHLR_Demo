#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat  Image ;
void DrawRectangle(Mat);
int main()
{

    vector<Vec4i> hierarchy;
    Mat mask,result,img_threshold;
    namedWindow("Control", CV_WINDOW_AUTOSIZE);

       int iLowH = 0;
       int iHighH = 179;

       int iLowS = 0;
       int iHighS = 255;

       int iLowV = 0;
       int iHighV = 255;

       //Create trackbars in "Control" window
       cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue
       cvCreateTrackbar("HighH", "Control", &iHighH, 179);

       cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation
       cvCreateTrackbar("HighS", "Control", &iHighS, 255);

       cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value
       cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    Image = imread("C:/Users/ksrnd/Desktop/Light/20190326_003.png");


        Mat img_hsv;
        cvtColor(Image,img_hsv,COLOR_RGB2HSV);

//    inRange(img_hsv, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), mask);
        inRange(img_hsv, Scalar(0, 0, 255), Scalar(179, 255, 255), mask);
        dilate( mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

        erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        DrawRectangle(mask);

    waitKey();

}
void DrawRectangle(Mat mask)
{
    vector<vector<Point>> contours;
    findContours( mask, contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE );

    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());


    for ( size_t i=0; i<contours.size(); i++) {

        approxPolyDP(contours[i],contours_poly[i],3,true);
        boundRect[i]=boundingRect(contours_poly[i]);

    }

    for ( size_t i=0; i<contours.size(); i++ ) {

        rectangle( Image, boundRect[i].tl(), boundRect[i].br(), Scalar(255,255,0), 2);

    }

    imshow("Origin",Image);
    imshow("Detect",mask);
}
