#ifndef Polukili_Ennemies_Earthworm_h
#define Polukili_Ennemies_Earthworm_h

#include <Ennemies/Ennemy.h>

namespace Polukili 
{
   namespace Ennemies 
   {

      class Earthworm : public Ennemy
      {
         public:
         
         /**
         * Constructor
         **/
         Earthworm(Level* level);
         
         //end of class Earthworm
      };

   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

#endif 

