#include <PeriodicTimer.h>

#include <Constants.h>
#include <Console.h>

#include <ogc/lwp_watchdog.h>

namespace Polukili
{
   /*************************************************/
   PeriodicTimer::PeriodicTimer()
      : nextExpiry(0)
   {
      this->setPeriod(1000);
      this->isExpired(); // to consume current period
   }

   /*************************************************/
   PeriodicTimer::PeriodicTimer(int period)
      : nextExpiry(0)
   {
      this->setPeriod(period);
      this->isExpired(); // to consume current period
   }

   /*************************************************/
   PeriodicTimer::~PeriodicTimer()
   {
      
   }
   
   /*************************************************/
   void PeriodicTimer::setPeriod(int period)
   {
      this->period = millisecs_to_ticks(period);
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
