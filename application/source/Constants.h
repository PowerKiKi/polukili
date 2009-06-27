#ifndef Polukili_Constant_h
#define Polukili_Constant_h

#include <string>

using namespace std;

namespace Polukili
{
   /** 
   * Contains all the default constraints for physics, Level, players, enemies, etc.
   */
   class Constants 
   {
   public :
   
   
      /**
      * Full path to the lof file.
      */
      static const string logFilename;
   
      /**
      * Base path for data
      */
      static const string basePath;
      
	   // scale between Box2D units and Screen units(pixels)
      static const int pixelsPerUnits;
      
      // Earth gravity
      static const float defaultGravity;
      
      
      static const float defaultDensity;
      
      static const float defaultFriction;
      
      static const float defaultRestitution;
      
      static const float defaultImpulseSpeed;
   
      static const float timeStep;
      
      static const int iterations;   
      
      /**
      * The maximum numbers of players in one level. (this should never ever change unless the wii get more wiimotes)
      */
      static const int maximumPlayers;
      
      /**
      * The margin in pixels applied on the physical world to be sure that no body will be create out of the world.
      */
      static const int physicMargin;
   
   };/* End of class Constants*/
} /* End of namespace Polukili*/

#endif 
