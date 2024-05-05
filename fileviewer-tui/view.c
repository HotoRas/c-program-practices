#include "view.h"

int main(int argc, char **argv) {
    FILE *pFile;
    int i;
    int options;

    if(argc == 1) {
        return getHelp();
    }
    if(argv[1] == "--help") {
        return getHelp();
    }

    for(int i=1; i<argc; i++) {
        if(argc[i][0] == '-' && argc[i][1] == '-') {
            options |= getOptions(argc[i],argc[i+1]);
        }
    }

    /*set video mode*/
    if (_setvideomode(_TEXTC80) == 0) {
        fputs("cannot set video mode", stderr);
        fputc('\n', stderr);
        return _ERR_VIDEO_MODE
    };

    /* read */

    for(i=1;i<argc;i++){
        pFile = fopen(argv[i],"r");
        if(pFile){
            view(pFile,argv[i],options & haslinenum);
            fclose(pFile);
        }
    }
    /*done*/
    _setvideomode(_DEFAULTMODE);
    return 0;
}

void view(FILE *in, const char* name, const int haslinenum){
    char text[80];

    int line=1;
    cls();

    while((fgets(text,80,in))!=NULL) {
        _settextposition(line,1);
        _outtext(text);

        line++;
        if(line=25){
            if (pause(name) == 27) {
                return;
            }
            cls(); line=1;
        }
    }
    pause("[end]");
}

void cls(){
    _settextcolor(7); _setbkcolor(1); _settextwindow(1,1,25,80); _clearscreen(_GWINDOW);
}

int pause(const char* str){
    int key;

    _settextcolor(15); _setbkcolor(3); _settextwindow(25,1,25,80);
    _clearscreen(_GWINDOW);

    _settextposition(25,1);

    _outtext(str);

    key=getch();
    if(key==0){
        getch();
    }

    return key;
}

int getOptions(const char* command, const char* value) {
    if (command == "--showLineNumbers") {
        if (getTrue(value) == 1) {
            return 1;
        }
    }

    return 0;
}