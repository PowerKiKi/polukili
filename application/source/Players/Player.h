#ifndef polukili_Players_Player_h_08f5452b_7458_424a_adf0_33de30429ebb
#define polukili_Players_Player_h_08f5452b_7458_424a_adf0_33de30429ebb

#include <Actor.h>

namespace Polukili 
{   
   namespace Players 
   {

      /** 
      *  Represents a player.
      */
      class Player : public Actor
      {
      public:
         
         /**
         * Constructor.
         */
         Player(Level* level);
         
         /**
         * Destructor
         */
         virtual ~Player();
         

         /**
         * Initialize physic data
         */
         virtual void initPhysic();


         //end of class Player
      };

   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

#endif // polukili_Players_Player_h_08f5452b_7458_424a_adf0_33de30429ebb

