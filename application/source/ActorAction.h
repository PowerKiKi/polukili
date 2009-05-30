#ifndef polukili_ActorAction_h_37379ac7_824a_4898_996b_f601e2feecf7
#define polukili_ActorAction_h_37379ac7_824a_4898_996b_f601e2feecf7

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

#endif // polukili_ActorAction_h_37379ac7_824a_4898_996b_f601e2feecf7
