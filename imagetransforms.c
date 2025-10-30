#include <string.h>
#include "imagedata.h"

// Fill the image with blue pixel
void fillWithSolidColour(char* outputBuffer, ImageData *imageData){
  for (uint32_t row = 0; row < imageData->imageHeight; row++){
    for (uint32_t pixel = 0; pixel < imageData->imageWidth; pixel++){
      int offset = imageData->dataOffset + (row * imageData->totalBytesPerRow) + (pixel * 3);
      outputBuffer[offset] = 0xFF;
      outputBuffer[offset + 1] = 0x00;
      outputBuffer[offset + 2] = 0x00;
    }
  }
}

// Flip image on the X axis (up->down)
// Copies the rows directly from the file buffer to the output buffer, in reverse order.
void verticalFlip(char* outputBuffer, char* fileBuffer, ImageData *imageData){
  for (uint32_t row = 0; row < imageData->imageHeight; row++){
    int outputOffset = imageData->fileSize - (row * imageData->totalBytesPerRow);
    int srcOffset = row * imageData->totalBytesPerRow;
    memcpy(outputBuffer + outputOffset, fileBuffer + srcOffset + imageData->dataOffset, imageData->totalBytesPerRow);
  }
}

// Flip image on the Y axis (left->right)
// Copies each row from the file buffer to the output buffer, with the pixels in reverse order.
void horizontalFlip(char* outputBuffer, char* fileBuffer, ImageData *imageData){
  for (uint32_t row = 0; row < imageData->imageHeight; row++){
    for (uint32_t pixel = 0; pixel < imageData->imageWidth; pixel++){
      int outputOffset = imageData->dataOffset + ((row + 1) * imageData->totalBytesPerRow) - imageData->paddingBytesPerRow - (pixel * 3);
      int srcOffset = imageData->dataOffset + (row * imageData->totalBytesPerRow) + (pixel * 3);
      memcpy(outputBuffer + outputOffset, fileBuffer + srcOffset, 3);
    }
  }
}
