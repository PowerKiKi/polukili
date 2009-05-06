#include <Actor.h>

#include <Level.h>

namespace Polukili 
{

   // Operations
   
   /*************************************************/
   Actor::Actor(Level* level)
   {
      this->level = level;
      this->level->actors.push_back(this);
   }
   
   /*************************************************/
   Actor::~Actor()
   {
      this->level->actors.remove(this);
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
   void Actor::loadGraphics()
   {
      
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

