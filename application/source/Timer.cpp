#include <Timer.h>

#include <Constants.h>

#include <ogc/lwp_watchdog.h>

namespace Polukili
{

   Timer::Timer()
   {
      this->startTime = gettime();
      this->started = true;
   }

   Timer::~Timer()
   {

   }

      
   void Timer::start()
   {
      
      this->startTime = gettime();
      this->started = true;
   }
   void Timer::stop()
   {
      this->stopTime = gettime();
      this->started = false;
   }
   bool Timer::isStarted()
   {
      return this->started;
   }
   void Timer::reset()
   {
      Timer::start();
   }
   long long Timer::getDiffTicks()
   {
      if(this->started)
      {
         return diff_ticks(this->startTime,gettime());
      }
      else
      {
         return diff_ticks(this->startTime,this->stopTime);
      }
   }
   u32 Timer::getMilliseconds()
   {
      return ticks_to_millisecs(getDiffTicks());
   }

   u32 Timer::getSeconds()
   {
      return ticks_to_secs(getDiffTicks());
   }
   
   float Timer::getDefaultFreq()
   {
      return (float)(ticks_to_millisecs(getDiffTicks())*1000) * Polukili::Constants::timeStep;
   }
}
