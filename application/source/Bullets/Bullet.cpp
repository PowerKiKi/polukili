#include <Bullets/Bullet.h>

#include <Level.h>
#include <Constants.h>
#include <Console.h>
#include <CollisionCategories.h>

namespace Polukili 
{
   namespace Bullets
   {
      /*************************************************/
      Bullet::Bullet(Level* level)
         : Actor(level)
      {
         this->level->bullets.push_back(this);
      }
      
      /*************************************************/
      Bullet::~Bullet()
      {
         this->level->bullets.remove(this);
      }
      
      /*************************************************/
      
      void Bullet::initPhysic(const b2Vec2& position)
      {
         this->timer = new Timer;
         b2BodyDef bodyDef;
         basePosition = position;
         bodyDef.position = position;
         this->body = level->world->CreateBody(&bodyDef);
         b2PolygonDef bulletShape;
         bulletShape.SetAsBox(((float)this->getImageWidth() * this->powerFactor / Constants::pixelsPerUnits) / 2.0f, ((float)this->getImageHeight() * this->powerFactor / Constants::pixelsPerUnits) / 2.0f);
         bulletShape.density = Constants::defaultDensity;
         bulletShape.friction = Constants::defaultFriction;
         bulletShape.restitution = Constants::defaultRestitution;
         bulletShape.filter.categoryBits   = bullets;
         bulletShape.filter.maskBits = ground+enemies;
         this->body->CreateShape(&bulletShape);
         this->body->SetMassFromShapes();
      }

      /*************************************************/
      string Bullet::getImagePath() const
      {
         return Constants::basePath + "default_bullet.png";
      }

      /*************************************************/
      int Bullet::getImageWidth() const
      {
         return 8;
      }

      /*************************************************/
      int Bullet::getImageHeight() const
      {
         return 8;
      }
      
      /*************************************************/
      int Bullet::attack(Polukili::Actor &actor)
      {
         return 0;
      }

   } /* End of namespace Polukili::Bullets */
} /* End of namespace Polukili */

