/*
 * libwiisprite - Image
 */

#ifndef LIBWIISPRITE_IMAGE
#define LIBWIISPRITE_IMAGE

#include <stdlib.h>
#include <gccore.h>
#include <png.h>

//!libwiisprite namespace
namespace wsp{
	
	//!Error codes when loading images.
	enum IMG_LOAD_ERROR{
		IMG_LOAD_ERROR_NONE = 0, //!< Image successfully loaded.
		IMG_LOAD_ERROR_NOT_FOUND, //!< File was not found.
		IMG_LOAD_ERROR_INV_PNG, //!< Invalid PNG header.
		IMG_LOAD_ERROR_PNG_FAIL, //!< Invalid PNG data.
		IMG_LOAD_ERROR_WRONG_SIZE, //!< The images width and height should both be a multiple of 4.
		IMG_LOAD_ERROR_ALREADY_INIT //!< Returns this if the image was already initialized.
	};

	//!Specifies how to load the image.
	enum IMG_LOAD_TYPE{
		IMG_LOAD_TYPE_PATH = 0, //!< Loads the image from a path on the filesystem.
		IMG_LOAD_TYPE_BUFFER //!< Loads the image from the provided buffer.
	};

	//!Stores imagedata and is capable of loading pngs.
	class Image{
		public:
			//!Constructor.
			Image();
			//!Destructor.
			virtual ~Image();

			//!Loads an image from a file. Width and height have to be a multiple of 4, or it won't load.
			//!Once an Image is initialized, it can't be initialized again.
			//!Uses fopen(), so some basic filesystem initialization is required.
			//!\param path The path to the file.
			//!\param loadtype Set this to how you want to load this image. (This is probably a path)
			//!\return An error code based on loading status.
			//!\sa \ref image_loadbuffer_page
			IMG_LOAD_ERROR LoadImage(const char* path, IMG_LOAD_TYPE loadtype = IMG_LOAD_TYPE_PATH);
			//!\overload
			//!\param path The path to the file. (This is probably a buffer)
			//!\param loadtype Set this to how you want to load this image.
			//!\sa \ref image_loadbuffer_page
			IMG_LOAD_ERROR LoadImage(const unsigned char* path, IMG_LOAD_TYPE loadtype = IMG_LOAD_TYPE_BUFFER);
			
			//!Cleans up the image to be able to reload it again.
			void DestroyImage();
			//!Gets the width of this image.
			//!\return The width of the image. Returns 0 if no image is loaded.
			u32 GetWidth() const;
			//!Gets the height of this image.
			//!\return The height of the image. Returns 0 if no image is loaded.
			u32 GetHeight() const;
	
			//!Checks if the image is loaded.
			//!\return true if an image is stored, false if not.
			bool IsInitialized() const;

			//!Used to select this image for the next texturing process.
			//!Most of the time you won't gonna use this.
			//!\param bilinear Turns on bilinear filtering.
			void BindTexture(bool bilinear = true);
		protected:
			//!Initializes a clear image to draw on. It will be displayed as an RGBA8 texture, so its format should be ARGB. Don't mess with it if you don't know what you're doing.
			//!Once an Image is initialized, it can't be initialized again.
			//!\param width The new width of the image.
			//!\param height The new height of the image.
			//!\return True if it was successfully initialized, false if not.
			bool _InitializeImage(u32 width, u32 height);
			//!Use this method if you've drawn something in the pixeldata.
			void _Flush();

			u8* _pixels; //!< Stores the pixeldata of this image. Use carefully.
		private:
			void _ConvertTexture(png_byte color_type, png_bytep* row_pointers);
			
			u32 _width, _height;
			bool _initialized;
			GXTexObj _texObj;
	};
};

/*! \page image_loadbuffer_page Image - Loading from buffer
 * \section image_loadbuffer_intro_sec Intro
 * Most of the time you'll want to load an image from the SD card. This is done easily by just specifying
 * the path of the image based on the location of the boot.[dol|elf| file. That means, if your boot file
 * is in /apps/foo and your image is /apps/foo/bar.png, then
\code
image.LoadImage("/apps/foo/bar.png");
\endcode
 * equals to
\code
image.LoadImage("bar.png");
\endcode
 * 
 * If you're using wiiload, think that the boot file is running from root.
 *
 * There are some situations however, where you want to load from a buffer. Say, you have a very small
 * application you just want to run very fast. Or maybe you have your own package system where you
 * can extract each file with its own buffer. Anyway, you will need a way to load an image directly,
 * and not through the filesystem.
 *
 * \section image_loadbuffer_preparing_sec Preparing the image
 * If you have your own method for loading something into an unsigned char array, skip this section.
 *
 * Since you are using devkit, there are some nice tools for you already available. If you look into
 * the devkitPPC/bin folder, there is a tool called raw2c. It can convert any file to a unsigned char
 * buffer. We're going to use this tool. To use it, simply specify you image as an argument when starting
 * the program. Or you could just drag and drop your image onto it. Either way you are presented with
 * a *.c and *.h file. Copy these files into your source folder and include the header file at the
 * point where you want to have access to it. The header file will have one unsigned char[] member,
 * which we will are going to use for loading.
 *
 * \section image_loadbuffer_loading_sec Loading the buffer
 * libwiisprite assumes that if you're loading a unsigned char array, that it's a buffer. If you're
 * just entering a simple char array ("foo/bar.png") it will assume that it's loading from a path.
 * You can take control over this behaviour with IMG_LOAD_TYPE.
 *
 * Let's say you converted bar.png with raw2c and included the header file in your source.
 * Now you just need to type the command
\code
image.LoadImage(bar);
\endcode
 * and it should load just fine!
 *
 */

#endif
