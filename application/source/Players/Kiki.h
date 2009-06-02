#ifndef Polukili_Players_Kiki_h
#define Polukili_Players_Kiki_h

#include <Players/Player.h>

namespace Polukili 
{
   namespace Players 
   {

      class Kiki : public Player
      {
         public:
         
         /**
         * Constructor
         **/
         Kiki(Level* level, s32 wiimoteChannel);
         
         /**
         * Returns the path to the image for the sprite.
         */
         virtual string getImagePath() const;
      };

   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

#endif 

