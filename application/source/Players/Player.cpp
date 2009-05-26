#include <Players/Player.h>

#include <Console.h>
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
         Console::log(LOG_INFO, "Player::Player() - new player");    
         this->level->players.push_back(this);
      }
      
      /*************************************************/
      Player::~Player()
      {
         this->level->players.remove(this);
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
         return 48;
      }

      /*************************************************/
      int Player::getImageHeight() const
      {
         return 96;
      }
      
   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

