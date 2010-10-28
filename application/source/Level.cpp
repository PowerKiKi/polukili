#include <Level.h>

#include <string>

#include <mxml.h>
#include <Box2D/Box2D.h>

#include <Console.h>
#include <Constants.h>
#include <Game.h>
#include <ImageLibrary.h>
#include <Sprite.h>

#include <CollisionCategories.h>
#include <Bullets/Bullet.h>
#include <Pets/Pet.h>
#include <Players/Player.h>
#include <Players/Poupa.h>
#include <Players/Luna.h>
#include <Players/Kiki.h>
#include <Players/Lila.h>
#include <Ennemies/Ennemy.h>
#include <Ennemies/Bee.h>
#include <Ennemies/Spider.h>
#include <Ennemies/Earthworm.h>


namespace Polukili 
{
   /*************************************************/
   Level::Level(Game* game)
      : world(0), game(game), backgroundSprite(0), foregroundSprite(0), body(0)
   {
      // Nothing do to here
   }
   
   /*************************************************/
   Level::~Level()
   {
      Console::log(LOG_INFO, "Level::~Level()");
      this->unloadGraphics();
   
      while (!this->actors.empty())
         delete this->actors.front();

      if (this->world != 0)
         delete this->world;
   }

   /*************************************************/
   void Level::loadFromXML(const string& filename)
   {   
      Console::log(LOG_INFO, "Level::loadFromXML() - filename=%s", filename.c_str());
      if (this->world != 0) 
         delete this->world;
         
      FILE* fp;
      mxml_node_t* tree = 0;
      mxml_node_t* data = 0;
      mxml_node_t* child = 0;
      
      fp = fopen(filename.c_str(), "r");
      tree = mxmlLoadFile(NULL, fp, MXML_IGNORE_CALLBACK);
      fclose(fp);
      
      Console::log(LOG_INFO, "Level::loadFromXML() - file read");
      data = mxmlFindElement(tree, tree, "level", NULL, NULL, MXML_DESCEND);
      
      
      // Create the physic world and ground body
      b2Vec2 gravity(0.0f, Constants::defaultGravity);
      bool doSleep = false;
      this->world = new b2World(gravity, doSleep);
      this->world->SetContactListener(&this->game->contactListener);
      this->world->SetDebugDraw(&this->game->debugDraw);
      b2BodyDef groundBodyDef;
      groundBodyDef.position.Set(0.0f, 0.0f);
      
      this->body = this->world->CreateBody(&groundBodyDef);
      Console::log(LOG_INFO, "Level::loadFromXML() - physic world built");
      
      this->backgroundPath = mxmlElementGetAttr(data, "background");
      this->foregroundPath = mxmlElementGetAttr(data, "foreground");
      
      // Create physic shape for the level's ground
      Console::log(LOG_INFO, "Level::loadFromXML() - shapes reading");
      data = mxmlFindElement(tree, tree, "physics", NULL, NULL, MXML_DESCEND);      
      for (child = data->child; child != 0; child = child->next)
      {            
         if (stricmp(child->value.element.name, "circle") == 0)
         {
         
            Console::log(LOG_INFO, "Level::loadFromXML() - circle reading");
            float radius = (float)atof(mxmlElementGetAttr(child, "radius"));
            float x = (float)atof(mxmlElementGetAttr(child->child, "x"));
            float y = (float)atof(mxmlElementGetAttr(child->child, "y"));
            
			
            b2CircleShape circleShape;
            circleShape.m_radius = radius / Constants::pixelsPerUnits;
            circleShape.m_p.Set(x / Constants::pixelsPerUnits, y / Constants::pixelsPerUnits);
            
			b2FixtureDef circleDef;
			circleDef.shape = &circleShape;
			circleDef.filter.categoryBits = ground;
            
            this->body->CreateFixture(&circleDef);
            
            Console::log(LOG_INFO, "Level::loadFromXML() - circle read (radius=%f x=%f y=%f)", radius, x, y);

         }
         else if (stricmp(child->value.element.name, "polygon") == 0)
         {
            Console::log(LOG_INFO, "Level::loadFromXML() - polygon reading");
            b2PolygonShape polygonShape;
            polygonShape.m_vertexCount = 0;
            for (mxml_node_t* point = child->child; point != 0; point = point->next)
            {
               float x = (float)atof(mxmlElementGetAttr(point, "x"));
               float y = (float)atof(mxmlElementGetAttr(point, "y"));
               
               Console::log(LOG_INFO, "Level::loadFromXML() - polygon reading before set");
               polygonShape.m_vertices[polygonShape.m_vertexCount++].Set(x / Constants::pixelsPerUnits, y / Constants::pixelsPerUnits);
               Console::log(LOG_INFO, "Level::loadFromXML() - polygon reading values x=%f y=%f", (float)polygonShape.m_vertices[polygonShape.m_vertexCount - 1].x, (float)polygonShape.m_vertices[polygonShape.m_vertexCount - 1].y);
            }


            for (int32 i = 0; i < polygonShape.m_vertexCount; ++i)
            {
               int32 i1 = i;
               int32 i2 = i + 1 < polygonShape.m_vertexCount ? i + 1 : 0;
               b2Vec2 edge = polygonShape.m_vertices[i2] - polygonShape.m_vertices[i1];
               Console::log(LOG_INFO, "Level::loadFromXML() - checking:  p1 x=%f p1 y=%f", (float)polygonShape.m_vertices[i1].x , (float)polygonShape.m_vertices[i1].y);
               Console::log(LOG_INFO, "Level::loadFromXML() - checking:  p2 x=%f p2 y=%f", (float)polygonShape.m_vertices[i2].x , (float)polygonShape.m_vertices[i2].y);
               Console::log(LOG_INFO, "Level::loadFromXML() - checking:  edge x=%f edge y=%f", (float)edge.x , (float)edge.y);
               Console::log(LOG_INFO, "Level::loadFromXML() - checking:  length=%f minimum=%f", (float)edge.LengthSquared() , (float)(FLT_EPSILON * FLT_EPSILON));
               
               
               //b2Assert(edge.LengthSquared() > B2_FLT_EPSILON * B2_FLT_EPSILON);
               //m_normals[i] = b2Cross(edge, 1.0f);
               //m_normals[i].Normalize();
            }

            
            Console::log(LOG_INFO, "Level::loadFromXML() - polygon vertex count=%d", polygonShape.m_vertexCount);
            Console::log(LOG_INFO, this->body ? "not null" : "null");
            
			
            b2FixtureDef polygonDef;
            polygonDef.shape = &polygonShape;
            polygonDef.filter.categoryBits   = ground;
            this->body->CreateFixture(&polygonDef);
            
            Console::log(LOG_INFO, "Level::loadFromXML() - polygon read");
         }
      }
      Console::log(LOG_INFO, "Level::loadFromXML() - shapes read");
      
      // Create all actors
      data = mxmlFindElement(tree, tree, "actors", NULL, NULL, MXML_DESCEND);
      
      int nbPlayers = 0;
      for (child = data->child; child != 0; child = child->next)
      {
         Console::log(LOG_INFO, "Level::loadFromXML() - actor reading");
         Actor* actor;
      
         const char* type = mxmlElementGetAttr(child, "type");
         if (type)
            Console::log(LOG_INFO, "Level::loadFromXML() - actor type=%s", type);
         else
         {
            Console::log(LOG_INFO, "Level::loadFromXML() - actor type '%s' not found. Actor skipped.", type);
            continue;
         }
         
         // Forbid too many players (otherwise will crash because wiimotes channels and doesn't make sense anyway)
         if (nbPlayers >= Constants::maximumPlayers &&
            (stricmp(type, "poupa") == 0 ||
            stricmp(type, "luna") == 0 ||
            stricmp(type, "kiki") == 0 ||
            stricmp(type, "lila") == 0)
         )
         {
            Console::log(LOG_INFO, "player type=%s skipped, because too many players already", type);
         }
         
         // Players
         if (stricmp(type, "poupa") == 0)
            actor = new Players::Poupa(this, WPAD_CHAN_0 + nbPlayers++);   
         else if (stricmp(type, "luna") == 0)
            actor = new Players::Luna(this, WPAD_CHAN_0 + nbPlayers++);
         else if (stricmp(type, "kiki") == 0)
            actor = new Players::Kiki(this, WPAD_CHAN_0 + nbPlayers++);
         else if (stricmp(type, "lila") == 0)
            actor = new Players::Lila(this, WPAD_CHAN_0 + nbPlayers++);
            
         // Ennemies
         else if (stricmp(type, "bee") == 0)
            actor = new Ennemies::Bee(this);
         else if (stricmp(type, "spider") == 0)
            actor = new Ennemies::Spider(this);
         else if (stricmp(type, "earthworm") == 0)
            actor = new Ennemies::Earthworm(this);
         else
         {
            Console::log(LOG_INFO, "Level::loadFromXML() - actor type unknown. Actor skipped.", type);
            continue;
         }
         
         float powerFactor = (float)atof(mxmlElementGetAttr(child, "powerFactor"));
         actor->setPowerFactor(powerFactor);
            
         Console::log(LOG_INFO, "Level::loadFromXML() - actor '%s' will init physic.", type);
         float x = (float)atof(mxmlElementGetAttr(child->child, "x"));
         float y = (float)atof(mxmlElementGetAttr(child->child, "y"));
         actor->initPhysic(b2Vec2(x / Constants::pixelsPerUnits, y / Constants::pixelsPerUnits));
         Console::log(LOG_INFO, "Level::loadFromXML() - actor '%s' init physic at position (%f, %f).", type, x, y);
         
         Ennemies::Ennemy* ennemy = dynamic_cast<Ennemies::Ennemy*>(actor);
         if (ennemy && stricmp(mxmlElementGetAttr(child, "isTarget"), "True") == 0)
            ennemy->setTarget(true);
            
         Console::log(LOG_INFO, "Level::loadFromXML() - actor read");
      }
      Console::log(LOG_INFO, "Level::loadFromXML() - actors read");
      
      mxmlDelete(tree);
      
      Console::log(LOG_INFO, "Level::loadFromXML() - end");
   }
   
   /*************************************************/
   void Level::loadGraphics()
   {
      GRRLIB_texImg* image;
      image = this->game->imageLibrary.get(this->backgroundPath);
      if (image)
      {
         this->backgroundSprite = new Sprite(image, image->w, image->h);
      }
         
      image = this->game->imageLibrary.get(this->foregroundPath);
      if (image)
      {
         this->foregroundSprite = new Sprite(image, image->w, image->h);
      }
      
      for (list<Actor*>::iterator it = this->actors.begin(); it != this->actors.end(); it++)
         (*it)->loadGraphics();
   }

   /*************************************************/
   void Level::unloadGraphics()
   {   
      if (this->backgroundSprite)
      {
         delete this->backgroundSprite;
         this->backgroundSprite = 0;
      }
      
      if (this->foregroundSprite)
      {
         delete this->foregroundSprite;         
         this->foregroundSprite = 0;
      }
         
      this->game->imageLibrary.remove(this->backgroundPath);
      this->game->imageLibrary.remove(this->foregroundPath);
      
      for (list<Actor*>::iterator it = this->actors.begin(); it != this->actors.end(); it++)
         (*it)->unloadGraphics();
   }
   
   /*************************************************/
   void Level::render()
   {   
      Console::log(LOG_INFO, "Level::render() - begin");
      
      if (this->backgroundSprite)
         this->backgroundSprite->draw();
   
      for (list<Ennemies::Ennemy*>::iterator it = this->ennemies.begin(); it != this->ennemies.end(); it++)
         (*it)->render();
         
      for (list<Players::Player*>::iterator it = this->players.begin(); it != this->players.end(); it++)
         (*it)->render();
         
      for (list<Pets::Pet*>::iterator it = this->pets.begin(); it != this->pets.end(); it++)
         (*it)->render();
         
      for (list<Bullets::Bullet*>::iterator it = this->bullets.begin(); it != this->bullets.end(); it++)
         (*it)->render();
      
      if (this->foregroundSprite)
         this->foregroundSprite->draw();

      Console::log(LOG_INFO, "Level::render() - end");
   }
   
   /*************************************************/
   void Level::nextStep()
   {
      Console::log(LOG_INFO, "Level::nextStep() - level nextStep begin");
      list<Actor*> actorsToDelete;
      
      // Each actors reacts to current situation
      for (list<Actor*>::iterator it = this->actors.begin(); it != this->actors.end(); it++)
      {
         (*it)->nextStep();
         if ((*it)->is(dead))
            actorsToDelete.push_back(*it);
      }
      
      
      Console::log(LOG_INFO, "destroy dead actors");
      // Delete all dead actors
      while (!actorsToDelete.empty())
      {
         Console::log(LOG_INFO, "will destroy dead actor");
         delete actorsToDelete.front();
         actorsToDelete.pop_front();         
         Console::log(LOG_INFO, "dead actor destroyed");
      }      
      
      
      Console::log(LOG_INFO, "nextstep physic with %d actors", this->actors.size());
      Console::log(LOG_INFO, "this->world->Step(%f, %d, %d);", Constants::timeStep, Constants::iterations, Constants::iterations);
      this->world->Step(Constants::timeStep, Constants::iterations, Constants::iterations);
      this->world->ClearForces();
      Console::log(LOG_INFO, "nextstep physic end");
   }
   
   /*************************************************/
   bool Level::isFinished() const
   {
      return false; // For now we prevent level to finish. TODO remove this security and test level changing
   
      for (list<Ennemies::Ennemy*>::const_iterator it = this->ennemies.begin(); it != this->ennemies.end(); it++)      
         if ((*it)->isTarget())
            return false;
            
      
      Console::log(LOG_INFO, "nextStep() - level is finished");
      return true;
   }

} /* End of namespace Polukili */

