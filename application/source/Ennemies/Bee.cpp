

#include <Ennemies/Bee.h>

#include <Console.h>
#include <Constants.h>
#include <Level.h>
#include <Box2D/Box2D.h>
#include <CollisionCategories.h>
#include <Sprite.h>
 
namespace Polukili 
{
   namespace Ennemies 
   {
      /*************************************************/
      Bee::Bee(Level* level)
         : Ennemy(level), rotationCenter(0)
      {
      
      }
      
      /*************************************************/
      Bee::~Bee()
      {
         Console::log(LOG_INFO, "will destroy bee");
         if (this->rotationCenter)
         {
            this->level->world->DestroyBody(this->rotationCenter);
            this->rotationCenter = 0;
         }
         Console::log(LOG_INFO, "destroyed");
      }
      
      /*************************************************/
      void Bee::initPhysic(const b2Vec2& position, float32 angle)
      {
         this->Actor::initPhysic(position);
         b2CircleShape beeShape;
         beeShape.m_radius=((float)this->getImageWidth() * this->powerFactor / Constants::pixelsPerUnits) / 2.0f;
		 
		 b2FixtureDef beeDef;
         beeDef.shape = &beeShape;
         beeDef.density = Constants::defaultDensity;
         beeDef.friction = Constants::defaultFriction;
         beeDef.restitution = Constants::defaultRestitution;
         beeDef.filter.categoryBits   = enemies;
         beeDef.filter.maskBits = players | ground | bullets;

         this->body->CreateFixture(&beeDef);
		 
		 
         // bee movement ( circle ) 
         
         b2BodyDef rotationCenterBodyDef;
         rotationCenterBodyDef.position.Set(basePosition.x + 1.0f, basePosition.y);
         this->rotationCenter = level->world->CreateBody(&rotationCenterBodyDef);
         
         b2CircleShape rotationCenterShape;
         rotationCenterShape.m_radius = 0.2f;
         rotationCenterShape.m_p.Set(0.0f, 0.0f);
		 
		 b2FixtureDef rotationCenterDef;
         rotationCenterDef.shape = &rotationCenterShape;
         rotationCenterDef.filter.categoryBits   = anchors;
         rotationCenterDef.filter.maskBits       = nothing;
         this->rotationCenter->CreateFixture(&rotationCenterDef);
         
         
         b2RevoluteJointDef  jointDef;
         jointDef.Initialize(this->rotationCenter, this->body, this->rotationCenter->GetPosition());
         jointDef.motorSpeed     = 10.0f;
         jointDef.enableMotor    = true;
         jointDef.collideConnected = false;
         
         this->jointToRotationCenter = level->world->CreateJoint(&jointDef);
         

    
      }

      /*************************************************/
      void Bee::nextStep()
      {
         
         this->body->ApplyForce(b2Vec2(0.0f, Constants::defaultGravity*this->body->GetMass()), this->basePosition);
         
      }
   } /* End of namespace Polukili::Ennemies */
} 

