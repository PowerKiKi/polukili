#include <Bullets/Bullet.h>

#include <Level.h>

namespace Polukili 
{
   namespace Bullets 
   {
      /*************************************************/
      Bullet::Bullet(Level* level)
         : Actor(level)
      {
         this->level->bullets.push_back(this);
      }
      
      /*************************************************/
      Bullet::~Bullet()
      {
         this->level->bullets.remove(this);
      }

      /*************************************************/
      int Bullet::attack(Polukili::Actor &actor)
      {
         return 0;
      }

   } /* End of namespace Polukili::Bullets */
} /* End of namespace Polukili */

