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
         va_start(args, input);
         char buffer[1024];
         vsprintf(buffer, input.c_str(), args);
         string to_log( buffer );
         
         // Print time
         const int l = 50;
         char buf[l];
         tm * pt;
         time_t t;
         time(&t);
         pt = localtime(&t);
         strftime(buf, l, "%Y-%m-%d %H:%M:%S ", pt);
                  
         fstream fp(Constants::logFilename.data(), ios::out | ios::app);
         fp << buf;
         fp << to_log << endl;
         fp.close();
      }

} /* End of namespace Polukili */

