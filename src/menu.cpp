#include "menu.hpp"


int menu( const std::string& header, const std::vector<std::string>& options ){
    // assume options is non-empty  and  options.size() < INT_MAX/1024
    int selected = 1024 * options.size();   //  selected * options.size()  == 0

    while( true ){
        control::clear_screen();

        std::cout << header << "\n";

        for( size_t i = 0; i < options.size(); i++ ){
            if( i == abs( selected % options.size() ) ){
                std::cout << ">    " << options[i] << "\n";
            } else {
                std::cout << "     " << options[i] << "\n";
            }
        }

        int key = control::get_key();

        if( key == 'w' || key == 'W' || key == 72 ){ // up
            selected--;
        } else if( key == 's' || key == 'S' || key == 80 ){ // down
            selected++;
        } else if( key == '\n' || key == '\r' || key == 13 ){ // enter
            return abs( selected % options.size() );
        }
    }

    return -1;
}