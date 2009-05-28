#ifndef polukili_Ennemies_Bee_h_897e3005_eabb_483c_8e68_7476adb41ec7
#define polukili_Ennemies_Bee_h_897e3005_eabb_483c_8e68_7476adb41ec7

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
         
         virtual void initPhysic(float x, float y);
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

#endif // polukili_Ennemies_Bee_h_897e3005_eabb_483c_8e68_7476adb41ec7

