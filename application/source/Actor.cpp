

#include "Actor.h"

namespace Polukili 
{

   // Operations
   
   /*************************************************/
   Actor::Actor(Level* level)
   {
      
   }

   /*************************************************/
   void Actor::render()
   {

   }

   /*************************************************/
   bool Actor::isDraggable()
   {
      return false;
   }

   /*************************************************/
   void Actor::unloadGraphics()
   {

   }

   /*************************************************/
   void Actor::nextStep()
   {

   }

   /*************************************************/
   bool Actor::acceptDrop(Actor &actorToBeDropped)
   {
      return false;
   }

   /*************************************************/
   bool Actor::isWeak(Element element)
   {
      return false;
   }

   /*************************************************/
   bool Actor::isStrong(Element element)
   {
      return false;
   }

   /*************************************************/
   void Actor::dropped(int droppedActor)
   {

   }

   /*************************************************/
   void Actor::applyEffects()
   {

   }

} /* End of namespace Polukili */

