#ifndef IMAGETRANSFORMS_H_
#define IMAGETRANSFORMS_H_

void verticalFlip(char* outputBuffer, char* fileBuffer, ImageData *imageData);

void horizontalFlip(char* outputBuffer, char* fileBuffer, ImageData *imageData);

void fillWithSolidColour(char* outputBuffer, ImageData *imageData);

#endif