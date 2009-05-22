#include <Ennemies/Ennemy.h>

#include <Constants.h>
#include <Level.h>

namespace Polukili 
{
   namespace Ennemies 
   {
      /*************************************************/
      Ennemy::Ennemy(Level* level)
         : Actor(level), target(false)
      {
         this->level->ennemies.push_back(this);
      }
      
      /*************************************************/
      Ennemy::~Ennemy()
      {
         this->level->ennemies.remove(this);
      }

      /*************************************************/
      void Ennemy::setTarget(bool isTarget)
      {
         this->target = isTarget;
      }
      
      /*************************************************/
      bool Ennemy::isTarget() const
      {
         return this->target;
      }

      /*************************************************/

      
   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

