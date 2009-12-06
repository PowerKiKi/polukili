#include "quad.h"

namespace wsp{
	Quad::Quad() : Layer(),
		_rect(NULL), _rotation(0), _border(false), _borderWidth(1)
	{
		_rect = new Rectangle();
		_fillC.r = 0;
		_borderC.r = 0;
		_fillC.g = 0;
		_borderC.g = 0;
		_fillC.b = 0;
		_borderC.b = 0;
		_fillC.a = 255;
		_borderC.a = 255;
	}

	Quad::~Quad(){
		if(_rect)
			delete _rect; _rect = NULL;
	}

	void Quad::SetRectangle(Rectangle* rect){
		if(rect == NULL)return;
		SetX(rect->x);
		SetY(rect->y);
		_width = rect->width;
		_height = rect->height;
	}
	const Rectangle* Quad::GetRectangle(){
		// Now we assign our data to the rectangle and return it.
		_rect->x = GetX();
		_rect->y = GetY();
		_rect->width = _width;
		_rect->height = _height;
		return _rect;
	}

	void Quad::SetWidth(u32 width){
		_width = width;
	}
	void Quad::SetHeight(u32 height){
		_height = height;
	}
	
	void Quad::SetRotation(f32 rotation){
		_rotation = rotation;
	}
	f32 Quad::GetRotation() const{
		return _rotation;
	}

	void Quad::SetBorderWidth(u16 width){
		_borderWidth = width;
	}
	u16 Quad::GetBorderWidth() const{
		return _borderWidth;
	}

	void Quad::SetBorder(bool border){
		_border = border;
	}
	bool Quad::IsBorder() const{
		return _border;
	}

	void Quad::SetFillColor(GXColor fillColor){
		_fillC = fillColor;
	}

	void Quad::SetBorderColor(GXColor borderColor){
		_borderC = borderColor;
	}

	void Quad::Draw(f32 offsetX, f32 offsetY) const{
		// Do some checks if the quad should be drawn at all
		if(!_border && _fillC.a == 0)
			return;
		if(IsVisible() == false || _width == 0 || _height == 0 || (_fillC.a == 0 && _borderC.a == 0))
			return;

		f32 width = ((GetWidth())/2),
			height = ((GetHeight())/2);

		// Use all the position data one can get
		Mtx model, tmp;
		guMtxIdentity(model);
		guMtxRotDeg(tmp, 'z', _rotation);
		guMtxConcat(model, tmp, model);
		guMtxTransApply(model, model, GetX()+width+offsetX,GetY()+height+offsetY, 0.0f);
		guMtxConcat(model, tmp, model);
		GX_LoadPosMtxImm(model, GX_PNMTX0);

		// Turn off texturing
		GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
		GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);
	
		// Draw a Quad
		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
			GX_Position2f32(-width, -height);
			GX_Color4u8(_fillC.r, _fillC.g, _fillC.b, _fillC.a);
			GX_Position2f32(width, -height);
			GX_Color4u8(_fillC.r, _fillC.g, _fillC.b, _fillC.a);
			GX_Position2f32(width,height);
			GX_Color4u8(_fillC.r, _fillC.g, _fillC.b, _fillC.a);
			GX_Position2f32(-width,height);
			GX_Color4u8(_fillC.r, _fillC.g, _fillC.b, _fillC.a);
		GX_End();

		// Draw its border
		if(_border){
			GX_SetLineWidth(_borderWidth,GX_TO_ONE);
			GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 5); // Do it five times to get every border
				GX_Position2f32(-width, -height);
				GX_Color4u8(_borderC.r, _borderC.g, _borderC.b, _borderC.a);
				GX_Position2f32(width, -height);
				GX_Color4u8(_borderC.r, _borderC.g, _borderC.b, _borderC.a);
				GX_Position2f32(width,height);
				GX_Color4u8(_borderC.r, _borderC.g, _borderC.b, _borderC.a);
				GX_Position2f32(-width,height);
				GX_Color4u8(_borderC.r, _borderC.g, _borderC.b, _borderC.a);
				GX_Position2f32(-width, -height);
				GX_Color4u8(_borderC.r, _borderC.g, _borderC.b, _borderC.a);
			GX_End();
			GX_SetLineWidth(_borderWidth,GX_TO_ZERO);
		}

		// Turn texturing back on
		GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	}
};
