#include "game.hpp"
#include "control/control.h"
#include "globals.h"

#define PI 3.14159265359
#define min(a, b) ((a>b)?b:a)

namespace game{


    Game_event Player::update(){

        int key = control::get_key();

        double dt = globals::deltatime();

        map::Block moved_to = 0;

        switch (key){
        case 'w':
            moved_to = move( engine::Polar( velocity*dt, direction ) );
            break;
        case 's':
            moved_to = move( engine::Polar( velocity*dt, direction+PI ) );
            break;
        case 'a':
            moved_to = move( engine::Polar( velocity*dt, direction-(PI/2) ) );
            break;
        case 'd':
            moved_to = move( engine::Polar( velocity*dt, direction+(PI/2) ) );
            break;
        case 'q':
            direction -= rotation_speed*dt;
            break;
        case 'e':
            direction += rotation_speed*dt;
            break;
        
        default:
            break;
        }


        for( auto obj : r_all_object ){
            if( obj == this ) continue;

            if( obj->collided(*this) ){
                return Game_event::LOOSE;
            }
        }

        if( moved_to & map::block_attributes::is_escape ){
            return Game_event::WIN;
        }

        return Game_event::NOTHING;

    }

    Rendered_stuff Player::render( size_t collumns, size_t rows, double ray_res ) const {
        
        Rendered_stuff out;
        out.ray_infos.reserve(collumns);
        out.max_dist = rows;

        double moving_dir = direction - fov/2;
        double dir_step = fov / collumns;

        for( size_t i=0;  i<collumns;  i++ ){

            engine::Vector2 ray_pos{ m_position };
            unsigned dist = 0;

            while( dist < rows  &&  !(r_map.get_block( ray_pos.x, ray_pos.y ) & map::block_attributes::blocks_light) ){
                dist++;
                ray_pos += engine::Vector2{ engine::Polar{ ray_res, moving_dir } };
            }


            // anti fish eye
            dist = static_cast<unsigned>( static_cast<double>(dist) * cos(moving_dir-direction) );
            dist = min( dist, rows-1 );

            
            map::Block ray_landed_point = r_map.get_block( ray_pos.x, ray_pos.y );
            
            out.ray_infos.emplace_back( dist, ray_landed_point );

            moving_dir += dir_step;
        }

        return out;

    }


    std::string Rendered_stuff::to_string() const {
        constexpr char wall_color[] = "\033[1;37m";
        constexpr char smoke_color[] = "\033[1;34m";
        constexpr char escape_color[] = "\033[1;33m";
        constexpr char enemy_color[] = "\033[1;31m";
        constexpr char ground_color[] = "\033[1;32m";
        constexpr char reset_color[] = "\033[0m";

        char grid[ray_infos.size()][max_dist] = {0};

        for( size_t i=0;  i<ray_infos.size();  i++ ){
            
            unsigned inverse_dist = max_dist - ray_infos[i].dist;

            unsigned sky = (max_dist - inverse_dist) / 2;
            unsigned obj = inverse_dist + sky;

            for( size_t j=0;  j<max_dist;  j++ ){
                if( j < sky ){
                    grid[i][j] = ' ';
                }else if( j < obj ){
                    grid[i][j] = '#';
                }else{
                    grid[i][j] = '.';
                }
            }

        }


        std::string out;
        const char* used_color;

        for( size_t i=0;  i<max_dist;  i++ ){
            for( size_t j=0;  j<ray_infos.size();  j++ ){
                char character = grid[j][i];

                if( character == '#' ){
                    using namespace map::block_attributes;

                    auto block = ray_infos[j].hitted_block;

                    if( block & is_escape ){
                        if( used_color != escape_color ){
                            out += escape_color;
                            used_color = escape_color;
                        }
                    }else if( block & blocks_light   &&   block & blocks_movement ){
                        if( used_color != wall_color ){
                            out += wall_color;
                            used_color = wall_color;
                        }
                    }else if( block & blocks_light  ){
                        if( used_color != smoke_color ){
                            out += smoke_color;
                            used_color = smoke_color;
                        }
                    }else{
                        if( used_color != reset_color ){
                            out += reset_color;
                            used_color = reset_color;
                        }
                    }

                }else if( character == '.' ){
                    if( used_color != ground_color ){
                        out += ground_color;
                        used_color = ground_color;
                    }
                }

                out += character;

            }
            out += '\n';
        }

        out += "\033[0m";

        return out;

    }

}