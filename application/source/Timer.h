/*
   Timer Class

*/
#ifndef Timer_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc
#define Timer_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc
#include <gctypes.h>

using namespace std;

class Timer
{
public:
   //Timer is automaticaly started on creation
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

#endif
