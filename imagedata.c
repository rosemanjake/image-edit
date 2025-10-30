#include <stdio.h>
#include <stdlib.h>
#include "imagedata.h"

const int HEADER_LENGTH = 54;

// Open file with optional mode.
FILE *openFile(const char* fileName, const char* mode){
  FILE *filePointer;
  filePointer = fopen(fileName, mode);

  if (filePointer == NULL){
    perror("Error: Could not open file.\n");
    return NULL;
  }

  return filePointer;
}

// Reads a full bitmap file and return its contents as a byte array.
unsigned char *readBitMapData(char *fileName, int *fileSize){
  FILE* file = openFile(fileName, "rb");
  if (file == NULL) return NULL;
  fseek(file, 0, SEEK_END);
  *fileSize = (int)ftell(file);
  fseek(file, 0, SEEK_SET);

  unsigned char *fileBuffer = malloc(*fileSize * sizeof(unsigned char));
  if (fileBuffer == NULL){
    perror("Could not allocate memory for fileBuffer");
    return NULL;
  }
  fread(fileBuffer, 1, *fileSize, file);
  fclose(file);

  return fileBuffer;
}

// Parse out the core data from the BMP file.
ImageData *getImageData(char* fileName){
  ImageData *imageData = malloc(sizeof(ImageData));
  imageData->fileSize = 0;
  imageData->fileBuffer = readBitMapData(fileName, &imageData->fileSize);
  if (imageData->fileSize <= 0 || imageData->fileBuffer == NULL){
    perror("Could not read file.");
    return NULL;
  }

  imageData->imageWidth = imageData->fileBuffer[18] |
                      (imageData->fileBuffer[19] << 8) |
                      (imageData->fileBuffer[20] << 16) |
                      (imageData->fileBuffer[21] << 24);

  imageData->imageHeight = imageData->fileBuffer[22] |
                      (imageData->fileBuffer[23] << 8) |
                      (imageData->fileBuffer[24] << 16) |
                      (imageData->fileBuffer[25] << 24);

  imageData->dataOffset = imageData->fileBuffer[10] |
                  (imageData->fileBuffer[11] << 8) |
                  (imageData->fileBuffer[12] << 16) |
                  (imageData->fileBuffer[13] << 24);

  imageData->pixelBytesPerRow = imageData->imageWidth * 3;
  imageData->paddingBytesPerRow = (4 - (imageData->pixelBytesPerRow % 4)) % 4;
  imageData->totalBytesPerRow = imageData->pixelBytesPerRow + imageData->paddingBytesPerRow;

  return imageData;
}

void freeImageData(ImageData *imageData) {
  free(imageData->fileBuffer);
  free(imageData);
}
