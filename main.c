#include <stdio.h>
#include "src/global/vars.h"
#include "src/messages/messages.h"

//compile cmd
// gcc main.c src/global/vars.c src/messages/messages.c -o main
int main () {
    globalMessage.lines = 3;
    mallocGlobalMessage();
    sprintf(globalMessage.content[0], "---------- Genetic calculator ----------");
    sprintf(globalMessage.content[1], "Made by Gabriel Hugi");
    sprintf(globalMessage.content[2], "V 1.0");
    printGlobalMessage();

    return 0;
}