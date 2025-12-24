#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <cmath>
#include <vector>

#include "map/map.hpp"


namespace engine {

    class Vector2;

    class Polar{
    public:

        double len, dir;
        Polar() : len(0), dir(0) {}
        Polar( double len, double dir ): len(len), dir(dir) {}
        Polar( const Polar& oth ): len(oth.len), dir(oth.dir) {}

        explicit Polar( const Vector2& );
    };

    class Vector2{
    public:
        double x, y;
    
        Vector2() : x(0), y(0) {}
        Vector2( double x, double y ) : x(x), y(y) {}
        Vector2( const Vector2& oth ) : x(oth.x), y(oth.y) {}

        explicit Vector2( const Polar& );

        void operator+=( const Vector2& oth );
        void operator-=( const Vector2& oth );
        void operator*=( double oth );
        void operator/=( double oth );

        Vector2 operator+( const Vector2& oth ) const;
        Vector2 operator-( const Vector2& oth ) const;
        Vector2 operator*( double oth ) const;
        Vector2 operator/( double oth ) const;

    };


    class Object{
    protected:

        Vector2 m_position;
        double m_width;
        
        const map::Game_map& r_map;
        const std::vector<const Object*>& r_all_object;


    public:
        Object( const map::Game_map& m, const std::vector<const Object*>& ao )
            : m_position(), m_width(0), r_map(m), r_all_object(ao) {}
        Object(const map::Game_map& m, const std::vector<const Object*>& ao, double x, double y, double width)
            : m_position( Vector2{x, y} ), m_width(width), r_map(m), r_all_object(ao) {}
        

        map::Block move( const Vector2& );
        map::Block move( const Polar& );

        bool point_in( const Vector2& ) const;
        bool collided( const Object& ) const;


        // just for testing
        const Vector2& get_position() const { return m_position; }
        double get_width() const { return m_width; }

    };


}



#endif