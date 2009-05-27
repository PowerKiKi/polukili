

#include <Ennemies/Bee.h>

#include <Logger.h>
#include <Constants.h>




namespace Polukili 
{
   namespace Ennemies 
   {
      /*************************************************/
      Bee::Bee(Level* level)
         : Ennemy(level)
      {
      }
      void Bee::nextStep()
      {

         //flying
         
         this->body->ApplyForce(b2Vec2(0.0f,-Constants::defaultGravity*this->body->GetMass()),this->body->GetPosition());
         
      }
   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

