#include <Players/Player.h>

#include <wiiuse/wpad.h>

#include <Console.h>
#include <Constants.h>
#include <Game.h>
#include <Level.h>
#include <Bullets/Bullet.h>
#include <CollisionCategories.h>
#include <PeriodicTimer.h>
#include <Sprite.h>

namespace Polukili 
{
   namespace Players 
   {
      /*************************************************/
      Player::Player(Level* level, s32 wiimoteChannel)
         : Actor(level), aimAngle(0), wiimoteChannel(wiimoteChannel)
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
      void Player::initPhysic(const b2Vec2& position, float32 angle)
      {
         this->Actor::initPhysic(position);
         this->body->SetFixedRotation(true);
         b2PolygonShape playerShape;
         playerShape.SetAsBox((((float)this->getImageWidth() / Constants::pixelsPerUnits) / 2.0f), (((float)this->getImageHeight() / Constants::pixelsPerUnits) / 2.0f));

         b2FixtureDef playerDef;
         playerDef.shape = &playerShape;
         playerDef.density = Constants::defaultDensity;
         playerDef.friction = Constants::defaultFriction;
         playerDef.restitution = Constants::defaultRestitution;
         playerDef.filter.categoryBits   = players;
         playerDef.filter.maskBits      = ground | enemies;
         
         
         this->body->CreateFixture(&playerDef);
      }
      
      /*************************************************/
      void Player::nextStep()
      {
         u16 btnsheld = WPAD_ButtonsHeld(this->wiimoteChannel);
         
         // moving and aiming
 
 
           

         if(btnsheld & WPAD_BUTTON_UP && !(btnsheld & WPAD_BUTTON_RIGHT))
         {
            //WPAD_BUTTON_UP only
            this->body->ApplyLinearImpulse(b2Vec2(-Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            if(this->aimAngle>(-180*(b2_pi/180)))
               this->aimAngle-=0.1;
         }
         if(btnsheld & WPAD_BUTTON_RIGHT )
         {
            if(btnsheld & WPAD_BUTTON_UP)
            {
               //WPAD_BUTTON_UP & WPAD_BUTTON_RIGHT
               if(this->aimAngle>(-135*(b2_pi/180)))
                  this->aimAngle-=0.1;
               if(this->aimAngle<(-135*(b2_pi/180)))
                  this->aimAngle+=0.1;
            }  
            else if (btnsheld & WPAD_BUTTON_DOWN)
            {
               //WPAD_BUTTON_RIGHT & WPAD_BUTTON_DOWN
               if(this->aimAngle>(-45*(b2_pi/180)))
                  this->aimAngle-=0.1;
               if(this->aimAngle<(-45*(b2_pi/180)))
                  this->aimAngle+=0.1;
              
            }
            else
            {
               //WPAD_BUTTON_RIGHT
               if(this->aimAngle>(-90*(b2_pi/180)))
                  this->aimAngle-=0.1;
               if(this->aimAngle<(-90*(b2_pi/180)))
                  this->aimAngle+=0.1;
            }            
         }            
         if(btnsheld & WPAD_BUTTON_DOWN && !(btnsheld & WPAD_BUTTON_RIGHT))
         {
            //WPAD_BUTTON_DOWN only
            this->body->ApplyLinearImpulse(b2Vec2(Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            if(this->aimAngle<(0*(b2_pi/180)))
               this->aimAngle+=0.1;
         }            

         //Shooting & Jumping
         if(btnsheld & WPAD_BUTTON_1)
         {
            if(this->bulletTimer->isExpired())
            {
               Console::log(LOG_INFO, "will shoot");
               Bullets::Bullet* bullet = new Bullets::Bullet(this->level);
               bullet->loadGraphics();
               b2Vec2 aimPos;
               aimPos.x = this->body->GetPosition().x + cos(this->aimAngle);
               aimPos.y = this->body->GetPosition().y + sin(this->aimAngle);
               bullet->initPhysic(aimPos, this->aimAngle);
               
               
               Console::log(LOG_INFO, "shot");
            }              
         }
         if(btnsheld & WPAD_BUTTON_2 )
         {
            this->body->ApplyLinearImpulse(b2Vec2(0,-3*Constants::defaultImpulseSpeed),this->body->GetPosition());
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
         
         GRRLIB_texImg* aimImage = this->level->game->imageLibrary.get(this->getAimImagePath());
         this->aimSprite = new Sprite(aimImage, this->getAimImageWidth(), this->getAimImageHeight());
 //        this->aimSprite->SetRefPixelPositioning(wsp::REFPIXEL_POS_PIXEL);
 //        this->aimSprite->SetRefPixelPosition(((int)this->getAimImageWidth()/2),(int)(this->getAimImageHeight()/2));
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
         this->aimSprite->setRotation(this->aimAngle / M_PI * 90.0);
         b2Vec2 aimPos;
         aimPos.x = this->body->GetPosition().x + cos(this->aimAngle);
         aimPos.y = this->body->GetPosition().y + sin(this->aimAngle);
         this->aimSprite->setPosition(Constants::pixelsPerUnits * aimPos.x, Constants::pixelsPerUnits * aimPos.y);
         this->aimSprite->draw();
      }
         
   } /* End of namespace Polukili::Players */
} 

