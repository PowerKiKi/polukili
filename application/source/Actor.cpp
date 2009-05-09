

#include "Actor.h"

namespace Polukili 
{

   /** 
   *  The highest parent for every object in games, eg: players, bullets, ennemies, levels...
   */

   {

      // Operations

      /** 
      *  Render the actor on screen according to current physic data and loaded sprite. Also render special effects if needed.
      */
      void Actor::render()
      {

      }

      /** 
      *  Returns if the actor is draggable using the wiimote. This will be true for Point'n'click actors.
      */
      bool Actor::isDraggable()
      {
         return false;
      }

      /** 
      *  Unload graphics data to free up memory.
      */
      bool Actor::unloadGraphics()
      {
         return false;
      }

      /** 
      *  Define the behavior of the actor for the next step. Apply forces/actions/modifications based on current context (wiimote inputs, state changes based on time, etc.)
      */
      void Actor::nextStep()
      {

      }

      /** 
      *  Returns if the actor accept annother actor to be dropped on itself. 
      */
      bool Actor::acceptDrop(Actor &actorToBeDropped)
      {
         return false;
      }

      /** 
      *  Returns wether the actor is weak against the specified element.
      */
      bool Actor::isWeak(Element element)
      {
         return false;
      }

      /** 
      *  Returns wether the actor is strong against the specified element.
      */
      bool Actor::isStrong(Element element)
      {
         return false;
      }

      /** 
      *  This method is called when an actor was dropped.
      */
      void Actor::dropped(int droppedActor)
      {

      }

      /** 
      *  Create/destroy special effects associated with current state.
      */
      void Actor::applyEffects()
      {

      }

      Actor::Actor(int physicWorld)
      {
         return 0;
      }

   } /* End of namespace Polukili */

