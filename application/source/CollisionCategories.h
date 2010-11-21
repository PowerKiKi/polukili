#ifndef Polukili_CollisionCategories_h
#define Polukili_CollisionCategories_h

namespace Polukili
{
   /** 
   *  The possible collision categories ( box2d can handle up to 16 categories.
   */
   enum CollisionCategories
   {
      nothing     = 0,
      ground      = 1,
      players     = 2,
      enemies     = 4,
      bullets     = 8,
      anchors     = 16,
      
   };
   
}

#endif 
