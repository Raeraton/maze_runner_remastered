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

    void init(){
        tcgetattr(STDIN_FILENO, &orig_termios);
    
        struct termios raw = orig_termios;
        
        raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
        //raw.c_oflag &= ~(OPOST);
        raw.c_cflag |= (CS8);
        raw.c_lflag &= ~(ECHO | ICANON | IEXTEN );
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 1;
        
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

    int get_key(){
        char c = '\0';
        read(STDIN_FILENO, &c, 1);

        char _[64];
        while( read(STDIN_FILENO, &_, 64) == 64 );

        return c;
    }

    void clear_screen(){
        system( "clear" );
    }

}

#endif