#include <Constants.h>

namespace Polukili 
{

   /*Sets the values of the constraints*/
   
   const string Constants::basePath("/APPS/Polukili/data/");
   
   // scale between Box2D units and Screen units(pixels)
   const int Constants::pixelsPerUnits = 15; 
   
   // Earth gravity
   const float Constants::defaultGravity = 9.81f; 
} /* End of namespace Polukili */
