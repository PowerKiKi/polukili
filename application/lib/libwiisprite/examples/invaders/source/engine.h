#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <ogcsys.h>
#include <gccore.h>

#include <wiisprite.h>

#include "entity.h"
#include <vector>

using std::vector;

using namespace wsp;

enum EngineMode
{
	ENGINE_MODE_INTRO,
	ENGINE_MODE_TITLE,
	ENGINE_MODE_GAME,
	ENGINE_MODE_END
};

class Engine
{
public:
	Engine();
	~Engine();
	
	void set_mode(EngineMode nmode);
	
	void update();

	void start_intro();
	void start_title();
	void start_game();
	void start_end(); // Lol

	// Add an entity to the ent_list_tmp buffer.
	void add_entity(Entity *nent);
	
	// Empties the entity list
	void flush_entities(); 

	static Engine *eng_handle;
private:
	EngineMode mode;
	EngineMode lmode;
	
	vector<Entity *> ent_list; // Processed by the engine each loop
	vector<Entity *> ent_list_tmp; // Buffers potential new entities

};
#endif
