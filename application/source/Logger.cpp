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

         std::string to_log( buffer );



         printf("logged %s\n", input.data());
         fstream fp(Constants::logFilename.data(), ios::out | ios::app);
         printf("open fail %i\n", fp.fail());
         fp << to_log << endl;
         fp.close();
      }

} /* End of namespace Polukili */

