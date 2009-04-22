#################################################
#                                               #
#  libwiisprite - v0.3.0b                        #
#                                               #
#################################################
#  Written by Chaosteil and Feesh!              #
#################################################

~~What is libwiisprite?~~

libwiisprite is a C++ sprite library written for the Wii which utilises
GX for all it's graphical operations, meaning the GPU is used to accelerate
graphics.

libwiisprite aims to make developing Wii homebrew simple and fun with
better graphical results than currently existing libraries.

~~Automatic Installation Instructions~~

To install libwiisprite on Linux, enter
	make linux
at the terminal, or if you use Windows, enter
	make win
at the command line.

This should install libwiisprite to the appropriate folders without any
hassle. If you have any troubles, please consider using the manual method below.

~~Manual Installation Instructions~~

You must have devkitPPC and libogc installed. Check out this link for
instructions how to do that:
http://wiibrew.org/wiki/Getting_Started_with_devkitppc

First of all change directory into the extracted libwiisprite directory.

To install libwiisprite:

	Copy ./lib/libwiisprite.a to lib/wii/ in your DevkitPPC folder
	(This could also be in the libogc folder. Make sure it has libogc.a and other files in it)
	Copy ./libwiisprite/include/*.h to include/ in your DevkitPPC folder
	(This could also be in the libogc folder. Make sure it has ogcsys.h and other files in it)


You will also need to install libpng (if you haven't already done so).

To install libpng:

	Copy ./libpng/lib/libpng.a to lib/wii/ in your DevkitPPC folder
	(This could also be the libogc folder. Make sure it has libogc.a and other files in it)
	Copy ./libpng/include/*.h to include/ in your DevkitPPC folder
	(This could also be in the libogc folder. Make sure it has ogcsys.h and other files in it)

You need also need to have access to a file system which can be accessed with fopen(). libfat is recommended and it's latest version is found in the libogc CVS repository.

~~How To Use libwiisprite In Your Project~~

When using libwiisprite, you need to alter the Makefile for your project.

Open up the Makefile, then to the LIBS variable, add -lwiisprite -lpng -lz.
(You may need to change the order of your libs to make this work correctly. Putting this at the front of your LIBS should work fine.)

If you still have problems after this, feel free to contact us with your problem. Just make sure you followed these steps precisely.

~~Sample Application~~

Here is a quick example usage of libwiisprite (it is also included in the template in the examples folder):

#include <wiiuse/wpad.h>
#include <wiisprite.h>

// libwiisprite uses wsp as it's namespace
using namespace wsp;

int main(int argc, char **argv)
{
	// Create the game window and initalise the VIDEO subsystem
	GameWindow gwd;
	gwd.InitVideo();
	
	gwd.SetBackground((GXColor){ 255, 255, 255, 255 });

	// Initialise Wiimote
	WPAD_Init();

	for(;;)
	{
		WPAD_ScanPads();
		if(WPAD_ButtonsDown(WPAD_CHAN_0)&WPAD_BUTTON_HOME)
			break;
		gwd.Flush();
	}
	return 0;
}

MAKE SURE YOU SAVE IT AS A C++ (*.cpp) FILE, OR IT WON'T WORK!

The end result of this program is a white screen. You can push the "Home"
button to exit the program.

More samples are found at the "examples" directory.

~~Getting Support~~

The library comes with documentation, but tutorials may be created.
If have made a tutorial, please contact Chaosteil or feesh at
<chaosteil@gmail.com> or <gummybassist@gmail.com>.
We will try and may link to your tutorial in later releases of the library.
