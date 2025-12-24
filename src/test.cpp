#include "control/control.h"
#include <iostream>




int main(){
    control::init();

    while(1){
        int lett = control::get_key();
        if( lett ) std::cout << lett << "\n";

        if( lett == 'q' ) break;
    }

}