#ifndef Polukili_Ennemies_Ennemy_h
#define Polukili_Ennemies_Ennemy_h

#include <Actor.h>

namespace Polukili 
{
   namespace Ennemies 
   {

      /** 
      *  Represents an ennemy
      */
      class Ennemy : public Polukili::Actor
      {
         public:
         
         /**
         * Constructor
         **/
         Ennemy(Level* level);
         
         /**
         * Destructor
         */
         virtual ~Ennemy();
         
         /** 
         *  Sets wether the ennemy must be destroyed to complete the level. It should always be true for boss.
         */
         void setTarget(bool isTarget);
         
         /** 
         *  Returns wether the ennemy must be destroyed to complete the level. It should always be true for boss.
         */
         virtual bool isTarget() const;

      private:
         bool target;
         //end of class Ennemy
      };

   } /* End of namespace Polukili::Ennemies */
} /* End of namespace Polukili */

#endif 

