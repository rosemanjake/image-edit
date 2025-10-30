#include "imagemetadata.h"
#include <stdio.h>
#include <stdlib.h>

const int HEADER_LENGTH = 54;

// Parse out the core data from the file header.
ImageMetadata *getHeaderInfo(unsigned char* fileBuffer){
  ImageMetadata *metadata = malloc(sizeof(ImageMetadata));

  metadata->fileSize = fileBuffer[2] | 
                    (fileBuffer[3] << 8) | 
                    (fileBuffer[4] << 16) | 
                    (fileBuffer[5] << 24);

  metadata->imageWidth = fileBuffer[18] | 
                      (fileBuffer[19] << 8) | 
                      (fileBuffer[20] << 16) | 
                      (fileBuffer[21] << 24);

  metadata->imageHeight = fileBuffer[22] | 
                      (fileBuffer[23] << 8) | 
                      (fileBuffer[24] << 16) | 
                      (fileBuffer[25] << 24);

  metadata->dataOffset = fileBuffer[10] | 
                  (fileBuffer[11] << 8) | 
                  (fileBuffer[12] << 16) | 
                  (fileBuffer[13] << 24);

  metadata->pixelBytesPerRow = metadata->imageWidth * 3;
  metadata->paddingBytesPerRow = (4 - (metadata->pixelBytesPerRow % 4)) % 4;
  metadata->totalBytesPerRow = metadata->pixelBytesPerRow + metadata->paddingBytesPerRow;

  char* fullHeader = malloc(HEADER_LENGTH);
  for (int i = 0; i < HEADER_LENGTH; i++){
    fullHeader[i] = fileBuffer[i];
  }
  metadata->fullHeader = fullHeader;

  return metadata;
}

void freeImageMetadata(ImageMetadata *metadata) {
  free(metadata->fullHeader);
  free(metadata);
}

void printImageMetadata(struct ImageMetadata *metadata){
  printf("File size: %d\n", metadata->fileSize);
  printf("Image height: %d\n", metadata->imageHeight);
  printf("Image width: %d\n", metadata->imageWidth);
  printf("pixelBytesPerRow: %d\n", metadata->pixelBytesPerRow);
  printf("paddingBytesPerRow: %d\n", metadata->paddingBytesPerRow);
}
