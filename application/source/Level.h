#ifndef polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e
#define polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e

#include <list>
#include <string>

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
   class Level
   {

      // Operations
   public:
   
      /** 
      * Constructor.
      */
      Level(Game* game);
      
      /** 
      * Destructor.
      */
      ~Level();
      
      /** 
      *  Load level data from XML file.
      */
      virtual void loadFromXML(const string& filename);
      
      /** 
      *  Load graphics data (wsp::Image) for the whole level (including actors).
      */
      virtual void loadGraphics();

      /** 
      *  Unload graphics data to free up memory.
      */
      virtual void unloadGraphics();
      
      /** 
      *  Render the actor on screen according to current physic data and loaded sprite. Also render special effects if needed.
      */
      virtual void render();
      
      /** 
      *  Advance the whole level logic from one step (all actors will react to situation)
      */
      virtual void nextStep();
      
      /**
      * Returns if the level is finished (basically if all targets were destroyed).
      */
      bool isFinished() const;

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
      string backgroundPath;
      string foregroundPath;
      wsp::Sprite* backgroundSprite;
      wsp::Sprite* foregroundSprite;
      
      /** 
      *  The physic body.
      */
      b2Body* body;

   };

} /* End of namespace Polukili */

#endif // polukili_Level_h_73616512_59b7_4686_b077_24fbdae36d1e

