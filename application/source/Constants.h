#ifndef polukili_Constant_h_5932f181_5c91_439d_82ad_c1b3e506a9bf
#define polukili_Constant_h_5932f181_5c91_439d_82ad_c1b3e506a9bf

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
      * Base path for data
      */
      static const string basePath;
      
      static const int pixelsPerUnits;
	
      static const float defaultGravity;
   
   };/* End of class Constants*/
} /* End of namespace Polukili*/

#endif // polukili_Constant_h_5932f181_5c91_439d_82ad_c1b3e506a9bf
