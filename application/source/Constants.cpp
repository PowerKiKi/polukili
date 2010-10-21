#include <Constants.h>

namespace Polukili 
{
   const string Constants::basePath("/APPS/Polukili/DATA/");   
   const string Constants::logFilename(Constants::basePath + "polukili.log");   
   const int Constants::pixelsPerUnits = 48;       
   const float Constants::defaultGravity = 1.81f;
   const float Constants::defaultDensity = 5.0f;      
   const float Constants::defaultFriction  = 0.5f;      
   const float Constants::defaultRestitution = 0.2f;   
   const float Constants::defaultImpulseSpeed = 10.0f;
   const float Constants::timeStep = 1.0f / 60.0f;
   const int Constants::iterations = 10;
   const int Constants::maximumPlayers = 4;
   const int Constants::physicMargin = 640;
} /* End of namespace Polukili */
