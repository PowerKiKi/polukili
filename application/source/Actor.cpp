#include <Actor.h>

#include <Constants.h>
#include <Console.h>
#include <Game.h>
#include <Level.h>

namespace Polukili 
{

   // Operations
   
   /*************************************************/
   Actor::Actor(Level* level)
      : powerFactor(1)
   {
      Console::log(LOG_INFO, "Actor::Actor() - new actor");
      this->level = level;
      this->level->actors.push_back(this);
      
   }
   
   /*************************************************/
   Actor::~Actor()
   {
      this->level->actors.remove(this);
   }

   /*************************************************/
   void Actor::initPhysic(float x, float y)
   {
      this->timer = new Timer;
      b2BodyDef bodyDef;
      this->basePosition = new b2Vec2(x / Constants::pixelsPerUnits, y / Constants::pixelsPerUnits);
      bodyDef.position.Set(x / Constants::pixelsPerUnits, y / Constants::pixelsPerUnits); 
      this->body = level->world->CreateBody(&bodyDef);
      b2PolygonDef actorShape;
      actorShape.SetAsBox(((float)this->getImageWidth() * this->powerFactor / Constants::pixelsPerUnits) / 2.0f, ((float)this->getImageHeight() * this->powerFactor / Constants::pixelsPerUnits) / 2.0f);
      actorShape.density = Constants::defaultDensity;
      actorShape.friction = Constants::defaultFriction;
      actorShape.restitution = Constants::defaultRestitution;

      this->body->CreateShape(&actorShape);
      this->body->SetMassFromShapes();
   }
   
   /*************************************************/
   void Actor::render()
   {
      this->sprite->SetZoom(this->powerFactor);
      this->sprite->SetRotation((float)this->body->GetAngle() / M_PI * 90.0);
      b2Vec2 pos = body->GetPosition();
      this->sprite->SetPosition(Constants::pixelsPerUnits * pos.x, Constants::pixelsPerUnits * pos.y);
      this->sprite->Draw();
   }

   /*************************************************/
   bool Actor::isDraggable()
   {
      return false;
   }

   /*************************************************/
   void Actor::loadGraphics()
   {
      wsp::Image* image = this->level->game->imageLibrary.get(this->getImagePath());
      this->sprite = new wsp::Sprite();      
      this->sprite->SetImage(image, this->getImageWidth(), this->getImageHeight());
      this->sprite->SetRefPixelPositioning(wsp::REFPIXEL_POS_PIXEL);
      this->sprite->SetRefPixelPosition(((int)this->getImageWidth()/2),(int)(this->getImageHeight()/2));
   }

   /*************************************************/
   void Actor::unloadGraphics()
   {
      if (this->sprite)
      {
         delete this->sprite;
         this->sprite = 0;
      }
   
      this->level->game->imageLibrary.remove(this->getImagePath());
   }

   /*************************************************/
   void Actor::nextStep()
   {

   }

   /*************************************************/
   bool Actor::acceptDrop(Actor &actorToBeDropped)
   {
      return false;
   }

   /*************************************************/
   bool Actor::isWeak(Element element)
   {
      return false;
   }

   /*************************************************/
   bool Actor::isStrong(Element element)
   {
      return false;
   }

   /*************************************************/
   void Actor::dropped(int droppedActor)
   {

   }

   /*************************************************/
   void Actor::applyEffects()
   {

   }
   
   /*************************************************/
   string Actor::getImagePath() const
   {
      return Constants::basePath + "default.png";
   }

   /*************************************************/
   int Actor::getImageWidth() const
   {
      return 32;
   }

   /*************************************************/
   int Actor::getImageHeight() const
   {
      return 32;
   }

   /*************************************************/
   bool Actor::is(ActorState state)
   {
      return (this->state & state) == state;
   }
   
} /* End of namespace Polukili */

