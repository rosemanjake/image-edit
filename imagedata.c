#include <stdio.h>
#include <stdlib.h>
#include "imagedata.h"

const int HEADER_LENGTH = 54;

// Open file with optional mode.
FILE *openFile(const char* fileName, const char* mode){
  FILE *filePointer;
  filePointer = fopen(fileName, mode);

  if (filePointer == NULL){
    printf("Error: Could not open file.\n");
  }

  return filePointer;
}

// Reads a full bitmap file and return its contents as a byte array.
char *readBitMapData(char *fileName, int *fileSize){
  FILE* file = openFile(fileName, "rb");
  fseek(file, 0, SEEK_END);
  *fileSize = (int)ftell(file);
  fseek(file, 0, SEEK_SET);

  char *fileBuffer = malloc(*fileSize * sizeof(unsigned char));
  fread(fileBuffer, 1, *fileSize, file);
  fclose(file);

  return fileBuffer;
}

// Parse out the core data from the file header.
ImageData *getImageData(char* fileName){
  ImageData *imageData = malloc(sizeof(ImageData));
  imageData->fileSize = 0;
  imageData->fileBuffer = readBitMapData(fileName, &imageData->fileSize);
  if (imageData->fileSize <= 0){
    perror("Could not read file size.");
    return NULL;
  }

  imageData->imageWidth = (unsigned char)imageData->fileBuffer[18] |
                      ((unsigned char)imageData->fileBuffer[19] << 8) |
                      ((unsigned char)imageData->fileBuffer[20] << 16) |
                      ((unsigned char)imageData->fileBuffer[21] << 24);

  imageData->imageHeight = (unsigned char)imageData->fileBuffer[22] |
                      ((unsigned char)imageData->fileBuffer[23] << 8) |
                      ((unsigned char)imageData->fileBuffer[24] << 16) |
                      ((unsigned char)imageData->fileBuffer[25] << 24);

  imageData->dataOffset = (unsigned char)imageData->fileBuffer[10] |
                  ((unsigned char)imageData->fileBuffer[11] << 8) |
                  ((unsigned char)imageData->fileBuffer[12] << 16) |
                  ((unsigned char)imageData->fileBuffer[13] << 24);

  imageData->pixelBytesPerRow = imageData->imageWidth * 3;
  imageData->paddingBytesPerRow = (4 - (imageData->pixelBytesPerRow % 4)) % 4;
  imageData->totalBytesPerRow = imageData->pixelBytesPerRow + imageData->paddingBytesPerRow;

  return imageData;
}

void freeImageData(ImageData *imageData) {
  free(imageData->fileBuffer);
  free(imageData);
}
