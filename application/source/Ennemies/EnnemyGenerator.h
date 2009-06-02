#ifndef Polukili_Ennemies_EnnemyGenerator_h
#define Polukili_Ennemies_EnnemyGenerator_h

#include <Ennemies/Ennemy.h>

namespace Polukili 
{
   namespace Ennemies 
   {

      class EnnemyGenerator : public Ennemy
      {
         public:
         
         /**
         * Constructor
         **/
         EnnemyGenerator(Level* level);
         

         // Attributes
      public:
         int frequency;

         //end of class EnnemyGenerator
      };

   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

#endif 

