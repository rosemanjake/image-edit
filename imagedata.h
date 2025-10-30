
#ifndef IMAGEMETADATA_H_
#define IMAGEMETADATA_H_

#include <stdint.h>
#include <stdio.h>

extern const int HEADER_LENGTH;

typedef struct ImageData{
  int fileSize;
  char *fileBuffer;
  uint32_t imageWidth;
  uint32_t imageHeight;
  uint32_t dataOffset;
  uint32_t pixelBytesPerRow;
  uint32_t paddingBytesPerRow;
  uint32_t totalBytesPerRow;
} ImageData;

ImageData *getImageData(char* fileName);

FILE *openFile(const char* fileName, const char* mode);

void printImageData(struct ImageData *imageData);

void freeImageData(ImageData *imageData);

#endif