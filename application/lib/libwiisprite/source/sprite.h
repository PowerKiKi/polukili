/*
 * libwiisprite - Sprite, Rectangle
 */

#ifndef LIBWIISPRITE_SPRITE
#define LIBWIISPRITE_SPRITE

#include <stdlib.h>
#include <gccore.h>
#include "image.h"
#include "layer.h"
#include "tiledlayer.h"

//!libwiisprite namespace
namespace wsp{
	//!Basic data for a rectangle.
	struct Rectangle{
		f32 x, //!<X position.
			y; //!<Y position.
		f32 width, //!<Width of rectangle.
			height; //!<Height of rectangle.
	};

	//!Texture transformation.
	enum TRANSFORM{
		TRANS_NONE = 0, //!< No transformation.
		TRANS_MIRROR = 1, //!< Texture is mirrored.
		TRANS_BILINEAR_OFF = 2, //!< Turns off bilinear filtering for this texture.
		TRANS_ADDITIVE_BLENDING = 4 //!< Turns on additive blending. Useful for particle effects.
	};

	//!Changes how the position gets calculated for the sprite.
	enum REFPIXEL_POSITIONING{
		REFPIXEL_POS_TOPLEFT = 0, //!< Default. Sprite position is based on topleft corner.
		REFPIXEL_POS_PIXEL //!<The reference pixel is placed at the X and Y coordinates.
	};

	//!A basic drawable object with animation support.
	class Sprite : public Layer{
		public:
			//!Constructor.
			Sprite();
			//!Destructor.
			virtual ~Sprite();
			
			//!Assigns this sprite to an image.
			//!If there is already an image with the same size, no data gets changed.
			//!\param image The image for this sprite.
			//!\param frameWidth The width of the frame. Should be a multiple of image->GetWidth() or 0 if it should get the same width as the image.
			//!\param frameHeight The height of the frame. Should be a multiple of image->GetHeight() or 0 if it should get the same height as the image.
			void SetImage(Image* image, u32 frameWidth = 0, u32 frameHeight = 0);
			//!Gets the assigned image.
			//!\return A pointer to the image. NULL if no image was assigned.
			const Image* GetImage() const;
			//!Changes the transformation of the texture.
			//!\param transform The new transformation for the texture. Use the TRANSFORMATION enum members as flags, e.g. (TRANS_MIRROR | TRANS_BILINEAR_OFF)
			void SetTransform(u8 transform);
			//!Gets the texture transformation.
			//!\return The transformation of the texture as a flag.
			u8 GetTransform() const;

			//!Sets the rotation angle of the sprite.
			//!\param rotation The new angle of the sprite. It is measured in degrees/2, so if 90 degrees is wanted, 45 degrees should be the passed parameter.
			void SetRotation(f32 rotation);
			//!Gets the rotation angle of the sprite.
			//!\return The current angle of the sprite.
			f32 GetRotation() const;

			//!Sets the zooming of the sprite. It resets any defined stretch values.
			//!\param zoom The new zoom of the sprite. 1 is normal size, cannot be smaller than 0.
			void SetZoom(f32 zoom);
			//!Gets the zooming of the sprite. If StretchWidth is not the same as StretchHeight, it returns 0.
			//!\return The current zoom of the sprite. 1 is normal size.
			f32 GetZoom() const;
			//!Sets the width stretch of the sprite.
			//!\param stretchWidth Stretches the width of the sprite by this value. 1 is normal size, cannot be smaller than 0.
			void SetStretchWidth(f32 stretchWidth);
			//!Sets the height stretch of the sprite.
			//!\param stretchHeight Stretches the height of the sprite by this value. 1 is normal size, cannot be smaller than 0.
			void SetStretchHeight(f32 stretchHeight);
			//!Gets the width stretch of the sprite. Is equal to zoom value if zoom was set.
			//!\return The current width stretch of the sprite. 1 is normal size.
			f32 GetStretchWidth() const;
			//!Gets the height stretch of the sprite. Is equal to zoom vallue if zoom was set.
			//!\return The current height stretch of the sprite. 1 is normal size.
			f32 GetStretchHeight() const;

			//!Sets the transparency of the sprite. 
			//!\param alpha Sets the transparency. Has a range from 0x00 (invisible) to 0xFF (fully visible)
			void SetTransparency(u8 alpha);
			//!Gets the transparency of the sprite.
			//!\return The current transparency of the sprite. Has a range from 0x00 (invisible) to 0xFF (fully visible)
			u8 GetTransparency() const;

			//!Sets a reference pixel. The sprite rotates and zooms around this specified point. When
			//!a new image gets initialized, the refpixel is moved to the center and the positioning
			//!is REFPIXEL_POS_TOPLEFT.
			//!\param x The x position of the reference pixel.
			//!\param y The y position of the reference pixel.
			void SetRefPixelPosition(f32 x, f32 y);
			//!Allows to set the x coordinate of the reference pixel as a standalone.
			//!\param x The x position of the reference pixel.
			void SetRefPixelX(f32 x);
			//!Allows to set the y coordinate of the reference pixel as a standalone.
			//!\param y The y position of the reference pixel.
			void SetRefPixelY(f32 y);
			//!Gets the current reference pixel x coordinate.
			//!\return The x position of the reference pixel.
			f32 GetRefPixelX() const;
			//!Gets the current reference pixel y coordinate.
			//!\return The y position of the reference pixel.
			f32 GetRefPixelY() const;
			//!Sets how the sprite should react on X and Y coordinates.
			//!\param positioning Specifies the type of the positioning.
			void SetRefPixelPositioning(REFPIXEL_POSITIONING positioning);
			//!Gets the positioning.
			//!\return The current positioning of the sprite.
			REFPIXEL_POSITIONING GetRefPixelPositioning() const;

			//!Defines a collision rectangle. On startup it's the same as Image width and height.
			//!\param x Offset from the upper left corners position of the sprite.
			//!\param y Offset from the upper left corners position of the sprite.
			//!\param width The width of the collision rectangle.
			//!\param height The height of the collision rectangle.
			void DefineCollisionRectangle(f32 x, f32 y, f32 width, f32 height);
			//!Gets the current collision rectangle.
			//!\return A pointer to the rectangle.
			const Rectangle* GetCollisionRectangle() const;
			//!Checks if another rectangle collides with this sprite.
			//!\param rect The rectangle to check.
			//!\param x The position of the rectangle, since x in rectangle is only an offset.
			//!\param y The position of the rectangle, since y in rectangle is only an offset.
			//!\return true if it is colliding, false if not.
			bool CollidesWith(const Rectangle* rect, f32 x = 0, f32 y = 0) const;
			//!Checks if another sprite collides with this sprite.
			//!\param sprite The sprite to check.
			//!\param complete Set this to true, if you also want to use zoom and rotation with the collision detecting.
			//!\return true if it is colliding, false if not.
			bool CollidesWith(const Sprite* sprite, bool complete = false) const;
			//!Checks if the sprite does cross a tile on the tiledlayer which number is not 0.
			//!\param tiledlayer the tiledlayer to check.
			//!\return true if it is colliding, false if not.
			bool CollidesWith(const TiledLayer* tiledlayer) const;
			
			//!Gets the current frame of the sprite.
			//!\return The frame this sprite is at.
			//!\sa \ref sprite_sequences_page
			u32 GetFrame() const;
			//!Gets the current position of the sequence.
			//!Equals to GetFrame() if sequence was not changed.
			//!\return The current position of the sequence.
			//!\sa \ref sprite_sequences_page
			u32 GetFrameSequencePos() const;
			//!Gets how long the current frame sequence is.
			//!Same as GetRawFrameCount() if no frame sequence speficied.
			//!\sa \ref sprite_sequences_page
			u32 GetFrameSequenceLength() const;
			//!Gets how many frames there are at all.
			//!\sa \ref sprite_sequences_page
			u32 GetRawFrameCount() const;
			//!Sets the current frame to a frame at the sequence.
			//!\param sequenceIndex The index in the current frame sequence.
			//!\sa \ref sprite_sequences_page
			void SetFrame(u32 sequenceIndex);
			//!Sets the current frame to the next frame in the sequence. Goes back to the first member if no frames left in the sequence.
			//!\sa \ref sprite_sequences_page
			void NextFrame();
			//!Sets the current frame to the previous frame in the sequence. Goes to the last member if the current frame is 0.
			//!\sa \ref sprite_sequences_page
			void PrevFrame();
			//!Sets the current frame sequence.
			//!\param sequence An array with data for each sequence. Each member cannot be bigger than the maximum amount of frames.
			//!\param length The length of the sequence. Gets length amount of data.
			//!\sa \ref sprite_sequences_page
			void SetFrameSequence(u32* sequence, u32 length);

			//!Draws the Sprite.
			void Draw(f32 offsetX = 0, f32 offsetY = 0) const;
		protected:
		private:
			void _CalcFrame();

			f32 _rotation, _stretchWidth, _stretchHeight;
			u8 _alpha;
			Image* _image;
			u8 _trans;

			Rectangle* _colRect;

			u32 _frame, _frameRawCount;
			u32* _frameSeq; u32 _frameSeqLength, _frameSeqPos;
			f32 _txCoords[4];
			f32 _refPixelX, _refPixelY, _refWidth, _refHeight;
			REFPIXEL_POSITIONING _positioning;
	};
};

/*! \page sprite_sequences_page Sprite - Animation Sequences
 *  Animation sequences help the develeloper handle animations more easily.
 *
 *  Sequences are arrays of u32 variables. Each of these variables is a frame index
 *  of the sprite.
 *
 *  The starting sequence looks like this:
\verbatim
When you do NextFrame() on a Sprite which has 4 frames without modifying its
sequence, frames get changed like this:
[0] -> [1] -> [2] -> [3] -> [0] -> ...
This happens, when you do PrevFrame()
[0] -> [3] -> [2] -> [1] -> [0] -> ...
\endverbatim
 *  As you can see, it is pretty straightforward.
 *
 *  Now we assign an own sequence.\n
 *  When assigning a sequence, each of its members musn't be bigger than actual frames available,
 *  or it won't get set. So if we assign the sequence to u32 seq[6] = {0, 3, 1, 1, 2, 3}; this happens:
\verbatim
On NextFrame():
[0] -> [3] -> [1] -> [1] -> [2] -> [3] -> [0] -> ...
On PrevFrame():
[0] -> [3] -> [2] -> [1] -> [1] -> [3] -> [0] -> ...
\endverbatim
 * 
 * The sequence just keeps on looping and only changes when you assign a new one or change to an
 * Image with fewer frames than the current one. So as you may see, sequencing can help you a lot
 * with your animation needs.
 */

#endif
