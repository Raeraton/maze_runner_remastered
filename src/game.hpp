#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>

#include "engine.hpp"
#include "map/map.hpp"


namespace game{

    struct Rendered_stuff{
        struct Ray_info{
            unsigned dist;
            map::Block hitted_block;

            Ray_info() = default;
            Ray_info(unsigned d, map::Block hb) : dist(d), hitted_block(hb) {}
        };

        std::vector<Ray_info> ray_infos;
        size_t max_dist;

        std::string to_string() const;
    };

    enum Game_event{
        NOTHING,
        WIN,
        LOOSE
    };


    class Player: public engine::Object {
        double direction = 0;

        double velocity;
        double fov;
        double rotation_speed;

    public:

        Player(
            const map::Game_map& m, const std::vector<const Object*>& ao, double x, double y, double width,
            double velocity, double fov, double rotation_speed
        ) : engine::Object( m, ao, x, y, width ), velocity(velocity), fov(fov), rotation_speed(rotation_speed) {}
        
        
        Game_event update();

        Rendered_stuff render( size_t collumns, size_t rows, double ray_res ) const;

    };

}


#endif