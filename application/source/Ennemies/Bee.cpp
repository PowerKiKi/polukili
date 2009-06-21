

#include <Ennemies/Bee.h>

#include <Console.h>
#include <Constants.h>
#include <Level.h>
#include <Box2D.h>
#include <CollisionCategories.h>
 
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
      void Bee::initPhysic(const b2Vec2& position)
      {
         this->Actor::initPhysic(position);
         b2CircleDef beeShape;
         beeShape.radius=((float)this->getImageWidth() * this->powerFactor / Constants::pixelsPerUnits) / 2.0f;
         beeShape.density = Constants::defaultDensity;
         beeShape.friction = Constants::defaultFriction;
         beeShape.restitution = Constants::defaultRestitution;

         beeShape.filter.categoryBits   = enemies;
         
         beeShape.filter.maskBits = players+ground+bullets;

         this->body->CreateShape(&beeShape);
         this->body->SetMassFromShapes();
         // bee movement ( circle ) 
         
         b2BodyDef rotationCenterDef;
         rotationCenterDef.position.Set(basePosition.x+1.0f,basePosition.y);
         this->rotationCenter = level->world->CreateBody(&rotationCenterDef);
         
         b2CircleDef rotationCenterShapeDef;
         rotationCenterShapeDef.radius = 0.2f;
         rotationCenterShapeDef.localPosition.Set(0.0f, 0.0f);

         rotationCenterShapeDef.filter.categoryBits   = anchors;
         rotationCenterShapeDef.filter.maskBits       = nothing;
         this->rotationCenter->CreateShape(&rotationCenterShapeDef);
         
         
         b2RevoluteJointDef  jointDef;
         jointDef.Initialize(this->rotationCenter, this->body, this->rotationCenter->GetPosition());
         jointDef.motorSpeed     = 10.0f;
         jointDef.enableMotor    = true;
         jointDef.collideConnected = false;
         
         this->jointToRotationCenter = level->world->CreateJoint(&jointDef);
         

    
      }
         
      /*************************************************/
      void Bee::render()
      {
         this->sprite->SetZoom(this->powerFactor);
         b2Vec2 pos = body->GetPosition();
         this->sprite->SetPosition(Constants::pixelsPerUnits * pos.x, Constants::pixelsPerUnits * pos.y);
         this->sprite->Draw();
      }

      /*************************************************/
      void Bee::nextStep()
      {
         
         this->body->ApplyForce(b2Vec2(0.0f, Constants::defaultGravity*this->body->GetMass()), this->basePosition);
         
      }
   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

