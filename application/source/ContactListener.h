#ifndef Polukili_ContactListener_h
#define Polukili_ContactListener_h

#include <Box2D.h>

using namespace std;

namespace Polukili
{
   class ContactListener : public b2ContactListener
   {
   public:
      void Add(const b2ContactPoint* point);
      void Persist(const b2ContactPoint* point);
      void Remove(const b2ContactPoint* point);
   };
}

#endif
