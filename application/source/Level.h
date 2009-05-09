#ifndef polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e
#define polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e

#include <list>

#include "Actor.h"

namespace Polukili 
{
   namespace Players 
   {
      class Player;
   }
   namespace Pets 
   {
      class Pet;
   }
   namespace Ennemies
   {
      class Ennemy;
   }
   namespace Bullets 
   {
      class Bullet;
   }
}

namespace Polukili 
{

   /** 
   *  Represents a level, its ennemies and everything needed.
   */
   class Level : public Actor
   {

      // Operations
   public:

      /** 
      *  Load level data from XML file.
      */
      virtual void loadFromXML(const char* filename);

      // Attributes
   public:
      std::list< Players::Player* > players;
      std::list< Ennemies::Ennemy* > ennemies;
      std::list< Bullets::Bullet* > bullets;
      std::list< Pets::Pet* > pets;

   };

} /* End of namespace Polukili */

#endif // polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e

