

#include <Ennemies/Bee.h>

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
         
         float deltaX = 180.0f/Constants::pixelsPerUnits;
         float deltaY = 180.0f/Constants::pixelsPerUnits;
         
         b2Vec2 position = this->body->GetPosition();
         b2Vec2 linearVelocity = this->body->GetLinearVelocity();
         static b2Vec2 forces(10.0f,0.0f);
         
         if(linearVelocity.x >= 0.0f)
         {
            forces.y = sin(position.x-this->basePosition->x)*4.0f;
         }
         else
         {
            forces.y = cos(position.x-this->basePosition->x)*4.0f;
         }
         
         this->body->SetLinearVelocity(forces);
      }
   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

