#include "engine.hpp"


namespace engine{


    Polar::Polar( const Vector2& v ){
        len = sqrt( v.x*v.x  +  v.y*v.y );
        dir = atan2(v.y, v.x);
    }

    Vector2::Vector2( const Polar& p ){
        x = p.len * cos(p.dir);
        y = p.len * sin(p.dir);
    }

    void Vector2::operator+=( const Vector2& oth ){
        x += oth.x;
        y += oth.y;
    }
    void Vector2::operator-=( const Vector2& oth ){
        x -= oth.x;
        y -= oth.y;
    }
    void Vector2::operator*=( double oth ){
        x *= oth;
        y *= oth;
    }
    void Vector2::operator/=( double oth ){
        x /= oth;
        y /= oth;
    }

    Vector2 Vector2::operator+( const Vector2& oth ) const {
        Vector2 out{*this};
        out += oth;
        return out;
    }
    Vector2 Vector2::operator-( const Vector2& oth ) const {
        Vector2 out{*this};
        out -= oth;
        return out;
    }
    Vector2 Vector2::operator*( double oth ) const {
        Vector2 out{*this};
        out *= oth;
        return out;
    }
    Vector2 Vector2::operator/( double oth ) const{
        Vector2 out{*this};
        out /= oth;
        return out;
    }







    map::Block Object::move( const Vector2& vec ){
        Vector2 temp = m_position + vec;

        auto out = r_map.get_block( temp.x, temp.y );

        for( const Object* object : r_all_object ){
            if( object == this ) continue;

            if( object->point_in( temp ) )
                return out;
        }

        if( r_map.get_block( temp.x, temp.y ) & map::block_attributes::blocks_movement ){
            return out;
        }

        m_position = temp;

        return out;

    }

    map::Block Object::move( const Polar& polar ){
        return move(Vector2{polar});
    }

    bool Object::point_in( const Vector2& p ) const {
        auto diff = m_position - p;
        double dist = sqrt( diff.x*diff.x  +  diff.y*diff.y );

        return dist < m_width;

    }
    bool Object::collided( const Object& oth ) const {
        auto diff = m_position - oth.m_position;
        double dist = sqrt( diff.x*diff.x  +  diff.y*diff.y );

        return dist < (m_width + oth.m_width);
    }
    


};