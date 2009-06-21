#include <ContactListener.h>

#include <Constants.h>
#include <Console.h>

#include <Actor.h>
#include <Bullets/Bullet.h>

namespace Polukili
{
   void ContactListener::Add(const b2ContactPoint* point)
   {
      Console::log(LOG_INFO, "hit");
      
      Actor* a1 = (Actor*)(point->fixtureA->GetBody()->GetUserData());
      Actor* a2 = (Actor*)(point->fixtureB->GetBody()->GetUserData());
      
      Bullets::Bullet* bullet = dynamic_cast<Bullets::Bullet*>(a1);
      Actor* actor = dynamic_cast<Actor*>(a2);
      
      if (!bullet)
      {
         bullet = dynamic_cast<Bullets::Bullet*>(a2);
         actor = dynamic_cast<Actor*>(a1);
      }
      
      if (bullet && actor)
      {
         Console::log(LOG_INFO, "bullets(%d) hits actor(%d)", bullet, actor);
         bullet->attacks(actor);
      }
      else if (bullet && !actor)
      {
         Console::log(LOG_INFO, "bullets(%d) hits wall", bullet);
         bullet->attacksWalls();
      }
      else
         Console::log(LOG_INFO, "other hit");
   }

   void ContactListener::Persist(const b2ContactPoint* point)
   {
   
   }

   void ContactListener::Remove(const b2ContactPoint* point)
   {
   
   }
}
