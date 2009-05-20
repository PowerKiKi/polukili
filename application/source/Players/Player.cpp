#include <Players/Player.h>

#include <Constants.h>
#include <Level.h>

namespace Polukili 
{
   namespace Players 
   {

      /*************************************************/
      Player::Player(Level* level)
         : Actor(level)
      {
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
        // TODO: should do something here
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

