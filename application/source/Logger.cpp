#include <Logger.h>
#include <fstream>

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
         va_start( args, input );
         char buffer[1024];
         vsprintf( buffer, input.c_str(), args );
         string to_log( buffer );
         fstream fp(Constants::logFilename.data(), ios::out | ios::app);
         fp << to_log << endl;
         fp.close();
      }

} /* End of namespace Polukili */

