#include <Constants.h>

namespace Polukili 
{
   
   const string Constants::logFilename(Constants::basePath + "polukili.log");
   
   const string Constants::basePath("/APPS/Polukili/data/");
   
   const int Constants::pixelsPerUnits = 15; 
      
   const float Constants::defaultGravity = 9.81f; 
            
   const float Constants::defaultDensity = 5.0f;
      
   const float Constants::defaultFriction  = 0.5f;
      
   const float Constants::defaultRestitution = 0.2f;
   
} /* End of namespace Polukili */
