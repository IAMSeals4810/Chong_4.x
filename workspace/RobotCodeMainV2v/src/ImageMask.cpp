#include "ImageMask.h"

ImageMask::ImageMask(){
	image = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	binaryImage = imaqCreateImage(IMAQ_IMAGE_U8, 0);
	error = 0;
}

ImageMask::ImageMask(Image* img, Image* binImg, int imaqError){
	image = img;
	binaryImage = binImg;
	error = imaqError;
}

bool ImageMask::maskImage(){
	error = imaqColorThreshold(image, binaryImage, 255, IMAQ_HSV, &RING_HUE_RANGE, &RING_SAT_RANGE, &RING_VAL_RANGE);
	if(error < IMAQdxErrorSuccess){
		return false;
	}
	return true;
}

void ImageMask::setImage(Image* img){
	image = img;
}

Image* ImageMask::getbinImage(){
	return binaryImage;
}

int ImageMask::getError(){
	return error;
}
