
#include "map/map.hpp"
#include <iostream>
#include <string>


using namespace map;


int main(  ){


    Game_map map = Game_map::from_seed( 64, 96, 69 );
    for( int y=0;  y<map.height();  y++ ){
        for( int x=0;  x<map.width();  x++ ){
            std::cout << " " << block_to_char( map.get_block(x, y) ) ;
        }std::cout << "\n";
    }
    map.to_file("test.txt");


    return 0;

}