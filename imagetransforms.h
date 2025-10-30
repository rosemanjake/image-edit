#ifndef IMAGETRANSFORMS_H_
#define IMAGETRANSFORMS_H_

void verticalFlip(unsigned char* outputBuffer, unsigned char* fileBuffer, ImageData *imageData);

void horizontalFlip(unsigned char* outputBuffer, unsigned char* fileBuffer, ImageData *imageData);

void fillWithSolidColour(unsigned char* outputBuffer, ImageData *imageData);

#endif