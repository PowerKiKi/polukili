#ifndef polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e
#define polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e

#include <list>

#include <Box2D.h>

#include <Actor.h>

using namespace std;

namespace Polukili 
{
   class Game;
   class Actor;
   
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

   /** 
   *  Represents a level, its ennemies and everything needed.
   */
   class Level : public Actor
   {

      // Operations
   public:
      Level(Game* game);
      
      /** 
      *  Load level data from XML file.
      */
      virtual void loadFromXML(const char* filename);

      /**
      * Initialize physic data
      */
      virtual void initPhysic();
      
      /** 
      *  Load graphics data (wsp::Image) for the actor. In most cases the same Image will be loaded once for all instance of a specific class. So a static wsp::Image shall be used.
      */
      virtual void loadGraphics();

      /** 
      *  Unload graphics data to free up memory.
      */
      virtual void unloadGraphics();

      // Attributes
   public:
      std::list< Actor* > actors;
      std::list< Players::Player* > players;
      std::list< Ennemies::Ennemy* > ennemies;
      std::list< Bullets::Bullet* > bullets;
      std::list< Pets::Pet* > pets;
      b2World* world;
      
   private: 
      Game* game;

   };

} /* End of namespace Polukili */

#endif // polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e

