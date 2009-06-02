#ifndef Polukili_Players_Lila_h
#define Polukili_Players_Lila_h

#include <Players/Player.h>

namespace Polukili 
{
   namespace Players 
   {

      class Lila : public Player
      {
         public:
         
         /**
         * Constructor
         **/
         Lila(Level* level, s32 wiimoteChannel);
         
         /**
         * Returns the path to the image for the sprite.
         */
         virtual string getImagePath() const;
      };

   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

#endif 

