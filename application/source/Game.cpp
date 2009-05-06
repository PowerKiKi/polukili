

#include <Game.h>

#include <Level.h>

namespace Polukili 
{

   /*************************************************/
   Game::Game()
   {
      // TODO initiliaze libs and everything
   }
   
   /*************************************************/
   Game::~Game()
   {
      while (!this->levels.empty())
      {
         delete this->levels.top();
         this->levels.pop();
      }
   }
   
   /*************************************************/
   void Game::run(const char* initialLevel)
   {
      this->changeLevel(initialLevel);
      
      while (!this->levels.empty())
      {
         // TODO game logic goes here
      }
   }
   
   /*************************************************/
   void Game::changeLevel(const char* newLevelPath)
   {
      Level* level = new Level(this);
      level->loadFromXML(newLevelPath);
      
      // Unload previous level graphics if any
      if (!this->levels.empty())
         this->levels.top()->unloadGraphics();
      
      level->loadGraphics();
      this->levels.push(level);
   }

} /* End of namespace Polukili */

