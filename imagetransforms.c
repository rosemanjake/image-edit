#include "imagemetadata.h"

// Need to refactor this to work with the 2d array?
void fillWithSolidColour(unsigned char** finalData, ImageMetadata *metadata){
  for (int y = metadata->imageHeight - 1; y >= 0; y--){ 
    for (uint32_t x = 0; x < metadata->pixelBytesPerRow; x+=3){
      finalData[y][x] = 0xFF;
      finalData[y][x + 1] = 0x00;
      finalData[y][x + 2] = 0x00;
    }
  }
}

// Flip an image on the y axis.
void verticalFlip(unsigned char** pixelArray, unsigned char** finalData, ImageMetadata *metadata){
  int currentRow = 0;
  for (int y = metadata->imageHeight - 1; y >= 0; y--){ 
    for (uint32_t x = 0; x < metadata->totalBytesPerRow; x++){
      finalData[currentRow][x] = pixelArray[y][x];
    }
    currentRow++;
  }
}

// Flip an image on the x axis.
void horizontalFlip(unsigned char** pixelArray, unsigned char** finalData, ImageMetadata *metadata){
  for (uint32_t y = 0; y < metadata->imageHeight; y++){ 
    int cellOffset = 0;
    for (int32_t x = (metadata->totalBytesPerRow - metadata->paddingBytesPerRow) - 1; x >= 0; x-=3){
      finalData[y][cellOffset] = pixelArray[y][x-2];
      finalData[y][cellOffset+1] = pixelArray[y][x-1];
      finalData[y][cellOffset+2] = pixelArray[y][x];
      cellOffset+=3;
    }
    for (uint32_t p = 0; p < metadata->paddingBytesPerRow; p++) {
      finalData[y][metadata->pixelBytesPerRow + p] = 0x00;
    }
  }
}

