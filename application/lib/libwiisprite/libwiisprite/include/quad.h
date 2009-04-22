/*
 * libwiisprite - Quad
 */

#ifndef LIBWIISPRITE_QUAD
#define LIBWIISPRITE_QUAD

#include <stdlib.h>
#include <gccore.h>

#include "layer.h"
#include "sprite.h"

//!libwiisprite namespace
namespace wsp{
	//!Capable of drawing a rectangle on screen.
	class Quad : public Layer {
		public:
			//!Constructor.
			Quad();
			//!Destructor.
			virtual ~Quad();

			//!Allows to apply data from a rectangle to this quad.
			//!\param rect A pointer to the rectangle from which the data should be applied to this quad.
			void SetRectangle(Rectangle* rect);
			//!Returns a rectangle with the data of the quad. X and Y aren't offsets, but
			//!actual coordinates of the quad.
			//!\return A rectangle with the current data.
			const Rectangle* GetRectangle();

			//!Sets the width of the quad.
			//!\param width The new width of the quad.
			void SetWidth(u32 width);
			//!Seets the height of the quad.
			//!\param height The new height of the quad.
			void SetHeight(u32 height);

			//!Sets the rotation angle of the quad.
			//!\param rotation The new angle of the quad. It is measured in degrees/2, so if 90 degrees is wanted, 45 degrees should be the passed parameter.
			void SetRotation(f32 rotation);
			//!Gets the rotation angle of the quad.
			//!\return The current angle of the quad.
			f32 GetRotation() const;

			//!Sets the border width of the quad.
			//!\param width The new border width of the quad.
			void SetBorderWidth(u16 width);
			//!Gets the border width of the quad.
			//!\return The current border width of the quad.
			u16 GetBorderWidth() const;

			//!Turns the border of the quad on or off.
			//!\param border Set to true if the quad should have border, false if not.
			void SetBorder(bool border);
			//!Returns the current state of the broder.
			//!\return True if there is a border set, false if not.
			bool IsBorder() const;

			//!Sets the color of the quad. Initial color is black.
			//!\param fillColor A GXColor with the desired data.
			void SetFillColor(GXColor fillColor);
			//!Sets the color of the border of the quad. Initial color is black.
			//!\param borderColor A GXColor with the desired data.
			void SetBorderColor(GXColor borderColor);

			//!Draws the quad.
			void Draw(f32 offsetX = 0, f32 offsetY = 0) const;
		protected:
		private:
			Rectangle* _rect;
			f32 _rotation;
			bool _border;
			u16 _borderWidth;
			GXColor _fillC, _borderC;
	};
};

#endif
