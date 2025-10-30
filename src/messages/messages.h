#pragma once
#include "../global/vars.h"

extern void printNewScreen();
extern void printCustom(int lines, char **string);
extern void printGlobalMessage();
extern int mallocGlobalMessage();
extern void freeGlobalMessage();
