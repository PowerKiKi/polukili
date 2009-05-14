

#include <Players/Player.h>

namespace Polukili 
{
   namespace Players 
   {

      class Player
      {
      public:
      
         /*************************************************/
         Player::Player(Level* level)
            : Actor(level)
         {
         }
         
         /*************************************************/
         void Player::initPhysic()
         {
           // TODO: should do something here
         }
         
         /*************************************************/
         void Player::loadGraphics()
         {
           // TODO: should do something here
         }
         
      }

   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

