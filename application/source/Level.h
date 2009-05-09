#ifndef polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e
#define polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e

#include <vector>

#include "Actor.h"

namespace Polukili 
{
   namespace Players 
   {
      class Player;
   } /* End of namespace polukili::Players */
} /* End of namespace Polukili */

namespace Polukili 
{

   /** 
   *  Represents a level, its ennemies and everything needed.
   */
   class Level : public Actor
   {

      // Operations
   public:

      /** 
      *  Load level data from XML file.
      */
      virtual void loadFromXML(String filename);

      // Attributes
   public:
      int players;
      int ennemies;
      int bullets;
      int pets;

      // Associations
   public:

      /**
      * @element-type Player
      */
      std::vector< Players::Player* > myPlayer;

      //end of class Level
   };

} /* End of namespace Polukili */

#endif // polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e

