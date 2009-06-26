#include <PeriodicTimer.h>

#include <Constants.h>
#include <Console.h>

#include <ogc/lwp_watchdog.h>

namespace Polukili
{

   /*************************************************/
   PeriodicTimer::PeriodicTimer(int period)
      : period(millisecs_to_ticks(period))
   {
      this->reset();
   }

   /*************************************************/
   PeriodicTimer::~PeriodicTimer()
   {
      
   }

   /*************************************************/
   bool PeriodicTimer::isExpired()
   {
      u64 now = gettime();
      bool expired = now >= this->nextExpiry;      
      if (expired)
         this->nextExpiry += (((now - this->nextExpiry) / this->period) + 1) * this->period;
         
      return expired;
   }
   
   /*************************************************/
   void PeriodicTimer::reset()
   {
      this->nextExpiry = gettime() + this->period;
   }
}
