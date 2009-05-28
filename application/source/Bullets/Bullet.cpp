#include <Bullets/Bullet.h>

#include <Level.h>
#include <Constants.h>
#include <Console.h>

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
      string Bullet::getImagePath() const
      {
         return Constants::basePath + "default_bullet.png";
      }

      /*************************************************/
      int Bullet::getImageWidth() const
      {
         return 8;
      }

      /*************************************************/
      int Bullet::getImageHeight() const
      {
         return 8;
      }
      
      /*************************************************/
      int Bullet::attack(Polukili::Actor &actor)
      {
         return 0;
      }

   } /* End of namespace Polukili::Bullets */
} /* End of namespace Polukili */

