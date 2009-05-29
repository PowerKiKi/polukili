#include <Players/Player.h>

#include <wiiuse/wpad.h>

#include <Console.h>
#include <Constants.h>
#include <Level.h>
#include <Bullets/Bullet.h>

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
         playerShape.filter.categoryBits   = 0x0002;
         playerShape.filter.maskBits      = 0x0005;
         
         this->body->CreateShape(&playerShape);
         this->body->SetMassFromShapes();
      }
      
      /*************************************************/
      void Player::nextStep()
      {
         u16 btnsheld = WPAD_ButtonsHeld(WPAD_CHAN_0);
         
         if (btnsheld & WPAD_BUTTON_UP)
            this->body->ApplyImpulse(b2Vec2(-Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            
         if (btnsheld & WPAD_BUTTON_DOWN)
            this->body->ApplyImpulse(b2Vec2(Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            
         if (btnsheld & WPAD_BUTTON_2)
            this->body->ApplyImpulse(b2Vec2(0,-3*Constants::defaultImpulseSpeed),this->body->GetPosition());
            
         if (btnsheld & WPAD_BUTTON_1)
         {
            Console::log(LOG_INFO, "will shoot");
            Bullets::Bullet* bullet = new Bullets::Bullet(this->level);
            bullet->loadGraphics();
            b2Vec2 pos = body->GetPosition();
            pos.x += 0.5;
            bullet->initPhysic(pos);
            
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

