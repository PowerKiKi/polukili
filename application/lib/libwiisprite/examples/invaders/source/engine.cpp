#include <ogcsys.h>
#include <gccore.h>

#include "engine.h"
#include "intro.h"
#include "title.h"
#include "game.h"
#include <vector>

#include <wiisprite.h>

using std::vector;
using namespace wsp;
Engine::Engine() : mode(ENGINE_MODE_INTRO), lmode(ENGINE_MODE_INTRO)
{
	Engine::eng_handle = this;
	start_intro();
}

Engine::~Engine()
{
	ent_list.clear();
	ent_list_tmp.clear();
}
	
void Engine::set_mode(EngineMode nmode)
{
	mode = nmode;
}
	
void Engine::update()
{
	if(mode != lmode)
	{
		switch(mode)
		{
			case ENGINE_MODE_INTRO:
				start_intro();
				break;
			case ENGINE_MODE_TITLE:
				start_title();
				break;
			case ENGINE_MODE_GAME:
				start_game();
				break;
			case ENGINE_MODE_END:
				start_end();
				break;
		}
		lmode = mode;
	}
	// Process any pending entities
	if(ent_list_tmp.size())
	{
		for(u32 i = 0; i<ent_list_tmp.size();i++)
		{
			ent_list.push_back(ent_list_tmp[i]);
		}
		ent_list_tmp.clear();
	}

	if(ent_list.size())
	{
		for(vector<Entity *>::iterator it = ent_list.begin(); it!=ent_list.end();)
		{
			if(!(*it)->update())
			{
				delete (*it);
				ent_list.erase(it);
				continue;
			}
			it++;
		}
	}
}

void Engine::start_intro()
{
	flush_entities();
	add_entity(new Intro());
}

void Engine::start_title()
{
	flush_entities();
	add_entity(new Title());	
}

void Engine::start_game()
{
	flush_entities();
	add_entity(new Game());
}

void Engine::start_end()
{

}

void Engine::add_entity(Entity *nent)
{
	ent_list_tmp.push_back(nent);
}
	
void Engine::flush_entities()
{
	for(vector<Entity*>::iterator it = ent_list_tmp.begin(); it!=ent_list_tmp.end();it++)
	{
		delete (*it);
	}
	for(vector<Entity*>::iterator it = ent_list.begin(); it!=ent_list.end();it++)
	{
		delete (*it);
	}

	ent_list_tmp.clear();
	ent_list.clear();
}

Engine *Engine::eng_handle = NULL;
