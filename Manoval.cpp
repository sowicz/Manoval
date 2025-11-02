
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath> 

using namespace cv;
int main()
{
    //std::string img_path = "C:\\Users\\sowic\\Desktop\\manom.jpg";
    std::string img_path = "C:\\Users\\sowic\\Desktop\\manom2.jpg";
    //std::string img_path = "C:\\Users\\sowic\\Desktop\\manom3.jpg";
    //std::string img_path = "C:\\Users\\sowic\\Desktop\\manom4.jpg";
    //std::string img_path = "C:\\Users\\sowic\\Desktop\\manom5.jpg";


	Mat img = imread(img_path, IMREAD_COLOR);

	// Verify that the image has been loaded
	if (img.empty()) {
		std::cout << "Nie mogę wczytać obrazu!" << std::endl;
		return -1;
	}
	// Convert to grayscale
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	//imshow("Skala szarosci", gray);


	// Lekki blur – pomaga wykryć okrąg
	GaussianBlur(gray, gray, Size(9, 9), 2);

	// Wykrywanie okręgów metodą Hougha
	std::vector<Vec3f> circles;
	HoughCircles(
		gray,
		circles,
		cv::HOUGH_GRADIENT,
		1,              // dp = rozdzielczość akumulatora
		gray.rows / 8,  // min. odległość między okręgami
		100,            // param1 – threshold dla Canny
		50,             // param2 – im mniejsze, tym więcej fałszywych
		150,              // minimalny radius
		220               // maksymalny radius
	);

	if (circles.empty()) {
		std::cerr << "Brak wykrytych okregow\n";
		return -1;
	}


	// wybierz największy okrąg
	int idx_max = 0;
	int max_r = 0;
	for (size_t i = 0; i < circles.size(); ++i) {
		int r = cvRound(circles[i][2]);
		if (r > max_r) { max_r = r; idx_max = (int)i; }
	}

	Vec3f c = circles[idx_max];
	Point center(cvRound(c[0]), cvRound(c[1]));
	int radius = cvRound(c[2]);


	// narysuj wykryty okrąg
	Mat out = img.clone();
	circle(out, center, radius, Scalar(0, 0, 255), 3);
	circle(out, center, 3, Scalar(0, 255, 0), -1);

	// --- Maska i Canny tylko wewnątrz okręgu ---
	Mat mask = Mat::zeros(gray.size(), CV_8U);
	circle(mask, center, radius - 5, 255, -1); // -5 żeby nie brać obwodu z ramki
	Mat masked;
	gray.copyTo(masked, mask);

	Mat edges;
	Canny(masked, edges, 50, 150);


	// --- HoughLinesP i wybór linii przechodzącej blisko środka ---
	std::vector<cv::Vec4i> lines;
	HoughLinesP(edges, lines, 1, CV_PI / 180, 50, radius / 4, 10);
	double bestLen = 0;
	Vec4i bestLine;



	// --- Wybór linii przechodzącej blisko środka ---
	for (auto& ln : lines) {
		Point p1(ln[0], ln[1]);
		Point p2(ln[2], ln[3]);

		double length = norm(p1 - p2);

		if (length > bestLen) {
			bestLen = length;
			bestLine = ln;
		}
	}

	// jeśli brak linii
	if (bestLen <= 0) {
		std::cout << "Nie znaleziono wskazowki!" << std::endl;
		return 0;
	}


	Point p1(bestLine[0], bestLine[1]);
	Point p2(bestLine[2], bestLine[3]);
	line(out, p1, p2, Scalar(255, 0, 0), 3);

	// wybierz koniec wskazówki
	double d1 = norm(p1 - center);
	double d2 = norm(p2 - center);
	Point tip = (d1 > d2) ? p1 : p2;

	// --- wyznaczanie strefy ---
	double angleRad = atan2(center.y - tip.y, tip.x - center.x);
	double angleDeg = angleRad * 180.0 / CV_PI;

	if (angleDeg < 0)
		angleDeg += 360.0;

	std::cout << "Kąt wskazówki: " << angleDeg << " stopni" << std::endl;

	// --- STREFY  ---
	int strefa = 0;

	if (angleDeg >= 315 || angleDeg < 45)
		strefa = 3;
	else if (angleDeg >= 45 && angleDeg < 135)
		strefa = 2;
	else if (angleDeg >= 135 && angleDeg < 230)
		strefa = 1;
	else if (angleDeg >= 230 && angleDeg < 315)
		strefa = 4;

	std::cout << "Strefa: " << strefa << std::endl;



	// Funkcja pomocnicza — rysowanie promienia w danym kierunku
	auto drawRay = [&](double angleDeg, cv::Scalar color) {
		double a = angleDeg * CV_PI / 180.0;

		int x2 = center.x + radius * cos(a);
		int y2 = center.y - radius * sin(a); // minus dla osi Y!

		line(out, center, Point(x2, y2), color, 2);
		};

	drawRay(-45, Scalar(0, 255, 0));
	drawRay(45, Scalar(0, 255, 0));
	drawRay(135, Scalar(0, 255, 0));
	drawRay(230, Scalar(0, 255, 0));

	// narysuj promienie co 90 stopni (4 strefy)
	//drawRay(-45, Scalar(0, 255, 0));   // 0° → w prawo
	//drawRay(45, Scalar(0, 255, 0));   // 90° → w górę
	//drawRay(135, Scalar(0, 255, 0));   // 180° → w lewo
	//drawRay(230, Scalar(0, 255, 0));   // 270° → w dół
	//strefa 4 wykluczona (strefa martwa gdzie wskazowka nie dojdzie)

	std::cout << "!!!!!_______Strefa: " << strefa << std::endl;
	imshow("Out", out);
	//imshow("Edges", edges);
	//imshow("Masked", masked);
	//imshow("Wykryty okrag", gray);



	waitKey(0);

}