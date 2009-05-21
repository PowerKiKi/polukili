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
      
      void Logger::log(const string& text)
      {
         printf("logged %s\n", text.data());
         fstream fp(Constants::logFilename.data(), ios::out | ios::app);
         printf("open fail %i\n", fp.fail());
         fp << text << endl;
         fp.close();
      }

} /* End of namespace Polukili */

