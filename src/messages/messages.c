#include "messages.h"
#include "../global/vars.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void fillIn (char *str, int size, char what) {
  for (int i = 0; i < size-1; i++) {
    str[i] = what;
  }
  str[size-1] = '\0';
}

int strlenIgnoreSpecialCodes(const char *str) {
int len = 0;
  int code = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '\x1b') {
      code = 1; // Start of ANSI escape
    } else if (code == 1 && str[i] == 'm') {
      code = 0; // End of ANSI escape
    } else if (code == 0) {
      len++; // Count only visible characters
    }
  }
  return len;
}

void putInsideBox (char **items, int lines, int leftBorder, int rightBorder) {
  int max = stdMaxChars-50;
  for (int i = 0; i < lines; i++) {
    int len = strlenIgnoreSpecialCodes(items[i]);
    int left = (max-len)/2; int right = (max-len)/2;
    if (left + right != max-len) right++;
    char leftStr[left+1]; char rightStr[right+1];
    char fillLeft = '\0'; char fillRight = '\0';
    if (leftBorder == 1) fillLeft = ' '; if (rightBorder == 1) fillRight = ' ';
    fillIn(leftStr, left, fillLeft); fillIn(rightStr, right, fillRight);
    char temp[max]; strcpy(temp, items[i]);
    sprintf(items[i], "%s%s%s", leftStr, temp, rightStr);
  }
}

void addSideInfo (char items[][stdMaxChars], char add[][stdMaxChars], int lines) {
  for (int i = 0; i < lines; i++) {
    strcat(items[i], " ");
    strcat(items[i], add[i]);
  }
}

void printNewScreen() {
  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #else
    system("clear");
  #endif
}

void transformNumberIntoPrintable(char *cool, char n) {
  //does not check for non numbers so use it properly, loser
  for (char i = 0; i < n; i++) {
    if (cool[i] == -1) cool[i] = ' ';
    else if (cool[i] < 10) cool[i]+=48;
  }
}

void printCustom(int lines, char **string) {
  putInsideBox(string, lines, 1, 1);
  for (int i = 0; i < lines; i++) {
    printf("%s\n", string[i]);
  }
}

void freeGlobalMessage() {
  for (int i = 0; i < globalMessage.lines; i++) {
    free(globalMessage.content[i]);
  }
  free(globalMessage.content);
  globalMessage.lines = 0;
}

void printGlobalMessage() {
  putInsideBox(globalMessage.content, globalMessage.lines, 1, 1);
  for (int i = 0; i < globalMessage.lines; i++) {
    printf("%s\n", globalMessage.content[i]);
  }
  freeGlobalMessage();
}

int mallocGlobalMessage() {
  int lines = globalMessage.lines;
  printNewScreen();
  globalMessage.content = malloc(lines * sizeof(char *));
  if (globalMessage.content == NULL) {
    perror("Main malloc failed for global message");
    return 1;
  }

  for (int i = 0; i < lines; i++) {
    globalMessage.content[i] = malloc(stdMaxChars * sizeof(char));
    if (globalMessage.content[i] == NULL) {
      perror("second malloc failed");
      for (int i2 = 0; i2 < i; i2++) free(globalMessage.content[i2]);
      free(globalMessage.content);
      return 1;
    }
  }
}