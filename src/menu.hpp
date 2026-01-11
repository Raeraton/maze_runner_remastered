#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <functional>
#include <iostream>

#include "control/control.h"


int menu( const std::string& header, const std::vector<std::string>& options );

template<typename T>
T input_value( const std::string& header, std::function<bool(T)> validator ){
    bool done = false;

    T out;

    while( !done ){
        control::clear_screen();

        std::cout << header << std::flush;
        std::cin >> out;
        if( validator(out) ){
            done = true;
        }
    }

    return out;
}

template<typename T>
T input_value( const std::string& header, std::function<T()> inputter, std::function<bool(T)> validator ){
    bool done = false;

    T out;

    while( !done ){
        control::clear_screen();

        std::cout << header << std::flush;
        out = inputter();
        if( validator(out) ){
            done = true;
        }
    }

    return out;
}


#endif