#include "intro.h"
#include <stdlib.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiisprite.h>
#include <ogc/gx.h>
#include <ogc/lwp_watchdog.h>

#include "engine.h"

using namespace wsp;

Intro::Intro() : start_time(ticks_to_millisecs(gettime())), fade_alpha(255)
{
	set_alive(true);
	Image *banner = new Image();
	if(banner->LoadImage("data/intro.png")!=IMG_LOAD_ERROR_NONE)
	{
		exit(0);
	}

	// Quads start at 0,0 with colour of 0,0,0 and alpha of 255 (perfect :D)
	fade.SetWidth(640);
	fade.SetHeight(480);
	
	Sprite *banner_spr = new Sprite();
	banner_spr->SetImage(banner);
	banner_spr->SetPosition((640-banner->GetWidth())/2,240-banner->GetHeight()/2);
	set_sprite(banner_spr);
}

Intro::~Intro()
{
	
}

bool Intro::update()
{
	u64 cticks = ticks_to_millisecs(gettime());
	if(cticks>start_time+5000)
	{
		Engine::eng_handle->set_mode(ENGINE_MODE_TITLE);
		set_alive(false);
	}
	if(cticks>start_time+4500)
	{
		f32 zoom = 1.0f-(cticks-(start_time+4500))/500.0f;
		get_sprite()->SetZoom(zoom);
	}	
	get_sprite()->Draw();
	
	if(fade_alpha!=0)
	{
		fade_alpha-=5;
		fade.SetFillColor((GXColor){0,0,0,fade_alpha});
		fade.Draw();
	}
	return get_alive();
}

void Intro::on_hit()
{

}
