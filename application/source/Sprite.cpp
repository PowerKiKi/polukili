#include <Sprite.h>

#include <Constants.h>
#include <Console.h>
#include <Game.h>
#include <Level.h>


namespace Polukili 
{
   /*************************************************/
   Sprite::Sprite(GRRLIB_texImg* image, int width, int height)
      : image(image), x(0), y(0), referenceX(0), referenceY(0), factor(1), angle(0)
   {
      Console::log(LOG_INFO, "new Sprite");
   }
   
   /*************************************************/
   Sprite::~Sprite()
   {
      Console::log(LOG_INFO, "will destroy sprite");
   }
   
   /*************************************************/
   void Sprite::draw()
   {
      GRRLIB_DrawImg(this->x - this->referenceX, this->y - this->referenceY, this->image, this->angle, this->factor, this->factor, 0xFFFFFFFF);
   }

   /*************************************************/
   void Sprite::setPosition(int x, int y)
   {
      this->x = x;
      this->y = y;
   }

   /*************************************************/
   void Sprite::setReferencePosition(int x, int y)
   {
      this->referenceX = x;
      this->referenceY = y;
   }

   /*************************************************/
   void Sprite::setZoom(float factor)
   {
      this->factor = factor;
   }
   
   /*************************************************/
   void Sprite::setRotation(float angle)
   {
      this->angle = angle;
   }
}

