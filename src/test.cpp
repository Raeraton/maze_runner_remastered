#include "control/control.h"
#include <iostream>

#include "engine.hpp"

#define PI 3.14159265359


std::ostream& operator<<( std::ostream& out, const engine::Polar& p ){
    out << "{ len:" << p.len << ", dir:" << p.dir*57.2957795 << " }";
    return out;
}

std::ostream& operator<<( std::ostream& out, const engine::Vector2& v ){
    out << "{ x:" << v.x << ", y:" << v.y << " }";
    return out;
}

std::ostream& operator<<( std::ostream& out, const engine::Object& o ){
    out << "{ pos:" << o.get_position() << ", width:" << o.get_width() << " }";
    return out;
}




void test_control(){

    std::cout << "=============== test controls\n";

    control::init();

    while(1){
        int lett = control::get_key();
        if( lett ) std::cout << lett << "\n";

        if( lett == 'q' ) break;
    }

}


void test_engine_coord(){

    using namespace engine;

    std::cout << "=============== test engine coord\n";

    Polar p1{ sqrt(2), PI/4 };
    Vector2 v1{p1};
    std::cout << p1 << " " << v1 <<'\n';
    
    Vector2 v2{ 0.5, 0.86602540378 };
    Polar p2{v2};
    std::cout << v2 << " " << p2 <<'\n';

    Vector2 a{1, 2}, b{3, 4}, c{5, 2};

    std::cout << a << " + " << b << " = " << a+b << "\n";
    std::cout << a << " - " << b << " = " << a-b << "\n";
    std::cout << a << " + " << c << " = " << a+c << "\n";
    std::cout << a << " - " << b << " + " << c << " = " << a-b+c << "\n";

    double l1 = 2;
    double l2 = 3;

    std::cout << a << " * " << l1 << " = " << a*l1 << '\n';
    std::cout << a << " * " << l2 << " = " << a*l2 << '\n';
    std::cout << a << " / " << l1 << " = " << a/l1 << '\n';
    std::cout << a << " / " << l2 << " = " << a/l2 << '\n';
    

}


void test_object(){

    using namespace engine;

    std::cout << "=============== test object\n";

    std::vector<const Object*> objects;
    map::Game_map map = map::Game_map::from_seed(5, 5, 69);

    Object o1{map, objects, 1.2, 1.2, 0.1};
    Object o2{map, objects, 1.8, 1.8, 0.1};

    objects.push_back(&o1);
    objects.push_back(&o2);

    std::cout << "o1: " << o1 << "\no2: " << o2 << "\n";

    for( int i=0;  i<10;  i++ ){
        o2.move(Vector2{-0.1, -0.1});
        std::cout << "o1: " << o1 << "\no2: " << o2 << "\n";
    }

    Vector2 v1{1.19, 1.19};
    Vector2 v2{1.33, 1.33};

    std::cout << v1 << " in " << o1 << " -> " << o1.point_in(v1) << '\n';
    std::cout << v2 << " in " << o1 << " -> " << o1.point_in(v2) << '\n';
    std::cout << v1 << " in " << o2 << " -> " << o2.point_in(v1) << '\n';
    std::cout << v2 << " in " << o2 << " -> " << o2.point_in(v2) << '\n';

}

void test_color(){
    std::cout << "=============== test color\n";

    char c[] = "\033[0;31m";

    std::string s = "Hello";
    s += c;
    s += " hello";

    std::cout << s << "\n\033[0m";

}


int main(){

    test_color();

    test_engine_coord();

    test_object();

    test_control();


}
