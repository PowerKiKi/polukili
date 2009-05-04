#ifndef polukili_Game_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc
#define polukili_Game_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc


#include <stack>

#include <Level.h>
#include <ImageLibrary.h>

namespace Polukili 
{

   /** 
   *  The game engine. It loads and "plays" levels.
   */
   class Game
   {
   
   public: 
   
   /**
   * Run the specified level. The path must point to the XML file description of the level.
   */
   void run(const char* initialLevel);

   /**
   * Change the current level for the one specified.
   * The current level will not be removed from stack. That means it will be resumed when new level is finished.
   */
   void changeLevel(const char* newLevelPath);

      // Attributes
   public:
      std::stack< Level* > levels;
      
      ImageLibrary imageLibrary;

      //end of class Game
   };

} /* End of namespace Polukili */

#endif // polukili_Game_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc

