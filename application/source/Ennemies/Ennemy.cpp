#include <Ennemies/Ennemy.h>

#include <Level.h>

namespace Polukili 
{
   namespace Ennemies 
   {
      /*************************************************/
      Ennemy::Ennemy(Level* level)
         : Actor(level)
      {
         this->level->ennemies.push_back(this);
      }
      
      /*************************************************/
      Ennemy::~Ennemy()
      {
         this->level->ennemies.remove(this);
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

