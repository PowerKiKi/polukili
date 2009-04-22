#include <stdlib.h>
#include "enemy.h"
#include "bullet.h"
#include <ogc/lwp_watchdog.h>
#include <wiisprite.h>
#include <math.h>
#include <stdlib.h>

using namespace wsp;

Enemy::Enemy()
{

}

Enemy::Enemy(Game *papa) : parent(papa), dying(false)
{
	Sprite *enemy_spr = new Sprite();
	enemy_spr->SetImage(parent->get_enemy_img(),48,48);
	enemy_spr->SetFrame(rand()%4);
	enemy_spr->SetPosition(rand()%600+20,-64.0f);
	set_sprite(enemy_spr);
	xsp = 2.0;
	ly = 40.0f;
}

Enemy::~Enemy()
{

}

bool Enemy::update()
{
	Sprite *enemy = get_sprite();
	if(!enemy)
		return false;
	if(!dying)
	{
		if(enemy->GetY()<40)
		{
			enemy->Move(0.0f, 1.0f);
		}
		else
		{
			if(xsp>0)
			{
				if(enemy->GetX()<600)
					enemy->Move(xsp,0.0f);
				else
				{
					//DROP DOWN, INCREASE SPEED, CHANGE DIRECTION
					if(enemy->GetY()<ly+40.0f)
					{
						enemy->Move(0.0f,1.0f);
					}
					else
					{
						ly = enemy->GetY();
						xsp*=-1.01;
						enemy->SetTransform(TRANS_MIRROR);
					}
				}
			}
			else if(xsp<0)
			{
				if(enemy->GetX()>0)
					enemy->Move(xsp,0.0f);
				else
				{
					//DROP DOWN, INCREASE SPEED, CHANGE DIRECTION
					if(enemy->GetY()<ly+40.0f)
					{
						enemy->Move(0.0f,1.0f);
					}
					else
					{
						ly = enemy->GetY();
						xsp*=-1.01;
						enemy->SetTransform(TRANS_NONE);
					}
				}
			}
		}
	}
	else
	{
		if(enemy->GetZoom()>0.1f)
		{
			enemy->SetZoom(enemy->GetZoom()*0.8);
		}
		else
		{
			return false;
		}
	}
	enemy->Draw();

	return get_alive();
}

void Enemy::on_hit()
{
	dying = true;
}
