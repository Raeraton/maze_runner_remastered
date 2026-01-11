#include "gameloop.h"
#include "map/map.hpp"
#include "game.hpp"
#include "globals.h"
#include "control/control.h"

#include <chrono>
#include <iostream>


int gameloop( map::Game_map& map, double velocity, double fov, double rotation_speed ){
    
    map.to_file("map.txt");

    std::vector<const engine::Object*> all_object;

    // after all_object, x, y width, velocity, fov, rotation_speed (magic numbers for testing/production xd)
    game::Player player{map, all_object, 1.5, 1.5, 0.5, velocity, fov, rotation_speed};


    game::Game_event event = game::Game_event::NOTHING;


    while( event == game::Game_event::NOTHING ){

        event = player.update();

        control::clear_screen();
        std::cout << player.render( 128, 32, 0.1 ).to_string();

    }

}


int start_game( uint64_t width, uint64_t height, int seed, double velocity, double fov, double rotation_speed){
    map::Game_map map = map::Game_map::from_seed( width, height, seed );
    return gameloop( map, velocity, fov, rotation_speed );
}