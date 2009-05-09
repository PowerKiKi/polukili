#ifndef polukili_Effect_h_897eab33_e849_46f9_97c7_88a8d43bd9ca
#define polukili_Effect_h_897eab33_e849_46f9_97c7_88a8d43bd9ca

#include <wiisprite.h>

namespace Polukili 
{

   /** 
   *   It basically add a semi-transparent animated sprite over the actor's sprite to display effect.
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

#endif // polukili_Effect_h_897eab33_e849_46f9_97c7_88a8d43bd9ca

