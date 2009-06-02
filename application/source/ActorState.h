#ifndef Polukili_ActorState_h
#define Polukili_ActorState_h

namespace Polukili
{
   /** 
   *  The possible states for an actor.
   */
   enum ActorState
   {
      normal         = 0,
      dead           = 1,
      exploding      = 2,
      imploding      = 4,
      frozen         = 8,
      burning        = 16,
      collapsing     = 32,
      dying          = 64,
   };
   
}/* End of namespace Polukili */

#endif
