#pragma once

// structs

struct message {
    char **content;
    int lines;
};


//var declarations

extern const int stdMaxChars;
extern struct message globalMessage;