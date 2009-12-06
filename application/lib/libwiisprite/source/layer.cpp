#include "layer.h"

namespace wsp{
	Layer::Layer() : 
		_height(0), _width(0),
		_x(0), _y(0),
		_visible(true)	
	{
	}
	Layer::~Layer(){
	}

	u32 Layer::GetHeight() const{
		return _height;
	}
	u32 Layer::GetWidth() const{
		return _width;
	}

	f32 Layer::GetX() const{
		return _x;
	}
	f32 Layer::GetY() const{
		return _y;
	}

	bool Layer::IsVisible() const{
		return _visible;
	}
	void Layer::SetVisible(bool visible){
		_visible = visible;
	}
	
	void Layer::SetPosition(f32 x, f32 y){
		_x = x;
		_y = y;
	}
	void Layer::Move(f32 deltaX, f32 deltaY){
		_x += deltaX;
		_y += deltaY;
	}
	void Layer::SetX(f32 x){
		_x = x;
	}
	void Layer::SetX(s32 x){
		SetX((f32)x);
	}
	void Layer::SetX(u32 x){
		SetX((f32)x);
	}
	void Layer::SetY(f32 y){
		_y = y;
	}
	void Layer::SetY(s32 y){
		SetY((f32)y);
	}
	void Layer::SetY(u32 y){
		SetY((f32)y);
	}

	void Layer::Draw(f32 offsetX, f32 offsetY) const{
		// Nothing at all :)
	}
};
