#ifndef Polukili_Bullets_Bullet_h
#define Polukili_Bullets_Bullet_h

#include <Actor.h>

namespace Polukili 
{
   namespace Bullets 
   {

      /** 
      *  Represent a bullet/missile. 
      */
      class Bullet : public Polukili::Actor
      {
      public:
         
         /**
         * Constructor
         **/
         Bullet(Level* level);
         
         /**
         * Destructor
         */
         virtual ~Bullet();         
         
         
         
         /**
         * Initialize physic data
         */
         virtual void initPhysic(const b2Vec2& position, float angle);
         /**
         * Returns the path to the image for the sprite.
         */
         virtual string getImagePath() const;
         
         /**
         * Returns the width of the tile in the image (must be multiple of 4).
         */
         virtual int getImageWidth() const;
         
         /**
         * Returns the height of the tile in the image (must be multiple of 4).
         */
         virtual int getImageHeight() const;
         

         virtual int attack(Polukili::Actor &actor);

         //end of class Bullet
      };

   } /* End of namespace Polukili::Bullets */
} /* End of namespace Polukili */

#endif

