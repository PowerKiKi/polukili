#ifndef Polukili_ActorAction_h
#define Polukili_ActorAction_h

namespace Polukili
{
   /** 
   *  The possible states for an actor.
   */
   enum ActorAction
   {
      nothing        = 0
      walking        = 1,
      running        = 2,
      jumping        = 4,
      flying         = 8,
      waiting        = 16,
      shooting       = 32,
      movingLeft     = 64,
      movingRight    = 128,
      movingUp       = 256,
      movingDown     = 512,
   };
   
}/* End of namespace Polukili */

#endif
