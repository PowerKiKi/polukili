

#include <Ennemies/Ennemy.h>

namespace Polukili 
{
   namespace Ennemies 
   {
      /*************************************************/
      Ennemy::Ennemy(Level* level)
         : Actor(level)
      {
      }

      /** 
      *  Returns wether the ennemy must be destroyed to complete the level. It should always be true for boss.
      */
      bool Ennemy::isTarget()
      {
         return false;
      }

      /*************************************************/
      void Ennemy::initPhysic()
      {
        // TODO: should do something here
      }
      
   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

