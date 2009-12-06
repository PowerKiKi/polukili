/*
 * libwiisprite - Layer
 */

#ifndef LIBWIISPRITE_LAYER
#define LIBWIISPRITE_LAYER

#include <stdlib.h>
#include <gccore.h>

//!libwiisprite namespace
namespace wsp{
	//!Drawable objects should derive from this class. Layers can be managed by LayerManagers.
	class Layer{
		public:
			//Constructor.
			Layer();
			//Destructor.
			virtual ~Layer();

			//!Gets the height of the layer.
			//!\return the current height of this layer.
			u32 GetHeight() const;
			//!Gets the width of the layer.
			//!\return the current width of this layer.
			u32 GetWidth() const;

			//!Gets the X position on the viewport.
			//!\return The X position.
			f32 GetX() const;
			//!Gets the Y position on the viewport.
			//!\return The Y position.
			f32 GetY() const;
		
			//!Checks if the layer is visible. Is visible by default.
			//!\return true if it is visible, false if not.
			bool IsVisible() const;
			//!Changes the visibility of the layer.
			//!\param visible true for show, false for hide.
			void SetVisible(bool visible);

			//!Changes the absolute position of the layer on the viewport.
			//!\param x The new X position.
			//!\param y The new Y position.
			void SetPosition(f32 x, f32 y);
			//!Moves the layer some units.
			//!\param deltaX Moves the layer a specific amount of units to the left/right.
			//!\param deltaY Moves the layer a specific amount of units up/down.
			void Move(f32 deltaX, f32 deltaY);
			//!Sets the X position on the viewport.
			//!\param x The new X position of this layer.
			void SetX(f32 x);
			//!\overload
			//!\param x The new X position of this layer.
			void SetX(s32 x);
			//!\overload
			//!\param x The new X position of this layer.
			void SetX(u32 x);
			//!Sets the Y position on the viewport.
			//!\param y The new Y position of this layer.
			void SetY(f32 y);
			//!\overload
			//!\param y The new Y position of this layer.
			void SetY(s32 y);
			//!\overload
			//!\param y The new Y position of this layer.
			void SetY(u32 y);
			
			//!Overloadable method. Here should drawing code be.
			//!\param offsetX Additional offset for the X position where to draw the layer.
			//!\param offsetY Additional offset for the Y position where to draw the layer.
			virtual void Draw(f32 offsetX = 0, f32 offsetY = 0) const;
		protected:
			u32 _height, //!< Height of the Layer.
				_width; //!< Width of the Layer.
		private:
			f32 _x, _y;
			bool _visible;
	};
};

#endif
