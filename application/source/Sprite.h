#ifndef Polukili_Sprite_h
#define Polukili_Sprite_h

#include <string>

#include <grrlib.h>

using namespace std;

namespace Polukili 
{
   /** 
   *  A graphical objects with its texture and current position on screen.
   */
   class Sprite
   {

      // Operations
   public:

      /**
      * Constructor
      */
      Sprite(GRRLIB_texImg* image, int width, int height);
      
      /**
      * Destructor
      */
      virtual ~Sprite();

      /** 
      *  Draw the sprite on screen according to current positions.
      */
      void draw();

      /**
       * Defines the current position
       */
      void setPosition(int x, int y);

      /**
       * Defines the current zoom factor
       */
      void setZoom(float factor);

      /**
       * Defines the current rotation
       */
      void setRotation(float angle);

   private:

      /**
      *  The graphical sprite.
      */
      GRRLIB_texImg* image;

      int x;
      int y;
      float factor;
      int angle;
   };

} /* End of namespace Polukili */

#endif 

