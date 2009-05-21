#ifndef polukili_Logger_h_897eab33_e849_46f9_97c7_88a8d43bd9ca
#define polukili_Logger_h_897eab33_e849_46f9_97c7_88a8d43bd9ca

#include <string>

using namespace std;

namespace Polukili 
{

   /** 
   * 
   */
   class Logger 
   {
   public:

      static void init();
      static void log(const string& text);

      //end of class Effect
   };

} /* End of namespace Polukili */

#endif // polukili_Logger_h_897eab33_e849_46f9_97c7_88a8d43bd9ca

