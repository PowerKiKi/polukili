/*
	Wiisprite API Example by Feesh!
	Invaders... Possibly from Space!
*/


#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <wiisprite.h>

#include "engine.h"

using namespace wsp;

bool quit = false;

void ScanPADSandReset(void)
{
   PAD_ScanPads();
   WPAD_ScanPads();
	if(PAD_ButtonsDown(0)&PAD_TRIGGER_Z || WPAD_ButtonsDown(0)&WPAD_BUTTON_HOME)
	{
		quit = true;
	}
	if(!((*(u32*)0xCC003000)>>16))
	{
		quit = true;
	}
}


int main(int argc, char **argv)
{
	GameWindow gw;
	PAD_Init();
	WPAD_Init();
	gw.InitVideo();
	Quad fade;
	fade.SetWidth(640); // Used at the end of the prog
	fade.SetHeight(480);
	GXColor fade_col = { 0,0,0,0 };
	fatInitDefault();

	Engine engine;

	for(;;)
	{
		ScanPADSandReset();
		engine.update();
		if(quit)
		{
			if(fade_col.a<255)
			{
				fade_col.a+=5;
			}
			fade.SetFillColor(fade_col);
			fade.Draw();
			if(fade_col.a==255)
				break;
		}
		gw.Flush();
	}
	return 0;
}
