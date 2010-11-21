#ifndef Polukili_Players_Poupa_h
#define Polukili_Players_Poupa_h

#include <Players/Player.h>

namespace Polukili 
{
   class Level;
   
   namespace Players 
   {

      class Poupa : public Player
      {
         public:
         
         /**
         * Constructor
         **/
         Poupa(Level* level, s32 wiimoteChannel);
         
         /**
         * Returns the path to the image for the sprite.
         */
         virtual string getImagePath() const;
      };

   } /* End of namespace Polukili::Players */
} 

#endif

