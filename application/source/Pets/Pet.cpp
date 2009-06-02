#include <Pets/Pet.h>
 
#include <Level.h>

namespace Polukili 
{
   namespace Pets 
   {
      /*************************************************/
      Pet::Pet(Level* level)
         : Actor(level)
      {
         this->level->pets.push_back(this);
      }
   
      /*************************************************/
      Pet::~Pet()
      {
         this->level->pets.remove(this);
      }
   } /* End of namespace Polukili::Pets */
} /* End of namespace Polukili */

