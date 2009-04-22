/*
 * libwiisprite - GameWindow
 */

#ifndef LIBWIISPRITE_GAMEWINDOW
#define LIBWIISRPITE_GAMEWINDOW

#include <stdlib.h>
#include <gccore.h>
#include "image.h"

//!libwiisprite namespace
namespace wsp{
	//!Basic rendering unit.
	class GameWindow{
		public:
			//!Constructor.
			GameWindow();
			//!Destructor. Does call StopVideo() automatically.
			virtual ~GameWindow();

			//!Initializes the whole video subsystem.
			//!Should be the first command called with the library.
			void InitVideo();
			//!Shuts the video subsystem down. It won't work if Video wasn't initialized before.
			void StopVideo();
			//!Checks if the video subsystem is already initialized.
			//!\return true if initialized, false if not.
			static bool IsInitialized();
			//!Sets the background clear color
			//!\param bgcolor is a GXColor containing r, g, b and a.
			void SetBackground(GXColor bgcolor);
			//!Finishes rendering.
			void Flush();

			//!Gets the width of the screen.
			//!\return The width of the screen if intialized. 0 if the video subsystem is not initialized. 
			static u32 GetWidth();
			//!Gets the height of the screen.
			//!\return The height of the screen if intialized. 0 if the video subsystem is not initialized. 
			static u32 GetHeight();
		protected:
		private:
			void* _frameBuffer[2]; u32 _fb;
			bool _first;
			GXRModeObj* _rmode;
			void* _gp_fifo;
			static u32 _width, _height;
			static bool _initialized;
			static Image* _lastimage;
			static bool _lastimagebilinear;

		friend class Image; // Lets image access the _lastimage and _lastimagebilinear member.
	};
};

/*! \mainpage libwiisprite Documentation
 * \image html libwiisprite.png
 * \section intro_sec Introduction
 *
 * libwiisprite is a sprite library, created to help developers make homebrew games
 * and applications for the Wii. It was coded in C++ and makes good use of OOP concepts.
 *
 * libwiisprite makes it easy and fun to make games for the Wii.
 *
 * \section Quickstart
 * Just browse the Classes from the menu above. To add all of them to your project with
 * one command, use
\code
#include <wiisprite.h>
\endcode
 *
 * If you want to start as soon as possible, use the template example in the libwiisprite/examples folder as your base, and check out the spritetest and invaders examples. These will help you understand the concepts of this library.
 *
 * \section concepts_sec Explanations
 * This is for quick explaining what we mean with all these terms we use throughout the
 * library. They can help you get started on the more "advanced" features of this library.
 *
 * \ref global_coord_page\n 
 * \ref image_loadbuffer_page\n
 * \ref layermanager_append_page\n
 * \ref layermanager_viewwindows_page\n
 * \ref sprite_sequences_page\n
 * \ref tiledlayer_animations_page\n
 *
 * \section contact_sec Contact
 *
 * If you have any suggestions for the library or documentation, please mail
 * Chaosteil [at] gmail [dot] com or gummybassist [at] gmail [dot] com.
 * We are also happy to help with most of the problems that aren't explained in this
 * documentation.
 *
*/
/*! \page global_coord_page Global - Coordinate system
 * The coordinate system are the X and Y positions on the screen and in which direction everything
 * goes. It is a two dimensional (2D) cartesian coordinate system with inverted vertical axis.
 *
 * This snippet explains it in a simple way:
 \verbatim
 Coordinates:
 .------------> X (640, horizontal)
 |
 |
 |    Coordinate system starts at (0;0).
 |
 |
 V Y (480, vertical)
 \endverbatim
 * The top left is (0;0), the bottom right is (640;480). Of course the positions
 * can also be negative or bigger than said bottom right corner.
 */

#endif
