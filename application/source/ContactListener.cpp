#include <ContactListener.h>

#include <Constants.h>
#include <Console.h>

#include <Actor.h>
#include <Bullets/Bullet.h>

namespace Polukili
{
   void ContactListener::Add(const b2ContactPoint* point)
   {
      Bullets::Bullet* bullet = static_cast<Bullets::Bullet*>(point->shape1->GetBody()->GetUserData());
      Actor* actor = static_cast<Actor*>(point->shape2->GetBody()->GetUserData());
      
      if (!bullet)
      {
         actor = static_cast<Actor*>(point->shape1->GetBody()->GetUserData());
         bullet = static_cast<Bullets::Bullet*>(point->shape2->GetBody()->GetUserData());
      }
      
      if (bullet && actor)
      {
         Console::log(LOG_INFO, "bullets(%d) hits actor(%d)", bullet, actor);
         bullet->attacks(actor);
      }
   }

   void ContactListener::Persist(const b2ContactPoint* point)
   {
   
   }

   void ContactListener::Remove(const b2ContactPoint* point)
   {
   
   }
}
