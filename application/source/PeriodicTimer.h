#ifndef Polukili_PeriodicTimer_h
#define Polukili_PeriodicTimer_h

#include <gctypes.h>

using namespace std;

namespace Polukili
{
   /**
   * Timer Class
   */
   class PeriodicTimer
   {
   public:
      
      /**
      * Constructor with a period of 1 second.
      */
      PeriodicTimer();
      
      /**
      * Constructor for a periodic timer with period in milliseconds.
      */
      PeriodicTimer(int period);
      
      /**
      * Destructor.
      */
      ~PeriodicTimer();
      
      /**
      * Sets the period in milliseconds.
      */
      void setPeriod(int period);
      
      /**
      * Returns if the period is over. If true, the period must be consumed.
      */
      bool isExpired();
      
      /**
      * Reset the period starting now.
      */
      void reset();
      
   private:
      u64 period;
      u64 nextExpiry;
   };
}

#endif
