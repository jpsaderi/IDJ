#include "../include/Collider.hpp"

#ifdef DEBUG
#include "../include/Game.hpp"
#include "../include/Camera.hpp"
#include "SDL_include.h"
#endif


// CoM_M_PIe o conteúdo dessa função para dentro da sua e adapte o nome das funções para as suas.
// Funções usadas:
// Rect::GetCenter()				- Retorna um Vec2 no centro do Rect
// Vec2::operator-( const Vec2& )	- Subtrai dois Vec2
// Vec2::Rotate( float rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado

void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset): Component(associated) {
	this->scale = scale;
	this->offset = offset;
}

void Collider::Start(){

}

void Collider::Update(float dt){
	box = associated.box;
	box.w *= scale.x;
    box.h *= scale.y;
    float angle = associated.angleDeg*(M_PI/180);
    Vec2 offsetRotated = offset.Rotate(angle);
    box.x = (box.GetCenter().x + offsetRotated.x)-box.w/2;
    box.y = (box.GetCenter().y + offsetRotated.y)-box.h/2;
}

bool Collider::Is(string type){
	return type == "Collider";
}

void Collider::NotifyCollision(GameObject& other) {

}

void Collider::SetScale(Vec2 scale){
	this -> scale = scale;
}

void Collider::SetOffset(Vec2 offset){
	this -> offset = offset;
}

bool Collider::IsColliding(Collider other){
	float angle1 = associated.angleDeg*(M_PI/180);
	float angle2 = other.associated.angleDeg*(M_PI/180);
	Rect box2 = other.box;
	return Collision::IsColliding(box, box2, angle1, angle2);
}