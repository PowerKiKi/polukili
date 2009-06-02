#ifndef Polukili_Ennemies_Spider_h
#define Polukili_Ennemies_Spider_h

#include <Ennemies/Ennemy.h>

namespace Polukili 
{
   namespace Ennemies 
   {

      class Spider : public Ennemy
      {
         public:
         
         /**
         * Constructor
         **/
         Spider(Level* level);
         
         //end of class Spider
      };

   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

#endif 

