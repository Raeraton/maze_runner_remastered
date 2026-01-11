#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <cstdint>

// 1 win, 2 loose
int start_game( uint64_t width, uint64_t height, int seed, double velocity, double fov, double rotation_speed );


#endif