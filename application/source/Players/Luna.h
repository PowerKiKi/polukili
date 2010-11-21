#ifndef Polukili_Players_Luna_h
#define Polukili_Players_Luna_h

#include <Players/Player.h>

namespace Polukili 
{
   namespace Players 
   {

      class Luna : public Player
      {
         public:
         
         /**
         * Constructor
         **/
         Luna(Level* level, s32 wiimoteChannel);
                  
         /**
         * Returns the path to the image for the sprite.
         */
         virtual string getImagePath() const;
      };

   } /* End of namespace Polukili::Players */
} 

#endif 

