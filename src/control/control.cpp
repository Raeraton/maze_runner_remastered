#include "control.h"

#ifdef WIN32
#include <conio.h>

namespace control{
    void init(){}

    int get_key(){
        if( kbhit() )
            return getch();
        
        return 0;
    }

    void clear_screen(){
        system("cls");
    }
}

#else
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>



namespace control{

    struct termios orig_termios;

    void disableRawMode() {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }

    void init(){
        tcgetattr(STDIN_FILENO, &orig_termios);
        atexit(disableRawMode);
        struct termios raw = orig_termios;
        raw.c_lflag &= ~(ECHO | ICANON | ISIG);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

    int get_key(){
        char c = '\0';
        read(STDIN_FILENO, &c, 1);

        return c;
    }

    void clear_screen(){
        system( "clear" );
    }

}

#endif