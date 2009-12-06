#ifndef Polukili_ContactListener_h
#define Polukili_ContactListener_h

#include <Box2D.h>

using namespace std;

namespace Polukili
{
   class ContactListener : public b2ContactListener
   {
   public:
      void BeginContact(b2Contact* contact);
   };
}

#endif
