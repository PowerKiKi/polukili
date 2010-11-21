#include <Actor.h>

#include <Constants.h>
#include <Console.h>
#include <Game.h>
#include <Level.h>
#include <Sprite.h>

namespace Polukili 
{
   /*************************************************/
   Actor::Actor(Level* level)
      : level(level), body(0), sprite(0), state(normal), powerFactor(1)
   {
      Console::log(LOG_INFO, "Actor::Actor() - new actor");
      this->level->actors.push_back(this);      
   }
   
   /*************************************************/
   Actor::~Actor()
   {
      Console::log(LOG_INFO, "will destroy actor");
            
      this->level->actors.remove(this);
      
      if (this->body)
      {
         Console::log(LOG_INFO, "destroy physic");
         this->level->world->DestroyBody(this->body);    
         this->body = 0;
      }
      
      if (this->sprite)
      {
         Console::log(LOG_INFO, "destroy sprite");
         delete this->sprite;
         this->sprite = 0;
      }
      
      Console::log(LOG_INFO, "destroyed");
   }

   /*************************************************/
   void Actor::initPhysic(const b2Vec2& position, float32 angle)
   {
      this->timer.start();
      b2BodyDef bodyDef;
      basePosition = position;
      bodyDef.position = position;
      bodyDef.angle = angle;
	  bodyDef.type = b2_dynamicBody;
	  Console::log(LOG_INFO, "positon is: %f, %f", position.x, position.y);
      this->body = this->level->world->CreateBody(&bodyDef);
      this->body->SetUserData(this);
   }
   
   /*************************************************/
   void Actor::render()
   {
      this->sprite->setZoom(this->powerFactor);
      this->sprite->setRotation((float)this->body->GetAngle() / M_PI * 90.0);
      b2Vec2 pos = this->body->GetPosition();
      this->sprite->setPosition(Constants::pixelsPerUnits * pos.x, Constants::pixelsPerUnits * pos.y);
      this->sprite->draw();
   }

   /*************************************************/
   bool Actor::isDraggable()
   {
      return false;
   }

   /*************************************************/
   void Actor::loadGraphics()
   {
      GRRLIB_texImg* image = this->level->game->imageLibrary.get(this->getImagePath());
      this->sprite = new Sprite(image, this->getImageWidth(), this->getImageHeight());
      this->sprite->setReferencePosition(((int)this->getImageWidth()/2),(int)(this->getImageHeight()/2));
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
   
   /*************************************************/
   void Actor::isAttackedBy(int attackPower)
   {
      Console::log(LOG_INFO, "actor died");
      this->state = dead;
   }
   
   /*************************************************/
   void Actor::setPowerFactor(float powerFactor)
   {
      this->powerFactor = powerFactor;
   }
}

