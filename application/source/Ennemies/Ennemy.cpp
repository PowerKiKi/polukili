

#include "Ennemy.h"

namespace Polukili 
{
   namespace Ennemies 
   {

      // Operations

      /** 
      *  Returns wether the ennemy must be destroyed to complete the level. It should always be true for boss.
      */
      bool Ennemy::isTarget()
      {
         return false;
      }

   } /* End of namespace polukili::Ennemies */
} /* End of namespace Polukili */

