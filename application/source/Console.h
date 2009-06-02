#ifndef Polukili_Console_h
#define Polukili_Console_h

#include <BibScreenFont.h>
#include <fstream>

#define LOG_INFO __FILE__, __PRETTY_FUNCTION__, __LINE__

using namespace std;

namespace Polukili
{
   /**
   *	console (printf) support for libwiisprite
   */
   class Console
   {
   public:

      static void log(const char* file, const char* function, int line, const string& input, ...);
      static ssize_t write(const string&, const char* prefix = 0);

      void initialize(BibScreenFont* font);
      void render();
      void clear();
      
      
      static fstream logFile;
   private:
      BibScreenFont* font;
   };
}

#endif
