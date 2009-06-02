#include <Players/Player.h>

#include <wiiuse/wpad.h>

#include <Console.h>
#include <Constants.h>
#include <Level.h>
#include <Bullets/Bullet.h>
#include <CollisionCategories.h>
#include <Timer.h>

namespace Polukili 
{
   namespace Players 
   {
      /*************************************************/
      Player::Player(Level* level, s32 wiimoteChannel)
         : Actor(level), wiimoteChannel(wiimoteChannel)
      {
         Console::log(LOG_INFO, "Player::Player() - new player");    
         this->level->players.push_back(this);
      }
      
      /*************************************************/
      Player::~Player()
      {
         this->level->players.remove(this);
      }
      
      /*************************************************/
      void Player::initPhysic(const b2Vec2& position)
      {
         this->timer = new Timer;
         this->bulletTimer = new Timer;

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
         jointDef.enableLimit = true;
         jointDef.lowerAngle = -1.0f * b2_pi; // -180 degrees
         jointDef.upperAngle = 0.0f * b2_pi; // 180 degrees
         jointDef.motorSpeed = 0.0f;
         jointDef.enableMotor    = true;
         jointDef.collideConnected = false;

         this->aimJoint =  dynamic_cast<b2RevoluteJoint*> (level->world->CreateJoint(&jointDef));

         

         

      }
      
      /*************************************************/
      void Player::nextStep()
      {
         u16 btnsheld = WPAD_ButtonsHeld(this->wiimoteChannel);
         
         // moving and aiming
         this->aimPoint->ApplyForce(b2Vec2(-Constants::defaultGravity*this->aimPoint->GetMass(),0), this->aimPoint->GetPosition());
         Console::log(LOG_INFO, "%f",this->aimJoint->GetJointAngle() );
         if(btnsheld & WPAD_BUTTON_UP && !(btnsheld & WPAD_BUTTON_RIGHT))
         {
            //WPAD_BUTTON_UP only
            this->body->ApplyImpulse(b2Vec2(-Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            /*
            if(this->aimJoint->GetJointAngle()>(-1.0f * b2_pi))
               this->aimJoint->SetMotorSpeed(-1000.0f);*/
         }
         if(btnsheld & WPAD_BUTTON_RIGHT )
         {
            if(btnsheld & WPAD_BUTTON_UP)
            {
               //WPAD_BUTTON_UP & WPAD_BUTTON_RIGHT
               /*if(this->aimJoint->GetJointAngle()>(-0.75f * b2_pi))
                  this->aimJoint->SetMotorSpeed(-1000.0f);
               if(this->aimJoint->GetJointAngle()<(-0.75f * b2_pi))
                  this->aimJoint->SetMotorSpeed(1000.0f);*/
            }  
            else if (btnsheld & WPAD_BUTTON_DOWN)
            {
               //WPAD_BUTTON_RIGHT & WPAD_BUTTON_DOWN
               /*if(this->aimJoint->GetJointAngle()>(-0.25f * b2_pi))
                  this->aimJoint->SetMotorSpeed(-1000.0f);
               if(this->aimJoint->GetJointAngle()<(-0.25f * b2_pi))
                  this->aimJoint->SetMotorSpeed(1000.0f);*/
              
            }
            else
            {
               //WPAD_BUTTON_RIGHT
              /* if(this->aimJoint->GetJointAngle()>(-0.5f * b2_pi))
                  this->aimJoint->SetMotorSpeed(-1000.0f);
               if(this->aimJoint->GetJointAngle()<(-0.5f * b2_pi))
                  this->aimJoint->SetMotorSpeed(1000.0f);*/
            }            
         }            
         if(btnsheld & WPAD_BUTTON_DOWN && !(btnsheld & WPAD_BUTTON_RIGHT))
         {
            //WPAD_BUTTON_DOWN only
            this->body->ApplyImpulse(b2Vec2(Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            //Console::log(LOG_INFO, "WPAD_BUTTON_DOWN");
           /* if(this->aimJoint->GetJointAngle()>(-1.0f * b2_pi))
               this->aimJoint->SetMotorSpeed(1000.0f);*/
         }            

         //Shooting & Jumping
         if(btnsheld & WPAD_BUTTON_1)
         {
            if(this->bulletTimer->getMilliseconds()>=250)
            {
               Console::log(LOG_INFO, "will shoot");
               Bullets::Bullet* bullet = new Bullets::Bullet(this->level);
               bullet->loadGraphics();
               bullet->initPhysic(this->aimPoint->GetPosition());
               
               Console::log(LOG_INFO, "shot");
               this->bulletTimer->reset();
            }              
         }
         if(btnsheld & WPAD_BUTTON_2 )
         {
            this->body->ApplyImpulse(b2Vec2(0,-3*Constants::defaultImpulseSpeed),this->body->GetPosition());
         }  
      }  
      

      /*************************************************/
      int Player::getImageWidth() const
      {
         return 48;
      }

      /*************************************************/
      int Player::getImageHeight() const
      {
         return 48;
      }
      
   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

