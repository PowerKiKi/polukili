#ifndef Polukili_Game_h
#define Polukili_Game_h


#include <stack>

#include <grrlib.h>
#include <Box2D/Box2D.h>
#include <fat.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include <Level.h>
#include <ImageLibrary.h>
#include <ContactListener.h>
#include <Console.h>
#include <PeriodicTimer.h>

using namespace std;

namespace Polukili 
{

   /** 
   *  The game engine. It loads and "plays" levels.
   */
   class Game
   {
   
   public: 
   
      /**
      * Constructor.
      */
      Game();
      
      /**
      * Destructor.
      */
      virtual ~Game();
      
      /**
      * Run the specified level. The path must point to the XML file description of the level.
      */
      void run(const string& initialLevel);

      /**
      * Change the current level for the one specified.
      * The current level will not be removed from stack. That means it will be resumed when new level is finished.
      */
      void changeLevel(const string& newLevelPath);

      // Attributes
   public:
      
      ImageLibrary imageLibrary;
      ContactListener contactListener;
      
   private:
      stack< Level* > levels;
      GRRLIB_ttfFont* font;
      Console console;
      PeriodicTimer fpsTimer;
   };

} /* End of namespace Polukili */

#endif 

