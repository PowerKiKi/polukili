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
      class Bullet : public Actor
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
         virtual void initPhysic(const b2Vec2& position);
         
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
         
         /**
         * When a bullet attacks an actor (usuallz on collision detection).
         */
         virtual void attacks(Actor* actor);

         //end of class Bullet
      };

   } /* End of namespace Polukili::Bullets */
} /* End of namespace Polukili */

#endif

