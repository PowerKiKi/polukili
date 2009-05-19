#ifndef polukili_ActorState_h_42bdb625_de70_40bc_9396_0d2a7a0fba7d
#define polukili_ActorState_h_42bdb625_de70_40bc_9396_0d2a7a0fba7d

namespace Polukili
{
   /** 
   *  The possible states for an actor.
   */
   enum ActorState
   {
      normal         = 0,
      exploding      = 2,
      imploding      = 4,
      frozen         = 8,
      burning        = 16,
      waiting        = 32,
      walking        = 64,
      running        = 128,
      jumping        = 256,
      flying         = 512,
      movingLeft     = 1024,
      movingRight    = 2048,
      movingUp       = 4096,
      movingDown     = 8192,
      shooting       = 16384,
      collapsing     = 32768,
      dying          = 65536,
   };
   
}/* End of namespace Polukili */

#endif // polukili_ActorState_h_42bdb625_de70_40bc_9396_0d2a7a0fba7d
