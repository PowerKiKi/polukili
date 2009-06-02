#ifndef Polukili_Effect_h
#define Polukili_Effect_h

#include <wiisprite.h>

namespace Polukili 
{

   /** 
   * It basically add a semi-transparent animated sprite over the 
   * actor's sprite to display effect such as explosion or frozen
   */
   class Effect
   {

      // Operations
   public:

      Effect(const wsp::Sprite* originalSprite);

      // Attributes

   private:
      wsp::Sprite sprite;
      double duration;
      const wsp::Sprite* originalSprite;

      //end of class Effect
   };

} /* End of namespace Polukili */

#endif 

