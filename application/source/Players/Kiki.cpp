#include <Players/Kiki.h>

#include <Constants.h>
#include <Console.h>

namespace Polukili 
{
   namespace Players 
   {
      /*************************************************/
      Kiki::Kiki(Level* level, s32 wiimoteChannel)
         : Player(level, wiimoteChannel)
      {
      }
      
      /*************************************************/
      string Kiki::getImagePath() const
      {
         return Constants::basePath + "player_kiki.png";
      }      
   } 
} 

