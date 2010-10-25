#ifndef Polukili_Players_Player_h
#define Polukili_Players_Player_h

#include <Actor.h>
#include <PeriodicTimer.h>


namespace Polukili 
{   
   namespace Players 
   {
      /** 
      *  Represents a player.
      */
      class Player : public Actor
      {
      public:
         
         /**
         * Constructor.
         */
         Player(Level* level, s32 wiimoteChannel);
         
         /**
         * Destructor
         */
         virtual ~Player();        

         virtual void initPhysic(const b2Vec2& position, float32 angle = 0);
            
         /** 
         *  Define the behavior of the actor for the next step. Apply forces/actions/modifications based on current context (wiimote inputs, state changes based on time, etc.)
         */
         virtual void nextStep();
         
         /**
         * Returns the width of the tile in the image (must be multiple of 4).
         */
         virtual int getImageWidth() const;
         
         /**
         * Returns the height of the tile in the image (must be multiple of 4).
         */
         virtual int getImageHeight() const;

         

         
         /**
         * Returns the width of the tile in the aim image (must be multiple of 4).
         */
         virtual int getAimImageWidth() const;
         
         /**
         * Returns the height of the tile in the aim image (must be multiple of 4).
         */
         virtual int getAimImageHeight() const;       
         /**
         * Returns the path to the image for the aim sprite.
         */
         virtual string getAimImagePath() const;    
         /** 
         *  Load graphics data (GRRLIB_texImg) for the actor. In most cases the same Image will be loaded once for all instance of a specific class.
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
         
      protected:
         float aimAngle;
         PeriodicTimer* bulletTimer;
         s32 wiimoteChannel;
               /** 
         *  The graphical sprite.
         */
         Sprite* aimSprite;
      };

   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

#endif 

