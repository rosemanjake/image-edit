#ifndef IMAGETRANSFORMS_H_
#define IMAGETRANSFORMS_H_

void verticalFlip(unsigned char** pixelArray, unsigned char** finalData, ImageMetadata *metadata);

void horizontalFlip(unsigned char** pixelArray, unsigned char** finalData, ImageMetadata *metadata);

void fillWithSolidColour(unsigned char** finalData, ImageMetadata *metadata);

#endif