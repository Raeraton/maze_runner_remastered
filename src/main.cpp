#include "control/control.h"
#include "gameloop.h"
#include "menu.hpp"

#define rad_p_deg 0.0174532925

int main(){
    control::init();

    
    uint64_t width = 8;
    uint64_t height = 8;
    int seed = 1;
    double velocity = 0.25;
    double fov = 70;
    double rotation_speed = 15;

    bool running = true;
    while( running ){
        
        int opt = menu( "Main Menu", { "Start Game", "Settings", "Exit" } );
        
        switch( opt ){
            case 0:

                opt = start_game( width, height, seed, velocity, fov*rad_p_deg, rotation_speed*rad_p_deg );
                if( opt == 1 ){
                    std::cout << "You win!\n";
                } else if( opt == 2 ){
                    std::cout << "You lose!\n";
                }

                break;
            case 1:
                
                while( opt != 6 ){
                    opt = menu( "Settings", {
                         "Width: " + std::to_string(width),
                         "Height: " + std::to_string(height),
                         "Seed: " + std::to_string(seed),
                         "Velocity: " + std::to_string(velocity),
                         "FOV: " + std::to_string(fov),
                         "Rotation Speed: " + std::to_string(rotation_speed),
                         "Back" } );

                    switch( opt ){
                        case 0:
                            width = input_value<uint64_t>( "Enter width: ", [](uint64_t v){ return v >= 1 && v <= 1024; } );
                            break;
                        case 1:
                            height = input_value<uint64_t>( "Enter height: ", [](uint64_t v){ return v >= 1 && v <= 1024; } );
                            break;
                        case 2:
                            seed = input_value<int>( "Enter seed: ", [](int v){ return true; } );
                            break;
                        case 3:
                            velocity = input_value<double>( "Enter velocity: ", [](double v){ return v > 0.0 && v <= 10.0; } );
                            break;
                        case 4:
                            fov = input_value<double>( "Enter FOV: ", [](double v){ return v > 0.0 && v <= 3.14; } );
                            break;
                        case 5:
                            rotation_speed = input_value<double>( "Enter rotation speed: ", [](double v){ return v > 0.0 && v <= 10.0; } );
                            break;
                    }
                }

                break;
            case 2:
                running = false;
                break;
        }

    }


}