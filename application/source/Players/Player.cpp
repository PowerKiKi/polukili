#include <Players/Player.h>

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
        // TODO: should do something here
        	b2BodyDef bodyDef;
         bodyDef.position.Set(x/Constants::pixelsPerUnits, y/Constants::pixelsPerUnits); // arbitraire pour le y de toute facon il va tomber sur le ground
         this->body = level->world->CreateBody(&bodyDef);
         b2PolygonDef playerShape;
         persoShape.SetAsBox(this->getImageWidth()/Constants::pixelsPerUnits,this->getImageHeight()/Constants::pixelsPerUnits);
	
         persoShape.density = Constants::defaultDensity;
         persoShape.friction = Constants::defaultFriction;
         persoShape.restitution = Constants::defaultRestitution;
         
         this->body->CreateShape(&playerShape);
         this->body->SetMassFromShapes();
      }
      
   } /* End of namespace Polukili::Players */
} /* End of namespace Polukili */

