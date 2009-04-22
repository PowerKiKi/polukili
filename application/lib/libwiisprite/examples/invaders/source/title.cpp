#include "title.h"
#include <stdlib.h>
#include <wiisprite.h>
#include <ogcsys.h>
#include <gccore.h>

#include <wiiuse/wpad.h>

#include "menu.h"

using namespace wsp;
Title::Title() : child(NULL)
{
	set_alive(true);
	Image *title = new Image();
	if(title->LoadImage("data/title.png")!=IMG_LOAD_ERROR_NONE)
		exit(0);
	Sprite *title_spr = new Sprite();
	title_spr->SetImage(title);
	title_spr->SetPosition(320-title->GetWidth()/2,128);
	title_spr->SetZoom(0.0f);
	set_sprite(title_spr);
}

Title::~Title()
{

}

bool Title::update()
{
	if(get_sprite()->GetZoom()<1.0f)
		get_sprite()->SetZoom(get_sprite()->GetZoom()+0.05f);

	if(!child)
	{
		if(WPAD_ButtonsDown(0))
			child = new Menu();
	}
	else
	{
		if(!child->update())
		{
			delete child;
			child = NULL;
		}
	}
	
	get_sprite()->Draw();
	return get_alive();
}

void Title::on_hit()
{

}
