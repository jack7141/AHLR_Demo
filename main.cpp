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


    Image = imread("C:/Users/ksrnd/Desktop/Light/20190326_002.png");

    Mat img_hsv;
    cvtColor(Image,img_hsv,COLOR_RGB2HSV);

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

        //Center Point
        Point centerRect = (boundRect[i].tl() + boundRect[i].br())*0.5;
        circle(Image,centerRect,3,Scalar(255,0,255));

        int x = 0;

        if (x - boundRect[1].x < x - boundRect[i].x ) {
            Point UPoint;
            UPoint.x = boundRect[i].x;
            UPoint.y = boundRect[i].y;
            putText(Image," Down  ",UPoint,4,1.2,Scalar(0,255,255));
        } else {
            Point DPoint;
            DPoint.x = boundRect[i].x;
            DPoint.y = boundRect[i].y;
            putText(Image," UP  ",DPoint,4,1.2,Scalar(0,255,255));
        }
    }

    imshow("Origin",Image);
    imshow("Detect",mask);
}
