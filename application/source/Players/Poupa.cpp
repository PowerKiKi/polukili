#include <Players/Poupa.h>

#include <Constants.h>
#include <Console.h>

namespace Polukili 
{
   namespace Players 
   {
      /*************************************************/
      Poupa::Poupa(Level* level, s32 wiimoteChannel)
         : Player(level, wiimoteChannel)
      {
      }
   
      /*************************************************/
      string Poupa::getImagePath() const
      {
         return Constants::basePath + "player_poupa.png";
      }
   } 
}
