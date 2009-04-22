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
