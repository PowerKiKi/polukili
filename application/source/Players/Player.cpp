#include <Players/Player.h>

#include <wiiuse/wpad.h>

#include <Console.h>
#include <Constants.h>
#include <Game.h>
#include <Level.h>
#include <Bullets/Bullet.h>
#include <CollisionCategories.h>
#include <PeriodicTimer.h>

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
         this->bulletTimer = new PeriodicTimer(250);
      }
      
      /*************************************************/
      Player::~Player()
      {
         this->level->players.remove(this);
      }
      
      /*************************************************/
      void Player::initPhysic(const b2Vec2& position)
      {
         this->Actor::initPhysic(position);
         this->body->SetFixedRotation(true);
         b2PolygonDef playerShape;
         playerShape.SetAsBox((((float)this->getImageWidth() / Constants::pixelsPerUnits) / 2.0f), (((float)this->getImageHeight() / Constants::pixelsPerUnits) / 2.0f));
         playerShape.density = Constants::defaultDensity;
         playerShape.friction = Constants::defaultFriction;
         playerShape.restitution = Constants::defaultRestitution;

         playerShape.filter.categoryBits   = players;
         playerShape.filter.maskBits      = ground+enemies;
         
         
         this->body->CreateFixture(&playerShape);
         this->body->SetMassFromShapes();        
         
         
         b2BodyDef aimDef;
         aimDef.position.x = position.x + 1.0f; 
         aimDef.position.y = position.y; 
         this->aimPoint = level->world->CreateBody(&aimDef);
         b2CircleDef aimShape;
         aimShape.density = 0.01f;

         aimShape.radius = 0.01f;
         aimShape.localPosition.Set(0.0f, 0.0f);

         aimShape.filter.categoryBits   = anchors;
         aimShape.filter.maskBits      = nothing;
         this->aimPoint->CreateFixture(&aimShape);
         this->aimPoint->SetMassFromShapes();  
         
         b2RevoluteJointDef  jointDef;
         jointDef.Initialize(this->body, this->aimPoint, this->body->GetPosition());
        
         jointDef.lowerAngle = (-180*(b2_pi/180)); // -180 degrees
         jointDef.upperAngle = (0*(b2_pi/180)); // -180 degrees
         jointDef.enableLimit = true;
         jointDef.motorSpeed = 3.0f;
         jointDef.maxMotorTorque = 100000.0f; 
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
         //Console::log(LOG_INFO, "%f",this->aimJoint->GetJointAngle() / b2_pi );
         //Console::log(LOG_INFO, "%f",this->aimJoint->GetMotorSpeed() );
         
 
           

         if(btnsheld & WPAD_BUTTON_UP && !(btnsheld & WPAD_BUTTON_RIGHT))
         {
            //WPAD_BUTTON_UP only
            this->body->ApplyImpulse(b2Vec2(-Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            /*if(this->aimJoint->GetJointAngle()>(-180*(b2_pi/180)))
               this->aimJoint->SetMotorSpeed(-100.0f);*/
         }
         if(btnsheld & WPAD_BUTTON_RIGHT )
         {
            if(btnsheld & WPAD_BUTTON_UP)
            {
               //WPAD_BUTTON_UP & WPAD_BUTTON_RIGHT
               /*if(this->aimJoint->GetJointAngle()>(-135*(b2_pi/180)))
                  this->aimJoint->SetMotorSpeed(-100.0f);
               if(this->aimJoint->GetJointAngle()<(-135*(b2_pi/180)))
                  this->aimJoint->SetMotorSpeed(100.0f);*/
            }  
            else if (btnsheld & WPAD_BUTTON_DOWN)
            {
               //WPAD_BUTTON_RIGHT & WPAD_BUTTON_DOWN
               /*if(this->aimJoint->GetJointAngle()>(-45*(b2_pi/180)))
                  this->aimJoint->SetMotorSpeed(-100.0f);
               if(this->aimJoint->GetJointAngle()<(-45*(b2_pi/180)))
                  this->aimJoint->SetMotorSpeed(100.0f);*/
              
            }
            else
            {
               //WPAD_BUTTON_RIGHT
               /*if(this->aimJoint->GetJointAngle()>(-90*(b2_pi/180)))
                  this->aimJoint->SetMotorSpeed(-100.0f);
               if(this->aimJoint->GetJointAngle()<(-90*(b2_pi/180)))
                  this->aimJoint->SetMotorSpeed(100.0f);*/
            }            
         }            
         if(btnsheld & WPAD_BUTTON_DOWN && !(btnsheld & WPAD_BUTTON_RIGHT))
         {
            //WPAD_BUTTON_DOWN only
            this->body->ApplyImpulse(b2Vec2(Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            /*if(this->aimJoint->GetJointAngle()<(0*(b2_pi/180)))
               this->aimJoint->SetMotorSpeed(100.0f);*/
         }            

         //Shooting & Jumping
         if(btnsheld & WPAD_BUTTON_1)
         {
            if(this->bulletTimer->isExpired())
            {
               Console::log(LOG_INFO, "will shoot");
               Bullets::Bullet* bullet = new Bullets::Bullet(this->level);
               bullet->loadGraphics();
               bullet->initPhysic(this->aimPoint->GetPosition(), this->aimJoint->GetJointAngle());
               //bullet->body->SetAngle(this->aimJoint->GetJointAngle());
               
               Console::log(LOG_INFO, "shot");
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
 
       /*************************************************/
      string Player::getAimImagePath() const
      {
         return Constants::basePath + "cross_hair.png";
      }

      /*************************************************/
      int Player::getAimImageWidth() const
      {
         return 32;
      }

      /*************************************************/
      int Player::getAimImageHeight() const
      {
         return 32;
      }

      /*************************************************/
      void Player::loadGraphics()
      {
      
         this->Actor::loadGraphics();
         
         wsp::Image* aimImage = this->level->game->imageLibrary.get(this->getAimImagePath());
         this->aimSprite = new wsp::Sprite();    
         this->aimSprite->SetImage(aimImage, this->getAimImageWidth(), this->getAimImageHeight());
         this->aimSprite->SetRefPixelPositioning(wsp::REFPIXEL_POS_PIXEL);
         this->aimSprite->SetRefPixelPosition(((int)this->getAimImageWidth()/2),(int)(this->getAimImageHeight()/2));
      }
      
      /*************************************************/ 
      void Player::unloadGraphics()
      {
         if (this->aimSprite)
         {
            delete this->aimSprite;
            this->aimSprite = 0;
         }
         this->level->game->imageLibrary.remove(this->getAimImagePath()); 
         this->Actor::unloadGraphics();
      }
      

      /*************************************************/
      void Player::render()
      {
         this->Actor::render();
         this->aimSprite->SetRotation((float)this->aimPoint->GetAngle() / M_PI * 90.0);
         b2Vec2 pos = aimPoint->GetPosition();
         this->aimSprite->SetPosition(Constants::pixelsPerUnits * pos.x, Constants::pixelsPerUnits * pos.y);
         this->aimSprite->Draw();
      }
         
   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

