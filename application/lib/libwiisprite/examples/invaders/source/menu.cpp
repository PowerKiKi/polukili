#include <stdlib.h>
#include <ogcsys.h>
#include <gccore.h>
#include "menu.h"
#include "engine.h"


#include <ogc/lwp_watchdog.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include <wiisprite.h>

using namespace wsp;

Menu::Menu() : menu_sel(0), menu_bg(new Sprite()), cursor(new Sprite), last_time(ticks_to_millisecs(gettime()))
{
	set_alive(true);
	Image *bg = new Image();
	bg->LoadImage("data/menu.png");
	Image *cursor_img = new Image();
	cursor_img->LoadImage("data/cursor.png");

	menu_bg->SetImage(bg);
	cursor->SetImage(cursor_img,32,32);
	
	menu_bg->SetPosition(320-bg->GetWidth()/2,440-bg->GetHeight());
	cursor->SetPosition(320-bg->GetWidth()/2+10,470-bg->GetHeight());
	menu_bg->SetTransparency(0);
	cursor->SetTransparency(0);
}

Menu::~Menu()
{
	delete cursor->GetImage();
	delete menu_bg->GetImage();
	delete cursor;
	delete menu_bg;
}

bool Menu::update()
{
	if((WPAD_ButtonsDown(0)&WPAD_BUTTON_LEFT) && menu_sel == 0)
	{
		menu_sel = 1;
		cursor->Move(0.0f,65.0f);
	}
	if((WPAD_ButtonsDown(0)&WPAD_BUTTON_RIGHT) && menu_sel == 1)
	{
		menu_sel = 0;
		cursor->Move(0.0f,-65.0f);
	}
	if(WPAD_ButtonsDown(0)&WPAD_BUTTON_2)
	{
		if(menu_sel == 0)
		{
			Engine::eng_handle->set_mode(ENGINE_MODE_GAME);
			return false;		
		}
		else
		{
			GX_AbortFrame();
			GX_Flush();
			exit(0);
		}
	}

	if(ticks_to_millisecs(gettime())>last_time+100)
	{
		last_time+=100;
		cursor->NextFrame();
	}
	

	// Fading is the new ... scrolling..?
	if(menu_bg->GetTransparency()<255)
		menu_bg->SetTransparency(menu_bg->GetTransparency()+5);
	if(cursor->GetTransparency()<255)
		cursor->SetTransparency(menu_bg->GetTransparency()+5);

	menu_bg->Draw();
	cursor->Draw();

	return get_alive();
}

void Menu::on_hit()
{

}
