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
      
      Logger::log("Game::Game()");
      
      this->gameWindow.InitVideo();      
      this->gameWindow.SetBackground((GXColor){ 255, 255, 255, 255 });
      Logger::log("Game::Game() - video initialised");
      
      // Initialise Wiimote
      WPAD_Init();
      WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
      Logger::log("Game::Game() - wiimote initialized");
      
      Logger::log("Game::Game() - end");
   }
   
   /*************************************************/
   Game::~Game()
   {
      Logger::log("Game::~Game()");
      while (!this->levels.empty())
      {
         delete this->levels.top();
         this->levels.pop();
      }
   }
   
   /*************************************************/
   void Game::run(const string& initialLevel)
   {
      Logger::log("Game::run() - 0");
      this->changeLevel(initialLevel);
      Logger::log("Game::run() - 1");
      
      while (!this->levels.empty())
      {
      
         Logger::log("Game::run() - dedans");
         Level* level = this->levels.top();
                  
         level->nextStep();
         level->render();
         
         this->gameWindow.Flush();
         
         // If level is finished, resume the previous one
         if (level->isFinished())
         {
         
            Logger::log("Game::run() - resume previous level");
            this->levels.pop();
            delete level;
            
            if (this->levels.top())
               this->levels.top()->loadGraphics();
         }
         
         // WPAD_ButtonsDown tells us which buttons were pressed in this loop
         // this is a "one shot" state which will not fire again until the button has been released
         u32 pressed = WPAD_ButtonsDown(0);

         // We return to the launcher application via exit
         if ( pressed & WPAD_BUTTON_HOME ) exit(0);
      }
   }
   
   /*************************************************/
   void Game::changeLevel(const string& newLevelPath)
   {
      Logger::log("Game::changeLevel() - begin");
      Level* level = new Level(this);
      level->loadFromXML(newLevelPath);
      
      // Unload previous level graphics if any
      if (!this->levels.empty())
         this->levels.top()->unloadGraphics();
      
      level->loadGraphics();
      this->levels.push(level);
      
      Logger::log("Game::changeLevel() - end");
   }

} /* End of namespace Polukili */

