#include "rotate.h"
#include "translate.h"
#include "scale.h"
#include "similarity.h"
#include "GaussianFilter.h"
#include "enhancements.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>

#include "argparse.hpp"

#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <filesystem>

using namespace imgproc;

void rotate(const Image& img, const double ang)
{
    Image rotatedImgFwd = Rotation::rotate(img, ang, Rotation::rotateMethod::FWD_MAP);
	Image rotatedImgInv = Rotation::rotate(img, ang, Rotation::rotateMethod::INV_MAP);
    cv::imshow("rotatedImgFwd", imgToMat(rotatedImgFwd));
	cv::imshow("rotatedImgInv", imgToMat(rotatedImgInv));
}


void translate(const Image& img, const std::vector<int>& t)
{
    Image translatedImg = translate(img, t[0] /* tx */, t[1] /* ty */);
	cv::imshow("translatedImg", imgToMat(translatedImg));
}

void scale(const Image& img, const uint8_t scaleFac)
{
    Image scaledImg = Scale::scale(img, Scale::InterpolationMethod::Bilinear, scaleFac);
	Image scaledImg2 = Scale::scale(img, Scale::InterpolationMethod::NearestNeighbour, scaleFac);

    cv::imshow("scaled - bilinear", imgToMat(scaledImg));
    cv::imshow("scaled -- NN", imgToMat(scaledImg2));
}

void simTransform(const Image& img)
{
	Image similarTransformImg = similarityTransform(img);
	cv::imshow("similarityTransform", imgToMat(similarTransformImg));
}

void blur(const Image& img, const int kernelSize)
{
	auto blurredImg = applyGuassian(img, kernelSize, 3.f);
    cv::imshow("blurred", imgToMat(blurredImg));
}

void getPyramid(const Image& img)
{
	std::vector<Image> pyramid = getGuassianPyramid(img);
    std::cout << pyramid.size(); 

	for (size_t i = 0; i < pyramid.size(); i++)
 		cv::imshow("level " + std::to_string(i + 1), imgToMat(pyramid[i]));

}

void setupArgs(argparse::ArgumentParser& prog)
{
	// Required arg.
	prog.add_argument("img").help("image path");

	// Optional args (atleast one is required).
	prog.add_argument("-r", "--rotate")
		.help("rotate image by X degrees")
		.scan<'g', double>()
		.default_value(15);
	
	prog.add_argument("-t", "--translate")
		.help("translate image by X pixels to the right and Y pixels down")
		.nargs(2)
		.scan<'i', int>();

	prog.add_argument("--scale")
		.help("scale image by X value")
		.nargs(1)
		.scan<'i', int>();
	
	prog.add_argument("-si", "--sim")
		.help("apply similatry transform to image");
	
	prog.add_argument("--blur")
		.help("blur image by NxN Gaussian kernel")
		.scan<'i', int>();

}

int main(int argc, char** argv)
{
	argparse::ArgumentParser program{};
	setupArgs(program);

	try { program.parse_args(argc, argv); }
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		std::cerr << program;
		return 1;
	}
	
    Image img = matToImg(cv::imread(program.get<std::string>("img")));

	if (program.is_used("--rotate"))
 		rotate(img, program.get<double>("--rotate"));
	if (program.is_used("--translate"))
		translate(img, program.get<std::vector<int>>("--translate"));
 	if (program.is_used("--scale"))
		scale(img, program.get<int>("--scale"));
	if (program.is_used("--sim"))
		simTransform(img);
	if (program.is_used("--blur"))
 		blur(img, program.get<int>("--blur"));
 	// getPyramid(img);

	//Image darkImg = adjustBrightness(img, -100);
	//Image brightImg = adjustBrightness(img, 100);
	//Image invertedImg = invert(img);
	//Image contrastLowImg = contrast(img, 0.5);
	//Image contrastHighImg = contrast(img, 1.5);
	// cv::Mat grayImg = toGrayscale(img);
	// cv::imshow("darkened",   imgToMat(darkImg));
	// cv::imshow("brightened", imgToMat(brightImg));
	// cv::imshow("inverted", imgToMat(invertedImg));
	// cv::imshow("contrast lowered", imgToMat(contrastLowImg));
	// cv::imshow("contrast Higher",  imgToMat(contrastHighImg));
  	// cv::imshow("grayscale", grayImg);

	// TODO: 
	// - image pyramids (Laplacian), non-linear filters, template matching
	// - edge/corner detection
	// 	- simple feature detector
	// - stereo vision
	// - 3D reconstruction
	
    cv::imshow("originalImg", imgToMat(img));
    cv::waitKey();
    cv::destroyAllWindows();
    
	return 0;
}
