#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <ogcsys.h>
#include <malloc.h>
#include <vector>
#include <wiisprite.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>

#include "ship.h"
#include "enemy.h"
using std::vector;
using namespace wsp;

Game::Game() : next_wave(0), wave_num(1), show_hitbox(false)
{
	set_alive(true);
	// Create the player
	player = new Ship(this);
	bullet_img = new Image();
	
	if(bullet_img->LoadImage("data/bullet.png")!=IMG_LOAD_ERROR_NONE)
	{
		exit(0);
	}

	enemy_img = new Image();
	if(enemy_img->LoadImage("data/enemies.png")!=IMG_LOAD_ERROR_NONE)
	{
		exit(0);
	}
}

Game::~Game()
{
	
}

bool Game::update()
{
	if(WPAD_ButtonsDown(0)&WPAD_BUTTON_1)
		show_hitbox = true;
	if(WPAD_ButtonsDown(0)&WPAD_BUTTON_B)
		show_hitbox = false;
	for(vector<Entity *>::iterator iter = ent_list_tmp.begin();iter!=ent_list_tmp.end();iter++)
	{
		ent_list.push_back((*iter));
	}
	ent_list_tmp.clear();

	for(vector<Entity *>::iterator iter = ent_list.begin();iter!=ent_list.end();)
	{
		if(!(*iter)->update())
		{
			delete (*iter);
			ent_list.erase(iter);
			continue;
		}
		iter++;
	}
	
	player->update();

	generate_wave();

	return get_alive();
}

void Game::on_hit()
{

}

void Game::add_entity(Entity *new_ent)
{
	ent_list_tmp.push_back(new_ent);
}

vector<Entity *> *Game::get_ent_list()
{
	return &ent_list;
}

Image *Game::get_bullet_img()
{
	return bullet_img;
}

Image *Game::get_enemy_img()
{
	return enemy_img;
}

void Game::generate_wave()
{
	if(ticks_to_millisecs(gettime())>next_wave)
	{
		for(int i = 0;i<10+(6*wave_num);i++)
		{
			add_entity(new Enemy(this));
		}
		next_wave = ticks_to_millisecs(gettime())+10000;
	}
}
