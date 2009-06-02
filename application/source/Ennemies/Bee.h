#ifndef Polukili_Ennemies_Bee_h
#define Polukili_Ennemies_Bee_h

#include <Ennemies/Ennemy.h>

namespace Polukili 
{
   namespace Ennemies 
   {

      class Bee : public Ennemy
      {
         public:
         
         /**
         * Constructor
         **/
         Bee(Level* level);
         
         virtual void initPhysic(const b2Vec2& position);


         /** 
         *  Render the actor on screen according to current physic data and loaded sprite. Also render special effects if needed.
         */
         virtual void render();
         
         /** 
         *  Define the behavior of the bee for the next step. Apply forces/actions/modifications based on current context (wiimote inputs, state changes based on time, etc.)
         */         
         virtual void nextStep();
         //end of class Bee
         
         protected:
         
         b2Joint* jointToRotationCenter;
         b2Body* rotationCenter;
      };

   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

#endif 

