#ifndef polukili_Ennemies_Ennemy_h_3c76803b_6dad_4dfc_9f88_2fd20fc7f0d6
#define polukili_Ennemies_Ennemy_h_3c76803b_6dad_4dfc_9f88_2fd20fc7f0d6

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
         
         virtual void initPhysic(float x, float y);
         

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

#endif // polukili_Ennemies_Ennemy_h_3c76803b_6dad_4dfc_9f88_2fd20fc7f0d6

