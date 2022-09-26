#include "../include/Vec2.hpp"

Vec2::Vec2(){

}

Vec2::Vec2(float x, float y){
   this -> x = x;
   this -> y = y;
}

Vec2 Vec2::operator+ (Vec2 rhs){
   return Vec2(this -> x + rhs.x, this -> y + rhs.y);
}

Vec2 Vec2::operator- (Vec2 rhs){
   return Vec2(this -> x - rhs.x, this -> y - rhs.y);
}

Vec2 Vec2::operator*(float rhs){
   return Vec2(this -> x * rhs, this -> y * rhs);
}

Vec2 Vec2::operator*(Vec2 rhs){
   return Vec2(this -> x * rhs.x, this -> y * rhs.y);
}

Vec2 operator*(float escalar, Vec2 &rhs){
   return Vec2(escalar * rhs.x, escalar * rhs.y);
}

Vec2 operator*(Vec2 const &rhs, float escalar){
   return Vec2(escalar * rhs.x, escalar * rhs.y);
}

Vec2 Vec2::operator+=(Vec2 rhs){
   *this = Vec2(this -> x + rhs.x, this -> y + rhs.y);
}

Vec2 Vec2::Rotate(float angle){
   Vec2 aux;
   float cosx = cos(angle);
   float sinx = sin(angle);

   aux.x = (this -> x*cosx) - (this -> y * sinx);
   aux.y = (this -> y*cosx) + (this -> x * sinx);

   return aux;
}

Vec2 Vec2::Normalized(){
   if(this -> x != 0 && this -> y != 0){
      return Vec2(this -> x/this -> Magnitude(), this -> y / this -> Magnitude());
   }
   return *this;
}

float Vec2::Magnitude(){
   return sqrt(pow(this -> x, 2) + pow(this -> y, 2));
}

float Vec2::anglex(){
   return atan2(this->y, this->x);
}

float Vec2::anglex2(Vec2& rhs){
   Vec2 aux = (rhs-*this);
   return atan2(aux.y, aux.x);
}

float Vec2::dist(Vec2& rhs){
   return (*this - rhs).Magnitude();
}