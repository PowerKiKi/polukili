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
         Poupa(Level* level);
         
         //end of class Poupa
      };

   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

#endif

