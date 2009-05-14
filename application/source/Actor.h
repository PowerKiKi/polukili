#ifndef polukili_Actor_h_b64b7baa_3957_43a5_b7b0_78e992b91e8a
#define polukili_Actor_h_b64b7baa_3957_43a5_b7b0_78e992b91e8a

#include <wiisprite.h>
#include <mxml.h>
#include <Box2D.h>

#include <Effect.h>
#include <Element.h>
#include <ActorState.h>


namespace Polukili 
{
   class Level;

   /** 
   *  The highest parent for every object in games, eg: players, bullets, ennemies, levels...
   */
   class Actor
   {

      // Operations
   public:

      /**
      * Constructor
      */
      Actor(Level* level);

      /** 
      *  Render the actor on screen according to current physic data and loaded sprite. Also render special effects if needed.
      */
      virtual void render();

      /** 
      *  Load graphics data (wsp::Image) for the actor. In most cases the same Image will be loaded once for all instance of a specific class. So a static wsp::Image shall be used.
      */
      virtual void loadGraphics()  = 0;

      /** 
      *  Returns if the actor is draggable using the wiimote. This will be true for Point'n'click actors.
      */
      virtual bool isDraggable();

      /** 
      *  Unload graphics data to free up memory.
      */
      virtual void unloadGraphics();

      /** 
      *  Define the behavior of the actor for the next step. Apply forces/actions/modifications based on current context (wiimote inputs, state changes based on time, etc.)
      */
      virtual void nextStep();

      /** 
      *  Returns if the actor accept annother actor to be dropped on itself. 
      */
      virtual bool acceptDrop(Actor &actorToBeDropped);

      /** 
      *  Returns wether the actor is weak against the specified element.
      */
      virtual bool isWeak(Element element);

      /** 
      *  Returns wether the actor is strong against the specified element.
      */
      virtual bool isStrong(Element element);

      /** 
      *  This method is called when an actor was dropped.
      */
      virtual void dropped(int droppedActor);

      /** 
      *  Create/destroy special effects associated with current state.
      */
      virtual void applyEffects();

      /**
      * Initialize physic data
      */
      virtual void initPhysic() = 0;

      // Attributes

   protected:
   
      /**
      * The level containing the actor.
      */
      Level* level;
      
      /** 
      *  The physic body.
      */
      b2Body* body;

      /** 
      *  The graphical sprite.
      */
      wsp::Sprite* sprite;

      /** 
      *  Current state of the actor. It may be several state at once (flags).
      */
      ActorState state;

      /** 
      *  The factor of power for the actor. The highest the factor, the biggest the actor (zoom on sprite) and the most powerful he is. Value 1 is default factor.
      */
      double powerFactor;

   private:

      /** 
      *  Current effect on the actor.
      */
      Effect* effect;

      //end of class Actor
   };

} /* End of namespace Polukili */

#endif // polukili_Actor_h_b64b7baa_3957_43a5_b7b0_78e992b91e8a

