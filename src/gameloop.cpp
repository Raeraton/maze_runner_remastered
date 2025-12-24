#include "gameloop.h"
#include "map/map.hpp"
#include "game.hpp"
#include "globals.h"
#include "control/control.h"

#include <chrono>
#include <iostream>

#include <thread>




int gameloop(){
    
    map::Game_map map = map::Game_map::from_seed(5, 5, 69);
    std::vector<const engine::Object*> all_object;

    game::Player player{map, all_object, 1.5, 1.5, 0.5, 0.3, 0.8, 1};


    game::Game_event event = game::Game_event::NOTHING;

    auto time_point = std::chrono::high_resolution_clock::now();
    while( event == game::Game_event::NOTHING ){

        event = player.update();

        control::clear_screen();
        std::cout << player.render( 64, 24, 0.1 ).to_string();

        std::this_thread::sleep_for( std::chrono::milliseconds(10) );

        auto temp = std::chrono::high_resolution_clock::now();
        globals::deltatime() = std::chrono::duration<double>(   temp - time_point   ).count();
        time_point = temp;
    }

}