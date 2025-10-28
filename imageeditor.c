#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "commandinfo.h"
#include "imagemetadata.h"
#include "imagetransforms.h"

FILE *openFile(const char* fileName, const char* mode){
  FILE *filePointer;
  filePointer = fopen(fileName, mode);

  if (filePointer == NULL){
    printf("Error: Could not open file.\n");
  }

  return filePointer;
}

// Reads a full bitmap file and return its contents as a byte array.
unsigned char* readBitMapData(char* fileName){
  FILE* file = openFile(fileName, "rb");
  if (file == NULL) return NULL;
  fseek(file, 0, SEEK_END); // Use file system to point to the file's final byte
  long fileSize = ftell(file); // Get the file length
  fseek(file, 0, SEEK_SET); // Point to the file's first byte

  unsigned char* fileBuffer = malloc(fileSize * sizeof(unsigned char));
  fread(fileBuffer, 1, fileSize, file);

  return fileBuffer;
}

// Creates a 2d array that fits the dimensions in the image metadata.
// That is, it is a 2d array of the data in the BMP file exluding the header.
unsigned char **getPixelArray(ImageMetadata *metadata){
  unsigned char **pixelArray = malloc(metadata->imageHeight * sizeof(unsigned char *));
  for (u_int32_t i = 0; i < metadata->imageHeight; i++){
    pixelArray[i] = malloc(metadata->totalBytesPerRow * sizeof(unsigned char *));
  }
  return pixelArray;
}

// Fills the 2d pixel array with the data from the provided char array.
// The char array should be the file buffer containing the full BMP file data.
void fillPixelArray(unsigned char** pixelArray, unsigned char *data, ImageMetadata *metadata){
  for (uint32_t y = 0; y < metadata->imageHeight; y++){
    for (uint32_t x = 0; x < metadata->pixelBytesPerRow; x+=3){
      int fileBufferOffset = metadata->dataOffset + (y * metadata->totalBytesPerRow) + x;
      pixelArray[y][x] = data[fileBufferOffset];
      pixelArray[y][x + 1] = data[fileBufferOffset + 1];
      pixelArray[y][x + 2] = data[fileBufferOffset + 2];
    }
    for (uint32_t p = 0; p < metadata->paddingBytesPerRow; p++) {
      pixelArray[y][metadata->pixelBytesPerRow + p] = 0x00;
    }
  }
}

// Transform the 2d array with the image data into a 1d array of bytes.
// We use the 2d array for making modifications, but ultimately the file is a single array of bytes.
char* flattenPixelArray(unsigned char **data, ImageMetadata *metadata){
  char* newData = malloc(metadata->fileSize);
  int currentOffset = metadata->dataOffset;
  // Add header data
  for (int i = 0; i < HEADER_LENGTH; i++){
    newData[i] = metadata->fullHeader[i];
  }
  // Add pixel data
  for (uint32_t i = 0; i < metadata->imageHeight; i++){
    for (uint32_t j = 0; j < (metadata->pixelBytesPerRow + metadata->paddingBytesPerRow); j++){
      newData[currentOffset] = data[i][j];
      currentOffset++;
    }
  }
  return newData;
}

// Use the parsed command line argeuments and image data to perform a transform on an image.
void processImage(CommandInfo *commandInfo, ImageMetadata *metadata, unsigned char* fileBuffer){
  // Parse the input file's pixel data into a 2d array.
  unsigned char **pixelArray = getPixelArray(metadata);
  fillPixelArray(pixelArray, fileBuffer, metadata);

  // Allocate the 2d array for the final modified image data.
  unsigned char **modifiedImageData = getPixelArray(metadata);

  switch (commandInfo->transformation){
    case VERTICAL_FLIP:
      verticalFlip(pixelArray, modifiedImageData, metadata);
      break;
    case HORIZONTAL_FLIP:
      horizontalFlip(pixelArray, modifiedImageData, metadata);
      break;
    case SOLID_COLOR:
      fillWithSolidColour(modifiedImageData, metadata);
      break;
    default:
      puts("No valid transformation found!");
      break;
  }

  FILE* outputFile = openFile(commandInfo->outputFileName, "wb");
  fwrite(flattenPixelArray(modifiedImageData, metadata), 1, metadata->fileSize, outputFile);
}

int main(int argc, char *argv[]){
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  CommandInfo* commandInfo = getCommandInfo(argc, argv);
  if (commandInfo == NULL){
    printf("Could not parse command line arguments!\n");
    return 1;
  }

  unsigned char* fileBuffer = readBitMapData(commandInfo->inputFileName);
  if (fileBuffer == NULL) {
    printf("Failed to open file, exiting.\n");
    return 1;
  }

  ImageMetadata *metadata = getHeaderInfo(fileBuffer);
  if (metadata == NULL) {
    printf("Failed to parse file header, exiting.\n");
    return 1;
  }

  processImage(commandInfo, metadata, fileBuffer);

  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Function took %f seconds to execute (CPU time).\n", cpu_time_used);

  return 0;
}