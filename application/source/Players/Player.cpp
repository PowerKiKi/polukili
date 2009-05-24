#include <Players/Player.h>

#include <Logger.h>
#include <Constants.h>
#include <Level.h>
#include <wiiuse/wpad.h>

namespace Polukili 
{
   namespace Players 
   {

      /*************************************************/
      Player::Player(Level* level)
         : Actor(level)
      {
         Logger::log("Player::Player() - new player");    
         this->level->players.push_back(this);
      }
      
      /*************************************************/
      Player::~Player()
      {
         this->level->players.remove(this);
      }
      
      /*************************************************/
      void Player::initPhysic(float x, float y)
      {
         b2BodyDef bodyDef;
         bodyDef.position.Set(x / Constants::pixelsPerUnits, y / Constants::pixelsPerUnits); // arbitraire pour le y de toute facon il va tomber sur le ground
         this->body = level->world->CreateBody(&bodyDef);
         b2PolygonDef playerShape;
         playerShape.SetAsBox(this->getImageWidth() / Constants::pixelsPerUnits, this->getImageHeight() / Constants::pixelsPerUnits);

         playerShape.density = Constants::defaultDensity;
         playerShape.friction = Constants::defaultFriction;
         playerShape.restitution = Constants::defaultRestitution;

         this->body->CreateShape(&playerShape);
         this->body->SetMassFromShapes();
      }
      
      /*************************************************/
      void Player::nextStep()
      {
         u16 btnsheld = WPAD_ButtonsHeld(0);
         
         if(btnsheld & WPAD_BUTTON_UP)
         {
            this->body->ApplyImpulse(b2Vec2(-Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            
         }
         if(btnsheld & WPAD_BUTTON_DOWN)
         {
            this->body->ApplyImpulse(b2Vec2(Constants::defaultImpulseSpeed,0),this->body->GetPosition());
            
         }
         if(btnsheld & WPAD_BUTTON_2)
         {
            this->body->ApplyImpulse(b2Vec2(0,-3*Constants::defaultImpulseSpeed),this->body->GetPosition());
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
         return 96;
      }

      /*************************************************/
      int Player::getImageHeight() const
      {
         return 48;
      }
      
   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

