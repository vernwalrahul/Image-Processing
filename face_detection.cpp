#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
Mat image, final_img;
int h_low, h_high, s_low, s_high, v_low, v_high;

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

        for(i = 0; i < image.rows; i++){
            for(j = 0; j < image.cols; j++){
               int key_h = image.at<Vec3b>(i,j)[0];
               int key_s = image.at<Vec3b>(i,j)[1];
               int key_v = image.at<Vec3b>(i,j)[2];
               if(in_between(key_h, h_low, h_high)&&in_between(key_s, s_low, s_high)&&in_between(key_v, v_low, v_high))
                 final_img.at<uchar>(i,j)=255;
               else
                 final_img.at<uchar>(i,j)=0;
            }
        }
    imshow("Binary Image",final_img);    
}

void trackbar()
{
	image = imread("ball.jpg",CV_LOAD_IMAGE_COLOR);
	cvtColor(image, image, CV_BGR2HSV);
	final_img = image.clone();
	namedWindow("Binary Image", WINDOW_AUTOSIZE);
    
    createTrackbar("H_lower_bound", "Binary Image", &h_low, 255, update_image);
    createTrackbar("H_upper_bound", "Binary Image", &h_high, 255, update_image);

    createTrackbar("S_lower_bound", "Binary Image", &s_low, 255, update_image);
    createTrackbar("S_upper_bound", "Binary Image", &s_high, 255, update_image);

    createTrackbar("V_lower_bound", "Binary Image", &v_low, 255, update_image);
    createTrackbar("V_upper_bound", "Binary Image", &v_high, 255, update_image);

    imshow("Binary Image",final_img);
    waitKey(0);
}

int main()
{
	trackbar();
	return 0;
}