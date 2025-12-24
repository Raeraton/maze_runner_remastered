#include "map.hpp"
#include <fstream>
#include <exception>


constexpr uint8_t   NORTH = 0b1,
                    SOUTH = 0b10,
                    WEST  = 0b100,
                    EAST  = 0b1000;


int** generate_game_maze( uint64_t width, uint64_t height, int seed, uint64_t times ){
    
    typedef uint64_t num;

    srand(seed);

    auto grid = new int*[height];
    for( num i=0;  i<height;  i++ ){
        grid[i] = new int[width];

        for( num j=0;  j<width;  j++ ){
            grid[i][j] = 0;
        }
    }

    
    for( num y=0;  y<height;  y++ ){
        for( num x=0;  x<width-1;  x++ ){
            grid[y][x] = EAST;
        }
    }

    for( num y=0;  y<height-1;  y++ ){
        grid[y][width-1] = SOUTH;
    }



    
    num posx=width-1;
    num posy=height-1;



    for( uint64_t i=0;  i<times;  i++ ){

        int next_dir=0;

        while(
            (  next_dir==NORTH  &&  posy==0  ) ||
            (  next_dir==SOUTH  &&  posy==height-1  ) ||
            (  next_dir==WEST   &&  posx==0  ) ||
            (  next_dir==EAST   &&  posx==width-1) ||
            next_dir == 0
        ){
            next_dir = 1 << ( rand() % 4 );
        }

        grid[posy][posx] = next_dir;

        if( next_dir == NORTH ){ posy--; }
        else if( next_dir == SOUTH ){ posy++; }
        else if( next_dir == WEST ){ posx--; }
        else if( next_dir == EAST ){ posx++; }

    }



    return grid;
            
}




namespace map{

    constexpr uint8_t   wall = block_attributes::blocks_light | block_attributes::blocks_movement,
                        air = 0,
                        smoke = block_attributes::blocks_light,
                        barrier = block_attributes::blocks_movement,
                        escape = block_attributes::is_escape,
                        void_block = block_attributes::is_void | block_attributes::blocks_light | block_attributes::blocks_movement;


    Block block_from_char(char c){

        switch (c){
        case 'w':
            return wall;
        case 'a':
            return air;
        case 's':
            return smoke;
        case 'b':
            return barrier;
        case 'e':
            return escape;
        default:
            return void_block;
        }

    }

    char block_to_char(Block b){

        if( b == wall ) return 'w';
        if( b == air ) return 'a';
        if( b == smoke ) return 's';
        if( b == barrier ) return 'b';
        if( b == escape ) return 'e';
        
        return 'v';

    }



    Game_map& Game_map::operator=(Game_map&& oth){
        if( &oth == this ) return *this;

        delete[] m_grid;
        m_grid = oth.m_grid;

        m_width = oth.m_width;
        m_height = oth.m_height;

        oth.m_grid = nullptr;

        return *this;
    }


    Game_map Game_map::from_file( const std::string& path ){

        std::ifstream file(path);

        uint64_t wid, hei;
        file >> wid >> hei;

        auto blockBuff = new Block[wid*hei];
        for( uint64_t i=0; i<wid*hei; i++ ){
            char c;
            file >> c;
            blockBuff[i] = block_from_char(c);
        }

        file.close();

        return Game_map{
            wid, hei, blockBuff
        };


    }

    Game_map Game_map::from_seed( uint64_t width, uint64_t height, int seed ){

        auto grid = generate_game_maze(width, height, seed, 100*width*height);

        uint64_t    real_width = 2 * width + 1,
                    real_height = 2 * height + 1;
        

        auto real_grid = new Block[real_height*real_width];
        for( uint64_t i=0;  i<real_width*real_height;  i++ ){
            real_grid[i] = block_attributes::blocks_light | block_attributes::blocks_movement;
        }


        for( uint64_t y=0;  y<height;  y++ ){
            for( uint64_t x=0;  x<width;  x++ ){
                uint64_t midx = 1 + x*2;
                uint64_t midy = 1 + y*2;

                int block = grid[y][x];

                real_grid[ midx + midy*real_width ] = 0;

                if( block & NORTH )
                    real_grid[ midx + (midy-1)*real_width ] = 0;
                if( block & SOUTH )
                    real_grid[ midx + (midy+1)*real_width ] = 0;
                if( block & WEST )
                    real_grid[ midx - 1 + midy*real_width ] = 0;
                if( block & EAST )
                    real_grid[ midx + 1 + midy*real_width ] = 0;

            }
        }


        for( uint64_t i=0;  i<height;  i++ ){
            delete[] grid[i];
        } delete[] grid;


        return Game_map{ real_width, real_height, real_grid};
        
    }


    void Game_map::to_file( const std::string& path ) const {
        std::ofstream file{path};

        file << m_width << " " << m_height << '\n';

        for( uint64_t y=0;  y<m_height;  y++ ){
            for( uint64_t x=0;  x<m_width-1;  x++ ){
                file << block_to_char( get_block((int)x, (int)y) ) << " ";
            }
            file << block_to_char( get_block((int)(m_width-1), (int)y) ) << "\n";
        }

        file.close();
    }


    Block& Game_map::get_block( double x, double y ){
        if( m_grid == nullptr )
            throw std::exception();

        int ix = static_cast<int>(x) % m_width;
        int iy = static_cast<int>(y) % m_height;

        if( ix < 0 )
            ix += m_width;
        if( iy < 0 )
            iy += m_height;
        
        return m_grid[ ix+( iy*m_width ) ];
    }

    const Block& Game_map::get_block( double x, double y ) const {
        if( m_grid == nullptr )
            throw std::exception();

        int ix = static_cast<int>(x) % m_width;
        int iy = static_cast<int>(y) % m_height;

        if( ix < 0 )
            ix += m_width;
        if( iy < 0 )
            iy += m_height;
        
        return m_grid[ ix+( iy*m_width ) ];
    }

    Block& Game_map::get_block( int ix, int iy ){

        if( ix < 0 )
            ix += m_width;
        if( iy < 0 )
            iy += m_height;
        
        return m_grid[ ix+( iy*m_width ) ];
    }

    const Block& Game_map::get_block( int ix, int iy )const{

        if( ix < 0 )
            ix += m_width;
        if( iy < 0 )
            iy += m_height;
        
        return m_grid[ ix+( iy*m_width ) ];
    }

}