#include <Ennemies/Ennemy.h>

#include <Constants.h>
#include <Level.h>

namespace Polukili 
{
   namespace Ennemies 
   {
      /*************************************************/
      Ennemy::Ennemy(Level* level)
         : Actor(level), target(false)
      {
         this->level->ennemies.push_back(this);
      }
      
      /*************************************************/
      Ennemy::~Ennemy()
      {
         this->level->ennemies.remove(this);
      }

      /*************************************************/
      void Ennemy::setTarget(bool isTarget)
      {
         this->target = isTarget;
      }
      
      /*************************************************/
      bool Ennemy::isTarget() const
      {
         return this->target;
      }

      /*************************************************/
      void Ennemy::initPhysic(float x, float y)
      {
         b2BodyDef bodyDef;
         bodyDef.position.Set(x / Constants::pixelsPerUnits, y / Constants::pixelsPerUnits); // arbitraire pour le y de toute facon il va tomber sur le ground
         this->body = level->world->CreateBody(&bodyDef);
         b2PolygonDef shape;
         shape.SetAsBox(this->getImageWidth() / Constants::pixelsPerUnits, this->getImageHeight() / Constants::pixelsPerUnits);

         shape.density = Constants::defaultDensity;
         shape.friction = Constants::defaultFriction;
         shape.restitution = Constants::defaultRestitution;

         this->body->CreateShape(&shape);
         this->body->SetMassFromShapes();
      }
      
   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

