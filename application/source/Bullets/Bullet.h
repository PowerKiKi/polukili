#ifndef polukili_Bullets_Bullet_h_c2b41b77_d0cd_40be_b5f5_c8aca3789145
#define polukili_Bullets_Bullet_h_c2b41b77_d0cd_40be_b5f5_c8aca3789145

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

         // Operations
      public:

         virtual int attack(Polukili::Actor &actor);

         //end of class Bullet
      };

   } /* End of namespace Polukili::Bullets */
} /* End of namespace Polukili */

#endif // polukili_Bullets_Bullet_h_c2b41b77_d0cd_40be_b5f5_c8aca3789145

