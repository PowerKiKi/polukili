#ifndef Polukili_Pets_Pet_h
#define Polukili_Pets_Pet_h

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

#endif 

