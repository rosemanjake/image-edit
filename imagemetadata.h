
#ifndef IMAGEMETADATA_H_
#define IMAGEMETADATA_H_

#include <stdint.h>

extern const int HEADER_LENGTH;

typedef struct ImageMetadata{
  uint32_t fileSize;
  uint32_t imageWidth;
  uint32_t imageHeight;
  uint32_t dataOffset;
  uint32_t pixelBytesPerRow;
  uint32_t paddingBytesPerRow;
  uint32_t totalBytesPerRow;
  char* fullHeader;
} ImageMetadata;

ImageMetadata *getHeaderInfo(unsigned char* fileBuffer);

void printImageMetadata(struct ImageMetadata *metadata);

void freeImageMetadata(ImageMetadata *metadata);

#endif