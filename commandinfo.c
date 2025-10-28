#include "commandinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parses command line arguments
CommandInfo *getCommandInfo(int argc, char *argv[]){
  // Binary args should be arg count, function, input file, output file
  if (argc != 4){
    printf("Incorrect number of arguments. Expected 3, but was %d!\n", argc);
    return NULL;
  }

  CommandInfo *commandInfo = malloc(sizeof(CommandInfo));
  commandInfo->inputFileName = argv[2];
  commandInfo->outputFileName = argv[3];

  if (strcmp(argv[1], "vertical_flip") == 0){
    commandInfo->transformation = VERTICAL_FLIP;
  }else if(strcmp(argv[1], "horizontal_flip") == 0){
    commandInfo->transformation = HORIZONTAL_FLIP;
  }else if(strcmp(argv[1], "solid_color") == 0){
    commandInfo->transformation = SOLID_COLOR;
  } else{
    printf("No valid function argument provided!\n");
    free(commandInfo);
    return NULL;
  }

  return commandInfo;
}

