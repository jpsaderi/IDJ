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

Rect operator+(Vec2 vect, Rect rect){
    return Rect(vect.x + rect.x, vect.y + rect.y, rect.w, rect.h);
}

bool Rect::Contains(Vec2 rhs){
    if(((rhs.x > this -> x) && (rhs.x < (this -> x + this -> w))) && ((rhs.y > this -> y) && (rhs.y < (this -> y + this -> h)))){
        return true;
    }
    return false;
}

Vec2 Rect::GetCenter(){
    return Vec2((this -> x + this -> w/2), (this -> y + this -> h/2));
}