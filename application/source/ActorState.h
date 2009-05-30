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
      dead           = 1,
      exploding      = 2,
      imploding      = 4,
      frozen         = 8,
      burning        = 16,
      collapsing     = 32,
      dying          = 64,
   };
   
}/* End of namespace Polukili */

#endif // polukili_ActorState_h_42bdb625_de70_40bc_9396_0d2a7a0fba7d
