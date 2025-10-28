#ifndef COMMANDINFO_H_
#define COMMANDINFO_H_

enum TRANSFORMATION{
  VERTICAL_FLIP,
  HORIZONTAL_FLIP,
  SOLID_COLOR
};

typedef struct CommandInfo{
  enum TRANSFORMATION transformation;
  char* inputFileName;
  char* outputFileName;
} CommandInfo;

CommandInfo *getCommandInfo(int argc, char *argv[]);

#endif