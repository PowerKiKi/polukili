#ifndef Polukili_Console_h
#define Polukili_Console_h

#include <fstream>

#include <grrlib.h>

#define LOG_INFO __FILE__, __PRETTY_FUNCTION__, __LINE__

using namespace std;

namespace Polukili
{
   /**
   *  Console (printf) support for libwiisprite
   */
   class Console
   {
   public:
      
      /**
      * Constructor.
      */
      Console();
   
      /**
      * Destructor.
      */
      virtual ~Console();

      static void log(const char* file, const char* function, int line, const string& input, ...);
      static ssize_t write(const string&, const char* prefix = 0);

      void initialize(GRRLIB_ttfFont* font);
      void render();
      void clear();
      
      /**
      * Enable or disable the console log feature. 
      * (Even when disabled printf() are redirected to log file, only Console::log() is disabled)
      */
      void enable(bool enabled);
      
      /**
      * Returns whether the console is enabled.
      */
      bool isEnabled() const;
      
      
      static fstream logFile;
   private:
      GRRLIB_ttfFont* font;
      static bool enabled;
   };
}

#endif
