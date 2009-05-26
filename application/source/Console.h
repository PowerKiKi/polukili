/*
	Console class

	console (printf) support for libwiisprite
*/
#ifndef Console_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc
#define Console_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc

#include <BibScreenFont.h>
#include <fstream>

#define LOG_INFO __FILE__, __PRETTY_FUNCTION__, __LINE__

using namespace std;

namespace Polukili
{
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
