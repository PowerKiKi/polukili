#include <Logger.h>

#include <Constants.h>

namespace Polukili 
{
   // Operations

      void Logger::init()
      {
       // TODO should delete previous file if any
      }
      
      void Logger::log(const string& input, ...)
      {
         va_list args;
         va_start(args, input);
         char buffer[1024];
         vsprintf(buffer, input.c_str(), args);
      
         printf("%s\n", buffer);
      }

} /* End of namespace Polukili */

