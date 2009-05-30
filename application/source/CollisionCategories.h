#ifndef polukili_CollisionCategories_b938911c_897e_4e0a_98c4_455fbb9d4d65
#define polukili_CollisionCategories_b938911c_897e_4e0a_98c4_455fbb9d4d65

namespace Polukili
{
   /** 
   *  The possible collsision categories ( box2d can handle up to 16 categories.
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
   
}/* End of namespace Polukili */

#endif // polukili_CollisionCategories_b938911c_897e_4e0a_98c4_455fbb9d4d65
