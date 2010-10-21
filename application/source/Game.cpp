#include <Game.h>

#include <grrlib.h>
#include <Box2D/Box2D.h>
#include <fat.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include <Level.h>
#include <FreeMonoBold_ttf.h>
#include <Console.h>
#include <Constants.h>

namespace Polukili 
{
   /*************************************************/
   Game::Game()
   {
      this->font = GRRLIB_LoadTTF(FreeMonoBold_ttf, FreeMonoBold_ttf_size);
      this->console.initialize(this->font);
      Console::log(LOG_INFO, "=============================================================");
      
      GRRLIB_Init();
      // Black background
      GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

      Console::log(LOG_INFO, "Game::Game() - video initialised"); 
      
      // Initialise Wiimote
      WPAD_Init();
      WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
      Console::log(LOG_INFO, "Game::Game() - wiimote initialized");
      
      Console::log(LOG_INFO, "Game::Game() - end");
   }
   
   /*************************************************/
   Game::~Game()
   {
      Console::log(LOG_INFO, "Game::~Game()");
      while (!this->levels.empty())
      {
         delete this->levels.top();
         this->levels.pop();
      }

      GRRLIB_FreeTTF(this->font);
      GRRLIB_Exit();
   }
   
   /*************************************************/
   void Game::run(const string& initialLevel)
   {
      this->changeLevel(initialLevel);
      int frameCount = 0;
      char framePerSecond[32] = "";
      
      while (!this->levels.empty())
      {

         Level* level = this->levels.top();

         level->nextStep();
         level->render();
         
         if (this->console.isEnabled())
           this->console.render();

      //   GRRLIB_PrintfTTFW(580, 16, this->font, framePerSecond, 20, RGBA(255,0,0,0));
		 
         GRRLIB_Render();  // Render the frame buffer to the screen

         
         // If level is finished, resume the previous one
         if (level->isFinished())
         {
            Console::log(LOG_INFO, "Game::run() - resume previous level");
            this->levels.pop();
            delete level;
            
            if (this->levels.top())
               this->levels.top()->loadGraphics();
         }
         
         // WPAD_ButtonsDown tells us which buttons were pressed in this loop
         // this is a "one shot" state which will not fire again until the button has been released
         u32 pressed = WPAD_ButtonsDown(WPAD_CHAN_0);

         // We return to the launcher application via exit
         if (pressed & WPAD_BUTTON_HOME) return;
         if (pressed & WPAD_BUTTON_PLUS) this->console.enable(!this->console.isEnabled());
         
         // Count FPS
         frameCount++;
         if (this->fpsTimer.isExpired())
         {            
            sprintf(framePerSecond, "%2d FPS", frameCount);
            frameCount = 0;
         }
      }
   }
   
   /*************************************************/
   void Game::changeLevel(const string& newLevelPath)
   {
      Console::log(LOG_INFO, "Game::changeLevel() - begin");
      Level* level = new Level(this);
      level->loadFromXML(newLevelPath);
      
      // Unload previous level graphics if any
      if (!this->levels.empty())
         this->levels.top()->unloadGraphics();
      
      level->loadGraphics();
      this->levels.push(level);
      
      Console::log(LOG_INFO, "Game::changeLevel() - end");
   }

} /* End of namespace Polukili */

