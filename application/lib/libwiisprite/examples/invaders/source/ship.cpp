#include <stdlib.h>
#include <wiiuse/wpad.h>
#include "ship.h"
#include "bullet.h"
#include <ogc/lwp_watchdog.h>
#include <wiisprite.h>
#include <math.h>
#include "enemy.h"
using namespace wsp;

Ship::Ship()
{

}

Ship::Ship(Game *papa) : next_update(ticks_to_millisecs(gettime())), sinew(3.0), ypos(0.0)
{
	parent = papa;
	Image *ship_img = new Image();
	if(ship_img->LoadImage("data/ship.png")!=IMG_LOAD_ERROR_NONE)
	{
		exit(0);
	}

	Sprite *ship_spr = new Sprite();
	ship_spr->SetImage(ship_img,48,48);
	ship_spr->SetPosition(320-ship_img->GetWidth()/2,460-ship_img->GetHeight());
	ypos = 460-ship_img->GetHeight();
	set_sprite(ship_spr);
}

Ship::~Ship()
{

}

bool Ship::update()
{
	Sprite *ship = get_sprite();
	if(!ship)
		return false;

	u64 cticks = ticks_to_millisecs(gettime());

	if(WPAD_ButtonsHeld(0)&WPAD_BUTTON_UP)
	{
		if(ship->GetX()>-(s32)ship->GetWidth()/2)
		{
			ship->Move(-3.0f, 0.0f);
		}
		else
		{
			ship->SetPosition(-(s32)ship->GetWidth()/2,ship->GetY());
		}
	}
	if(WPAD_ButtonsHeld(0)&WPAD_BUTTON_DOWN)
	{
		if(ship->GetX()<640-ship->GetWidth()/2)
		{
			ship->Move(3.0f, 0.0f);
		}
		else
		{
			ship->SetPosition(640-ship->GetWidth()/2,ship->GetY());
		}
	}

	if(WPAD_ButtonsDown(0)&WPAD_BUTTON_2)
	{
		parent->add_entity(new Bullet(parent, ship->GetX()+ship->GetWidth()/2-4,ship->GetY()-8));
	}

	if(WPAD_ButtonsDown(0)&WPAD_BUTTON_1)
	{
		parent->add_entity(new Enemy(parent));
	}

	if(cticks>next_update)
	{
		next_update = cticks+50;
		ship->NextFrame();
	}

	ship->SetPosition(ship->GetX(),ypos+(sin(sinew)*3));
	sinew+=0.1;
	ship->Draw();
	return get_alive();
}

void Ship::on_hit()
{

}
