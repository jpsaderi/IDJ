#include "../include/Rect.hpp"

Rect::Rect(){

}

Rect::Rect(float x, float y, float w, float h){
    this -> x = x;
    this -> y = y;
    this -> w = w;
    this -> h = h;
}

Rect Rect::operator+(Vec2 rhs){
    return Rect(this -> x + rhs.x, this -> y + rhs.y, this -> w, this -> h);
}

bool Rect::Contains(Vec2 rhs){
    if(((rhs.x > this -> x) && (rhs.x < (this -> x + this -> w))) && ((rhs.y > this -> y) && (rhs.y < (this -> y + this -> h)))){
        return true;
    }
    return false;
}