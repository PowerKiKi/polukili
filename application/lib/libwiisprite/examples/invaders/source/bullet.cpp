#include "bullet.h"

#include <ogc/lwp_watchdog.h>

#include <wiisprite.h>

#include <stdio.h>

using namespace wsp;

Bullet::Bullet(Game *papa, f32 x, f32 y) : next_update(ticks_to_millisecs(gettime())+50), parent(papa)
{
	set_alive(true);
	Sprite *bullet_spr = new Sprite();
	bullet_spr->SetImage(parent->get_bullet_img(),8,16);
	bullet_spr->SetPosition(x, y);
	set_sprite(bullet_spr);
}

Bullet::~Bullet()
{

}

bool Bullet::update()
{
	Sprite *bullet_spr = get_sprite();
	if(bullet_spr->GetY()<0)
	{
		set_alive(false);
		return false;
	}
	if(ticks_to_millisecs(gettime())>next_update)
	{
		next_update += 60;
		bullet_spr->NextFrame();
	}

	/*
		Collision detection!

		Feesh! - Why do you go backwards? Is it because society wants you
		to go forwards but your too cool for that so you go backwards instead?
		What's with the beanie hat? I mean it's like 25 degrees out here? It's
		not like it's cold.
		
		Quit judging me ok! geez. Basically: We go backwards so we hit any
		enemies that are sitting on top of other enemies first :D. (WOW! FEESH IS A GENIUS!)
	*/
	for(vector<Entity *>::reverse_iterator iter = parent->get_ent_list()->rbegin();iter!=parent->get_ent_list()->rend();iter++)
	{
		if((*iter)==this)
			continue;
		Sprite *penemy = (*iter)->get_sprite();
		if(bullet_spr->CollidesWith(penemy))
		{
			on_hit();
			(*iter)->on_hit();
			break;
		}
	}
	// Alpha trail happens here
	bullet_spr->Draw();
	float ypos = bullet_spr->GetY();
	bullet_spr->Move(0.0f,40.0f);
	for(int i = 1;i<6;i++)
	{
		bullet_spr->SetTransparency(i*20);
		bullet_spr->Move(0.0f,-6);
		bullet_spr->Draw();
	}
	bullet_spr->SetTransparency(255);
	bullet_spr->SetPosition(bullet_spr->GetX(),ypos-4.0f);

	return get_alive();
}

void Bullet::on_hit()
{
	set_alive(false);
}
