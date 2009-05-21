#include <Game.h>

#include <wiisprite.h>
#include <Box2D.h>
#include <fat.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <Logger.h>

#include <Level.h>

namespace Polukili 
{

   /*************************************************/
   Game::Game()
   {
      
      Logger::log("Game creation");
      
      this->gameWindow.InitVideo();      
      this->gameWindow.SetBackground((GXColor){ 255, 255, 255, 255 });
      Logger::log("video initialised");
      
      // Initialise Wiimote
      WPAD_Init();
      WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
      Logger::log("wiimote initialized");
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
   void Game::run(const string& initialLevel)
   {
      this->changeLevel(initialLevel);
      
      while (!this->levels.empty())
      {
         Level* level = this->levels.top();
                  
         level->nextStep();
         level->render();
         
         this->gameWindow.Flush();
         
         // If level is finished, resume the previous one
         if (level->isFinished())
         {
            this->levels.pop();
            delete level;
            
            if (this->levels.top())
               this->levels.top()->loadGraphics();
         }
      }
   }
   
   /*************************************************/
   void Game::changeLevel(const string& newLevelPath)
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

