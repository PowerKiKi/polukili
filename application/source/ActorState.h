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
   }; 
}/* End of namespace polukili */

#endif // polukili_ActorState_h_42bdb625_de70_40bc_9396_0d2a7a0fba7d
