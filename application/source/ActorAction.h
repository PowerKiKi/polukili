#ifndef Polukili_ActorAction_h_3ff17742_affd_47d1_9970_fed522a38911
#define Polukili_ActorAction_h_3ff17742_affd_47d1_9970_fed522a38911

namespace Polukili
{
   /** 
   *  The possible states for an actor.
   */
   enum ActorAction
   {
      stopped        = 0,
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
   
}

#endif
