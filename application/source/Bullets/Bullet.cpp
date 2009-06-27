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
      void Bullet::initPhysic(const b2Vec2& position, float angle)
      {
         this->Actor::initPhysic(position);
         b2PolygonDef bulletShape;
         bulletShape.SetAsBox(((float)this->getImageWidth() * this->powerFactor / Constants::pixelsPerUnits) / 2.0f, ((float)this->getImageHeight() * this->powerFactor / Constants::pixelsPerUnits) / 2.0f);
         bulletShape.density = Constants::defaultDensity;
         bulletShape.friction = Constants::defaultFriction;
         bulletShape.restitution = Constants::defaultRestitution;
         bulletShape.filter.categoryBits   = bullets;
         bulletShape.filter.maskBits = ground+enemies;
         this->body->CreateFixture(&bulletShape);
         this->body->SetMassFromShapes();
         this->body->SetAngle(angle);
         b2Vec2 shotImpulse;
         shotImpulse.x = 2*cos(angle);
         shotImpulse.y = 2*sin(angle);
         this->body->ApplyImpulse(shotImpulse, this->body->GetPosition());
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
      void Bullet::attacks(Actor* actor)
      {
         Console::log(LOG_INFO, "bullet attacks actor");
         actor->isAttackedBy(345);
         //this->state = dead;
      }
      
      /*************************************************/
      void Bullet::attacksWalls()
      {
         Console::log(LOG_INFO, "bullet attacks wall");
         this->state = dead;
      }
   } 
}
