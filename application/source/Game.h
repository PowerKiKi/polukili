#ifndef polukili_Game_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc
#define polukili_Game_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc


#include <stack>

#include <wiisprite.h>
#include <Box2D.h>
#include <fat.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include <Level.h>
#include <ImageLibrary.h>
#include <BibScreenFont.h>
#include <Console.h>

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
      * Desstructor.
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
      
   private:
      stack< Level* > levels;
      wsp::GameWindow gameWindow;
      BibScreenFont font;
      Console console;
      bool consoleVisible;
   };

} /* End of namespace Polukili */

#endif // polukili_Game_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc

