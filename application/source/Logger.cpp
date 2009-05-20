#include <Logger.h>

namespace Polukili 
{
   // Operations

      void Logger::init()
      {
       // TODO should delete previous file if any
      }
      
      void Logger::log(const string& text)
      {
         fp = fopen(Constants::logFilename.data(), "a");
         fwrite(fp, text.data());
         fwrite(fp, "\n");
         fclose(fp);
      }

} /* End of namespace Polukili */

