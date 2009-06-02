#include <Players/Lila.h>

#include <Constants.h>
#include <Console.h>

namespace Polukili 
{
   namespace Players 
   {
      /*************************************************/
      Lila::Lila(Level* level, s32 wiimoteChannel)
         : Player(level, wiimoteChannel)
      {
      }
   
      /*************************************************/
      string Lila::getImagePath() const
      {
         return Constants::basePath + "player_lila.png";
      }
   } 
}

