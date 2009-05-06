#ifndef polukili_Pets_Pet_h_d713f2ef_f972_4a9d_8e7a_cd74affb1f10
#define polukili_Pets_Pet_h_d713f2ef_f972_4a9d_8e7a_cd74affb1f10

#include <Actor.h>

namespace Polukili 
{
   namespace Pets 
   {

      /** 
      *  A pet is player ally. It helps the player by destroying ennemies or protecting him.
      */
      class Pet : public Polukili::Actor
      {
         
         /**
         * Constructor
         **/
         Pet(Level* level);
         
         /**
         * Destructor
         */
         virtual ~Pet();
      
         //end of class Pet
      };

   } /* End of namespace Polukili::Pets */
} /* End of namespace Polukili */

#endif // polukili_Pets_Pet_h_d713f2ef_f972_4a9d_8e7a_cd74affb1f10

