#include <stdio.h>
#include <conio.h>
#include <graph.h>

#define _ERR_VIDEO_MODE 1
#define _SHOW_LINE_NUM 1

int main(int argc, char **argv);
void view(FILE *in, const char* name, const int haslinenum);
void cls();
int pause(const char* str);

int getHelp();
int getOptions(const char* command, const char* value);