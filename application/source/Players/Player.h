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
         virtual void initPhysic(float x, float y);
            
         /**
         * Returns the path to the image for the sprite.
         */
         virtual string getImagePath() const;
         
         /**
         * Returns the width of the tile in the image (must be multiple of 4).
         */
         virtual int getImageWidth() const;
         
         /**
         * Returns the height of the tile in the image (must be multiple of 4).
         */
         virtual int getImageHeight() const;


         //end of class Player
      };

   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

#endif // polukili_Players_Player_h_08f5452b_7458_424a_adf0_33de30429ebb

