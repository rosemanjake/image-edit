#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "commandinfo.h"
#include "imagedata.h"
#include "imagetransforms.h"

// Use the parsed command line argeuments and image data to perform a transform on an image.
void processImage(CommandInfo *commandInfo, ImageData *imageData){
  unsigned char* outputBuffer = malloc(imageData->fileSize);
  memcpy(outputBuffer, imageData->fileBuffer, imageData->fileSize);

  switch (commandInfo->transformation){
    case VERTICAL_FLIP:
      verticalFlip(outputBuffer, imageData->fileBuffer, imageData);
      break;
    case HORIZONTAL_FLIP:
      horizontalFlip(outputBuffer, imageData->fileBuffer, imageData);
      break;
    case SOLID_COLOR:
      fillWithSolidColour(outputBuffer, imageData);
      break;
    default:
      puts("No valid transformation found!");
      break;
  }

  FILE* outputFile = openFile(commandInfo->outputFileName, "wb");
  fwrite(outputBuffer, 1, imageData->fileSize, outputFile);
  fclose(outputFile);
  free(outputBuffer);
}

int main(int argc, char *argv[]){
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  CommandInfo *commandInfo = getCommandInfo(argc, argv);
  if (commandInfo == NULL){
    printf("Could not parse command line arguments!\n");
    return 1;
  }

  ImageData *imageData = getImageData(commandInfo->inputFileName);
  if (imageData == NULL) {
    printf("Failed to parse Bitmap file, exiting.\n");
    return 1;
  }

  processImage(commandInfo, imageData);

  free(commandInfo);
  freeImageData(imageData);

  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Function took %f seconds to execute (CPU time).\n", cpu_time_used);

  return 0;
}