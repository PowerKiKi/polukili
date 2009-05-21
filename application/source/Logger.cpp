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
         fstream fp(Constants::logFilename.data(),ios::app);
         fp << text << endl;
         fp.close();
      }

} /* End of namespace Polukili */

