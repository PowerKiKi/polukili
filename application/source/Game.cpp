#include <Game.h>

#include <wiisprite.h>
#include <Box2D.h>
#include <fat.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include <Level.h>

namespace Polukili 
{

   /*************************************************/
   Game::Game()
   {
      fatInitDefault();
   
      this->gameWindow.InitVideo();      
      this->gameWindow.SetBackground((GXColor){ 255, 255, 255, 255 });
      
      // Initialise Wiimote
      WPAD_Init();
      WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
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
         Level* level = this->levels.top();
         list<Actor*> actorsToDelete;
      
         WPAD_ScanPads();
         
         // Each actors reacts to current situation
         for (list<Actor*>::iterator it = level->actors.begin(); it != level->actors.end(); it++)
         {
            (*it)->nextStep();
            if ((*it)->is(dead))
               actorsToDelete.push_back(*it);
         }
         
         // Delete all dead actors
         for (list<Actor*>::iterator it = actorsToDelete.begin(); it != actorsToDelete.end(); it++)
            delete *it;
         
         // TODO game logic goes here
         
         this->gameWindow.Flush();
         
         float32 timeStep = 1.0f / 60.0f;
         int32 iterations = 10;         
         level->world->Step(timeStep, iterations); // TODO these variables should be in Constants class
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

