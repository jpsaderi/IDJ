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

Vec2 Vec2::operator+=(Vec2 rhs){
   *this = Vec2(this -> x + rhs.x, this -> y + rhs.y);
}

Vec2 Vec2::GetRotated(float angle){
   Vec2 aux;
   float cosx = cos(angle);
   float sinx = sin(angle);

   aux.x = (this -> x*cosx) - (this -> y * sinx);
   aux.y = (this -> y*cosx) - (this -> x * sinx);

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