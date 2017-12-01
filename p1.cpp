#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
Mat image, final_img;
void show_window()
{
	namedWindow("MyWindow",WINDOW_AUTOSIZE);
	Mat img(600,400,CV_8UC1,Scalar(0));
	imshow("MyWindow",img);
	waitKey(0);
}

void update_image(int threshold, void *a)
{
	int i, j;

        for(i = 0; i < image.rows; i++){
            for(j = 0; j < image.cols; j++){
                if(image.at<uchar>(i, j) > threshold)
                    final_img.at<uchar>(i, j) = 255;
                else
                    final_img.at<uchar>(i, j) = 0;
            }
        }
    imshow("Binary Image",final_img);    
}

void trackbar()
{
	image = imread("lena.jpg",CV_LOAD_IMAGE_COLOR);
	cvtColor(image, image, CV_BGR2GRAY);
	final_img = image.clone();
	namedWindow("Binary Image", WINDOW_AUTOSIZE);
    int threshold = 127;
    createTrackbar("change_me", "Binary Image", &threshold, 255, update_image);
    imshow("Binary Image",final_img);
    waitKey(0);
}

int main()
{
	trackbar();
	return 0;
}