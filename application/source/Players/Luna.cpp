#include <Players/Luna.h>

#include <Constants.h>
#include <Console.h>

namespace Polukili 
{
   namespace Players 
   {
      /*************************************************/
      Luna::Luna(Level* level, s32 wiimoteChannel)
         : Player(level, wiimoteChannel)
      {
      }
      
      /*************************************************/
      string Luna::getImagePath() const
      {
         return Constants::basePath + "player_luna.png";
      }
   }
}
