#ifndef MAP_H
#define MAP_H

#include <cstdint>
#include <string>


namespace map{


    typedef uint8_t Block;
    namespace block_attributes{
        constexpr uint8_t blocks_movement       = 0b1;
        constexpr uint8_t blocks_light          = 0b10;
        constexpr uint8_t is_void               = 0b100;
        constexpr uint8_t is_escape             = 0b1000;
    }

    Block block_from_char(char c);
    char block_to_char(Block);


    class Game_map{
        
        uint64_t m_width, m_height;
        Block* m_grid;

        Game_map( uint64_t width, uint64_t height, Block* gr ) :
            m_width(width), m_height(height), m_grid(gr)
        {}

    public:

        Game_map() : m_width(0), m_height(0), m_grid(nullptr) {}
        Game_map( const Game_map& ) = delete;
        Game_map( Game_map&& oth ) : m_width(oth.m_width), m_height(oth.m_height), m_grid(oth.m_grid) { oth.m_grid = nullptr; }
        ~Game_map(){ delete[] m_grid; }

        Game_map& operator=(Game_map&& oth);


        static Game_map from_file( const std::string& path );
        static Game_map from_seed( uint64_t w, uint64_t h, int seed );

        void to_file( const std::string& path ) const;

        

        inline uint64_t width(){ return m_width; }
        inline uint64_t height(){ return m_height; }

        Block& get_block( double x, double y );
        const Block& get_block( double x, double y ) const;

        Block& get_block( int x, int y );
        const Block& get_block( int x, int y )const;

    };


}


#endif