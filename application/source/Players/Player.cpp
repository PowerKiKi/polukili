#include <Players/Player.h>

#include <wiiuse/wpad.h>

#include <Console.h>
#include <Constants.h>
#include <Level.h>
#include <Bullets/Bullet.h>
#include <CollisionCategories.h>

namespace Polukili 
{
   namespace Players 
   {

      /*************************************************/
      Player::Player(Level* level)
         : Actor(level)
      {
         Console::log(LOG_INFO, "Player::Player() - new player");    
         this->level->players.push_back(this);
      }
      
      /*************************************************/
      Player::~Player()
      {
         this->level->players.remove(this);
      }
      
      void Player::initPhysic(const b2Vec2& position)
      {
         this->timer = new Timer;
         b2BodyDef bodyDef;
         basePosition = position;
         bodyDef.position = position; 
         bodyDef.fixedRotation= true;
         this->body = level->world->CreateBody(&bodyDef);
         b2PolygonDef playerShape;
         playerShape.SetAsBox((((float)this->getImageWidth() / Constants::pixelsPerUnits) / 2.0f), (((float)this->getImageHeight() / Constants::pixelsPerUnits) / 2.0f));
         playerShape.density = Constants::defaultDensity;
         playerShape.friction = Constants::defaultFriction;
         playerShape.restitution = Constants::defaultRestitution;
          // TO COMMENT ! perhaps creating an enum with categories
         // deal with who collide and doesn't
         playerShape.filter.categoryBits   = players;
         playerShape.filter.maskBits      = ground+enemies;
         
         
         this->body->CreateShape(&playerShape);
         this->body->SetMassFromShapes();        
         
         
         b2BodyDef aimDef;
         aimDef.position.x = position.x + 2.0f; 
         aimDef.position.y = position.y; 
         this->aimPoint = level->world->CreateBody(&aimDef);
         b2CircleDef aimShape;
         aimShape.density = 0.1f;

         aimShape.radius = 0.1f;
         aimShape.localPosition.Set(0.0f, 0.0f);
         // TO COMMENT ! perhaps creating an enum with categories
         // deal with who collide and doesn't
         aimShape.filter.categoryBits   = anchors;
         aimShape.filter.maskBits      = nothing;
         this->aimPoint->CreateShape(&aimShape);
         this->aimPoint->SetMassFromShapes();  
         
         b2RevoluteJointDef  jointDef;
         jointDef.Initialize(this->body, this->aimPoint, this->body->GetPosition());
         jointDef.collideConnected = false;
         jointDef.lowerAngle = -1.0f * b2_pi; // -180 degrees
         jointDef.upperAngle = 1.0f * b2_pi; // 180 degrees
         jointDef.enableMotor    = false;
         jointDef.collideConnected = false;

         this->aimJoint =  dynamic_cast<b2RevoluteJoint*> (level->world->CreateJoint(&jointDef));

         

         

      }
      
      /*************************************************/
      void Player::nextStep()
      {
         u16 btnsheld = WPAD_ButtonsHeld(WPAD_CHAN_0);
         this->aimPoint->ApplyForce(b2Vec2(0.0f, -Constants::defaultGravity*this->aimPoint->GetMass()), this->aimPoint->GetPosition());
         if (btnsheld & WPAD_BUTTON_UP)
         {
            this->body->ApplyImpulse(b2Vec2(-Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            this->aimJoint->EnableMotor(this->aimJoint->GetJointAngle()<1.0f);
         }  
         if (btnsheld & WPAD_BUTTON_DOWN)
         {
            this->body->ApplyImpulse(b2Vec2(Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            this->aimJoint->EnableMotor(this->aimJoint->GetJointAngle()>0.0f);
         }  
         if (btnsheld & WPAD_BUTTON_RIGHT)
         {
            
            //this->aimPoint->ApplyForce(b2Vec2(0,-20.0f),this->aimPoint->GetPosition());
         } 
         if (btnsheld & WPAD_BUTTON_2)
            this->body->ApplyImpulse(b2Vec2(0,-3*Constants::defaultImpulseSpeed),this->body->GetPosition());
            
         if (btnsheld & WPAD_BUTTON_1)
         {
            Console::log(LOG_INFO, "will shoot");
            Bullets::Bullet* bullet = new Bullets::Bullet(this->level);
            bullet->loadGraphics();
            bullet->initPhysic(this->aimPoint->GetPosition());
            
            Console::log(LOG_INFO, "shot");
         }
            
      }
      
      /*************************************************/
      string Player::getImagePath() const
      {
         return Constants::basePath + "player.png";
      }

      /*************************************************/
      int Player::getImageWidth() const
      {
         return 48;
      }

      /*************************************************/
      int Player::getImageHeight() const
      {
         return 96;
      }
      
   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

