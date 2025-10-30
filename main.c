#include <stdio.h>
#include "src/global/vars.h"
#include "src/messages/messages.h"

#ifdef __linux__
#define resultOfOperatingSystem 1;
#include <unistd.h>
void Sleep (int sb) {
    sb = sb + 1;
    if (sb > 10) {
        // do nothing, dummy function
        sb = 0;
    }
}
#endif
#ifdef WIN32
#define resultOfOperatingSystem 2
#include <windows.h>
static void usleep (int sb) {
    sb = sb + 1;
    if (sb > 10) {
        // do nothing, dummy function
        sb = 0;
    }
}
#else
#ifdef _WIN32
#define resultOfOperatingSystem 2
#include <windows.h>
static void usleep (int sb) {
    sb = sb + 1;
    if (sb > 10) {
        // do nothing, dummy function
        sb = 0;
    }
}
#endif
#endif

void wait (int _num) {
    if (resultOfOperatingSystem == 1) usleep(_num * 1000);
    if (resultOfOperatingSystem == 2) Sleep(_num);
}

//compile cmd
// gcc main.c src/global/vars.c src/messages/messages.c src/tools/tools.h -o main

void mainSwitch(int option);

int main () {
    globalMessage.lines = 3;
    mallocGlobalMessage();
    sprintf(globalMessage.content[0], "---------- Genetic calculator ----------");
    sprintf(globalMessage.content[1], "Made by Gabriel Hugi");
    sprintf(globalMessage.content[2], "V 1.0");
    printGlobalMessage();
    wait(2000);

    globalMessage.lines = 2;
    mallocGlobalMessage();
    sprintf(globalMessage.content[0], "Choose mode");
    sprintf(globalMessage.content[1], "1 - One simple gene (eg. Aa x aa)");
    printGlobalMessage();
    
    int mode = 0;
    scanf("%d", &mode);

    mainSwitch(mode);


    printNewScreen();
    return 0;
}

void mainSwitch(int mode) {
    switch(mode) {
        case 1:
            globalMessage.lines = 4;
            mallocGlobalMessage();
            sprintf(globalMessage.content[0], "Choose submode");
            sprintf(globalMessage.content[1], "1 - Offspring breeds with parents at random");
            sprintf(globalMessage.content[2], "2 - Offspring breeds with brothers at random");
            sprintf(globalMessage.content[3], "3 - Offspring breeds at random");
            printGlobalMessage();

            int option = 0;
            scanf("%d", &option);
        break;

    }
}