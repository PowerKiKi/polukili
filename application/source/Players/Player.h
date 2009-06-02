#ifndef Polukili_Players_Player_h
#define Polukili_Players_Player_h

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
         Player(Level* level, s32 wiimoteChannel);
         
         /**
         * Destructor
         */
         virtual ~Player();        

         virtual void initPhysic(const b2Vec2& position);
            
         /** 
         *  Define the behavior of the actor for the next step. Apply forces/actions/modifications based on current context (wiimote inputs, state changes based on time, etc.)
         */
         virtual void nextStep();
         
         /**
         * Returns the width of the tile in the image (must be multiple of 4).
         */
         virtual int getImageWidth() const;
         
         /**
         * Returns the height of the tile in the image (must be multiple of 4).
         */
         virtual int getImageHeight() const;
      
      protected:
         b2Body* aimPoint;
         b2RevoluteJoint* aimJoint;
         Timer* bulletTimer;
         s32 wiimoteChannel;
      };

   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

#endif 

