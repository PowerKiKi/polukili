#include <Players/Player.h>

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
      void Player::initPhysic()
      {
        // TODO: should do something here
      }
      
   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

