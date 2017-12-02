#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>

using namespace std;
using namespace cv;
#define PI 3.14159
Mat image, final_img, image_HSV, stat_image;
int h_low, h_high, s_low, s_high, v_low, v_high, area, sum_x, sum_y;

void show_window()
{
	namedWindow("MyWindow",WINDOW_AUTOSIZE);
	Mat img(600,400,CV_8UC1,Scalar(0));
	imshow("MyWindow",img);
	waitKey(0);
}

int in_between(int key, int x, int y)
{
    if(x<key && key<y)
        return 1;
    else
        return 0;
}

void update_image(int threshold, void *a)
{
	int i, j;
    area = sum_x = sum_y = 0;
        for(i = 0; i < image.rows; i++){
            for(j = 0; j < image.cols; j++){
               int key_h = image_HSV.at<Vec3b>(i,j)[0];
               int key_s = image_HSV.at<Vec3b>(i,j)[1];
               int key_v = image_HSV.at<Vec3b>(i,j)[2];
               if(in_between(key_h, h_low, h_high)&&in_between(key_s, s_low, s_high)&&in_between(key_v, v_low, v_high))
               {
                 final_img.at<uchar>(i,j)=255;
                 sum_x+=i;
                 sum_y+=j;
                 area+=1;
               }
               else
                 final_img.at<uchar>(i,j)=0;
            }
        }
    int radius = sqrt(area/PI);
    Point center;
    if(area!=0)
    {
        center.x = sum_x/area;
        center.y = sum_y/area;
        image = stat_image.clone();
        circle(image, center, radius, 127);  
    }
    imshow("Original Image",image);  
    imshow("Final Image",final_img);    
}

void trackbar()
{
	image = imread("ball.jpg",CV_LOAD_IMAGE_COLOR);
	final_img = image.clone();
    image_HSV = image.clone();
    stat_image = image.clone();
    cvtColor(final_img, final_img, CV_BGR2GRAY);
    cvtColor(image_HSV, image_HSV, CV_BGR2HSV);
	namedWindow("Original Image", WINDOW_AUTOSIZE);
    
    createTrackbar("H_lower_bound", "Original Image", &h_low, 255, update_image);
    createTrackbar("H_upper_bound", "Original Image", &h_high, 255, update_image);

    createTrackbar("S_lower_bound", "Original Image", &s_low, 255, update_image);
    createTrackbar("S_upper_bound", "Original Image", &s_high, 255, update_image);

    createTrackbar("V_lower_bound", "Original Image", &v_low, 255, update_image);
    createTrackbar("V_upper_bound", "Original Image", &v_high, 255, update_image);

    imshow("Original Image",image);
    waitKey(0);
}

int main()
{
	trackbar();
	return 0;
}