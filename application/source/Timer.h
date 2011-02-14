#ifndef Polukili_Timer_h
#define Polukili_Timer_h

#include <gctypes.h>

using namespace std;

namespace Polukili
{
   /**
   * Timer Class
   */
   class Timer
   {
   public:
      //Timer is automatically started on creation
      Timer();
      ~Timer();
      
      void start();
      void stop();
      bool isStarted();
      void reset();
      u32 getMilliseconds();
      u32 getSeconds();
      float getDefaultFreq();
      
   private:
      bool started;
      long long startTime;
      long long stopTime;
      long long getDiffTicks();
   };
}

#endif
