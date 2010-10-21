#ifndef Polukili_Effect_h
#define Polukili_Effect_h

namespace Polukili 
{
   class Sprite;

   /** 
   * It basically add a semi-transparent animated sprite over the 
   * actor's sprite to display effect such as explosion or frozen
   */
   class Effect
   {

      // Operations
   public:

      Effect(const Sprite* originalSprite);

      // Attributes

   private:
      Sprite* sprite;
      double duration;
      const Sprite* originalSprite;

      //end of class Effect
   };

} /* End of namespace Polukili */

#endif 

