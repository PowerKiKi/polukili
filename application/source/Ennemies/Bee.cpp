

#include <Ennemies/Bee.h>


#include <Constants.h>
#include <Level.h>
#include <Box2D.h>




namespace Polukili 
{
   namespace Ennemies 
   {
      /*************************************************/
      Bee::Bee(Level* level)
         : Ennemy(level)
      {
      
      }
      void Bee::initPhysic(float x, float y)
      {
         this->timer = new Timer;
         b2BodyDef bodyDef;
         this->basePosition = new b2Vec2(x / Constants::pixelsPerUnits, y / Constants::pixelsPerUnits);
         bodyDef.position.Set(x / Constants::pixelsPerUnits, y / Constants::pixelsPerUnits); 
         this->body = level->world->CreateBody(&bodyDef);
         b2PolygonDef beeShape;
         beeShape.SetAsBox((((float)this->getImageWidth() / Constants::pixelsPerUnits) / 2.0f), (((float)this->getImageHeight() / Constants::pixelsPerUnits) / 2.0f));
         beeShape.density = Constants::defaultDensity;
         beeShape.friction = Constants::defaultFriction;
         beeShape.restitution = Constants::defaultRestitution;
         // TO COMMENT ! perhaps creating an enum with categories
         // deal with who collide and doesn't

         beeShape.filter.categoryBits   = 0x0004;
         beeShape.filter.maskBits      = 0x0012;

         this->body->CreateShape(&beeShape);
         this->body->SetMassFromShapes();
         // bee movement ( circle ) 
         
         b2BodyDef rotationCenterDef;
         rotationCenterDef.position.Set(this->basePosition->x+1.0f,this->basePosition->y);
         this->rotationCenter = level->world->CreateBody(&rotationCenterDef);
         
         b2CircleDef rotationCenterShapeDef;
         rotationCenterShapeDef.density= 0.0f;
         rotationCenterShapeDef.radius = 0.1f;
         rotationCenterShapeDef.localPosition.Set(0.0f, 0.0f);
         // TO COMMENT ! perhaps creating an enum with categories
         // deal with who collide and doesn't
         rotationCenterShapeDef.filter.categoryBits   = 0x0008;
         rotationCenterShapeDef.filter.maskBits      = 0x0006;
         this->rotationCenter->CreateShape(&rotationCenterShapeDef);
         
         
         b2DistanceJointDef jointDef;
         jointDef.Initialize(this->body, this->rotationCenter, this->body->GetPosition() , this->rotationCenter->GetPosition());
         jointDef.collideConnected = false;
         
         this->jointToRotationCenter = level->world->CreateJoint(&jointDef);
         

    
      }
      void Bee::nextStep()
      {
         b2Vec2 force(this->body->GetPosition()-this->rotationCenter->GetPosition());
         //flying
         if(this->timer->getMilliseconds()>250)
         {
            force.x = -force.y;
            force.y = -(this->body->GetPosition()-this->rotationCenter->GetPosition()).x;
            this->body->ApplyImpulse(force,this->body->GetPosition());
            this->timer->reset();
         }  
         
         
      }
   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

