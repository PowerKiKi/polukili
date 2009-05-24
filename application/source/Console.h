/*
	Console class

	console (printf) support for libwiisprite
*/
#ifndef Console_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc
#define Console_h_0f2f4ee3_873c_48e0_afcf_deae99ae06dc

#include <BibScreenFont.h>
#include <fstream>

using namespace std;

class Console
{
public:
	void initialize(BibScreenFont* font);
	void render();
   void clear();
   
   static fstream logFile;
private:
	BibScreenFont* font;
};

#endif
