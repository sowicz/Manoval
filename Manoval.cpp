
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
int main()
{
    std::string img_path = "C:\\Users\\sowic\\Desktop\\manom.jpg";

	Mat img = imread(img_path, IMREAD_COLOR);

	// Verify that the image has been loaded
	if (img.empty()) {
		std::cout << "Nie mogę wczytać obrazu!" << std::endl;
		return -1;
	}
	// Convert to grayscale
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	cv::imshow("Skala szarosci", gray);


	waitKey(0);

}