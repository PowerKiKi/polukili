#include <Players/Player.h>

#include <Constants.h>
#include <Level.h>

namespace Polukili 
{
   namespace Players 
   {

      /*************************************************/
      Player::Player(Level* level)
         : Actor(level)
      {
         this->level->players.push_back(this);
      }
      
      /*************************************************/
      Player::~Player()
      {
         this->level->players.remove(this);
      }
      
      /*************************************************/
      void Player::initPhysic(float x, float y)
      {
         b2BodyDef bodyDef;
         bodyDef.position.Set(x / Constants::pixelsPerUnits, y / Constants::pixelsPerUnits); // arbitraire pour le y de toute facon il va tomber sur le ground
         this->body = level->world->CreateBody(&bodyDef);
         b2PolygonDef playerShape;
         playerShape.SetAsBox(this->getImageWidth() / Constants::pixelsPerUnits, this->getImageHeight() / Constants::pixelsPerUnits);

         playerShape.density = Constants::defaultDensity;
         playerShape.friction = Constants::defaultFriction;
         playerShape.restitution = Constants::defaultRestitution;

         this->body->CreateShape(&playerShape);
         this->body->SetMassFromShapes();
      }
      
      /*************************************************/
      string Player::getImagePath() const
      {
         return Constants::basePath + "player.png";
      }

      /*************************************************/
      int Player::getImageWidth() const
      {
         return 96;
      }

      /*************************************************/
      int Player::getImageHeight() const
      {
         return 48;
      }
      
   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

