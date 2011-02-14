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
         
         /**
         * Destructor
         */
         virtual ~Bee();
         
         
         virtual void initPhysic(const b2Vec2& position, float32 angle = 0);

         
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
} 

#endif 

