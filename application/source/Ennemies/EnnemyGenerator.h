#ifndef polukili_Ennemies_EnnemyGenerator_h_bf5fc0cf_fdb2_4bb9_93de_acbe7199cd49
#define polukili_Ennemies_EnnemyGenerator_h_bf5fc0cf_fdb2_4bb9_93de_acbe7199cd49

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

#endif // polukili_Ennemies_EnnemyGenerator_h_bf5fc0cf_fdb2_4bb9_93de_acbe7199cd49

