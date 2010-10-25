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
      void Bullet::initPhysic(const b2Vec2& position, float32 angle)
      {
         this->Actor::initPhysic(position, angle);
         b2PolygonShape bulletShape;
         bulletShape.SetAsBox(((float)this->getImageWidth() * this->powerFactor / Constants::pixelsPerUnits) / 2.0f, ((float)this->getImageHeight() * this->powerFactor / Constants::pixelsPerUnits) / 2.0f);
         
         b2FixtureDef bulletDef;
         bulletDef.shape = &bulletShape;
         bulletDef.density = Constants::defaultDensity;
         bulletDef.friction = Constants::defaultFriction;
         bulletDef.restitution = Constants::defaultRestitution;
         bulletDef.filter.categoryBits = bullets;
         bulletDef.filter.maskBits = ground + enemies;
         this->body->CreateFixture(&bulletDef);

         b2Vec2 shotImpulse;
         shotImpulse.x = 2*cos(angle);
         shotImpulse.y = 2*sin(angle);
         this->body->ApplyLinearImpulse(shotImpulse, this->body->GetPosition());
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
