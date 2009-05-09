#ifndef polukili_Players_Player_h_08f5452b_7458_424a_adf0_33de30429ebb
#define polukili_Players_Player_h_08f5452b_7458_424a_adf0_33de30429ebb

#include <polukili/Actor.h>

namespace Polukili 
{
   class Level;
} /* End of namespace Polukili */

namespace Polukili 
{
   namespace Players 
   {

      /** 
      *  Represents a player.
      */
      class Player : public polukili::Actor
      {

         // Associations
      public:

         polukili::Level *myLevel;

         //end of class Player
      };

   } /* End of namespace polukili::Players */
} /* End of namespace Polukili */

#endif // polukili_Players_Player_h_08f5452b_7458_424a_adf0_33de30429ebb

