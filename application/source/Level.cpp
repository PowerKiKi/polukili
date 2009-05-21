#include <Level.h>

#include <string>

#include <mxml.h>
#include <Box2D.h>

#include <Logger.h>
#include <Constants.h>
#include <Game.h>
#include <ImageLibrary.h>

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
      : world(0), game(game), backgroundSprite(0), foregroundSprite(0)
   {
      // Nothing do to here
   }
   
   /*************************************************/
   Level::~Level()
   {
      this->unloadGraphics();
   
      while (!this->actors.empty())
         delete this->actors.front();
        
      if (this->world != 0)
         delete this->world;
   }
   
   void dump(mxml_node_t* child)
   {

      string t;
      if (child->type == MXML_CUSTOM)
         t = "";
      else if (child->type == MXML_ELEMENT)
         t = "MXML_ELEMENT";
      else if (child->type ==MXML_IGNORE )
         t = "MXML_IGNORE";
      else if (child->type ==MXML_INTEGER )
         t = "MXML_INTEGER";
      else if (child->type == MXML_OPAQUE)
         t = "MXML_OPAQUE";
      else if (child->type ==MXML_REAL )
         t = "MXML_REAL";
      else if (child->type == MXML_TEXT)
         t = "MXML_TEXT";
         Logger::log(t);
   }

   /*************************************************/
   void Level::loadFromXML(const string& filename)
   {   
      Logger::log("loadFromXML()");
      if (this->world != 0) 
         delete this->world;
         
      FILE* fp;
      mxml_node_t* tree = 0;
      mxml_node_t* data = 0;
      mxml_node_t* child = 0;
      
      fp = fopen(filename.data(), "r");
      tree = mxmlLoadFile(NULL, fp, MXML_IGNORE_CALLBACK);
      fclose(fp);
      
      Logger::log("loadFromXML() - file read");
      data = mxmlFindElement(tree, tree, "level", NULL, NULL, MXML_DESCEND);
      
      
      // Create the physic world and ground body
      b2AABB worldAABB;
      worldAABB.lowerBound.Set(0, 0);
      float width = (float)atof(mxmlElementGetAttr(data, "width"));
      float height = (float)atof(mxmlElementGetAttr(data, "height"));
      worldAABB.upperBound.Set(width, height);
      b2Vec2 gravity(0.0f, Constants::defaultGravity);
      bool doSleep = false;      
      this->world = new b2World(worldAABB, gravity, doSleep);
      b2BodyDef groundBodyDef;
      groundBodyDef.position.Set(0.0f, 0.0f);
      this->body = this->world->CreateBody(&groundBodyDef);
      Logger::log("loadFromXML() - physic world built");
      
      this->backgroundPath = mxmlElementGetAttr(data, "background");
      this->foregroundPath = mxmlElementGetAttr(data, "foreground");
      
      // Create physic shape for the level's ground
      Logger::log("loadFromXML() - shapes reading");
      data = mxmlFindElement(tree, tree, "physics", NULL, NULL, MXML_DESCEND);      
      for (child = data->child; child != 0; child = child->next)
      {            
         if (stricmp(child->value.element.name, "circle") == 0)
         {
         
            Logger::log("loadFromXML() - circle reading");
            float radius = (float)atof(mxmlElementGetAttr(child, "radius"));
            float x = (float)atof(mxmlElementGetAttr(child->child, "x"));
            float y = (float)atof(mxmlElementGetAttr(child->child, "y"));
            
            b2CircleDef circleDef;
            circleDef.radius = radius;
            circleDef.localPosition.Set(x, y);
            this->body->CreateShape(&circleDef);
            
            Logger::log("loadFromXML() - circle read (radius=%f x=%f y=%f)", radius, x, y);

         }
         else if (stricmp(child->value.element.name, "polygon") == 0)
         {
            Logger::log("loadFromXML() - polygon reading");
            b2PolygonDef polygonDef;
            polygonDef.vertexCount = 0;
            for (mxml_node_t* point = child->child; point != 0; point = point->next)
            {
               float x = (float)atof(mxmlElementGetAttr(point, "x"));
               float y = (float)atof(mxmlElementGetAttr(point, "y"));
               
               Logger::log("loadFromXML() - polygon reading before set");
               polygonDef.vertices[polygonDef.vertexCount++].Set(x, y);
               Logger::log("loadFromXML() - polygon reading after set value x:%f y:%f", polygonDef.vertices[polygonDef.vertexCount - 1].x, polygonDef.vertices[polygonDef.vertexCount - 1].y);
            }
            
            Logger::log("loadFromXML() - polygon reading before create shape ");
            //HERE IS THE BUG !!!!! TODO watching variables
            this->body->CreateShape(&polygonDef);
            
            Logger::log("loadFromXML() - polygon read");
         }
      }
      Logger::log("loadFromXML() - shapes read");
      
      // Create all actors
      data = mxmlFindElement(tree, tree, "actors", NULL, NULL, MXML_DESCEND);
      for (child = data->child; child != 0; child = child->next)
      {
         Actor* actor;
      
         const char* type = mxmlElementGetAttr(data, "type");
         
         // Players
         if (stricmp(type, "poupa") == 0)
            actor = new Players::Poupa(this);
         else if (stricmp(type, "luna") == 0)
            actor = new Players::Luna(this);
         else if (stricmp(type, "kiki") == 0)
            actor = new Players::Kiki(this);
         else if (stricmp(type, "lila") == 0)
            actor = new Players::Lila(this);
            
         // Ennemies
         else if (stricmp(type, "bee") == 0)
            actor = new Ennemies::Bee(this);
         else if (stricmp(type, "spider") == 0)
            actor = new Ennemies::Spider(this);
         else if (stricmp(type, "earthworm") == 0)
            actor = new Ennemies::Earthworm(this);
         else
            continue;
            
            
         float x = (float)atof(mxmlElementGetAttr(data->child, "x"));
         float y = (float)atof(mxmlElementGetAttr(data->child, "y"));
         actor->initPhysic(x, y);
         
         Ennemies::Ennemy* ennemy = dynamic_cast<Ennemies::Ennemy*>(actor);
         if (ennemy && stricmp(mxmlElementGetAttr(data, "isTarget"), "True") == 0)
            ennemy->setTarget(true);
      }
      Logger::log("loadFromXML() - actors read");
      
      mxmlDelete(tree);
      
      Logger::log("loadFromXML() - end");
   }
   
   /*************************************************/
   void Level::loadGraphics()
   {
      wsp::Image* image;
      image = this->game->imageLibrary.get(this->backgroundPath);
      if (image)
      {
         this->backgroundSprite = new wsp::Sprite();
         this->backgroundSprite->SetImage(image, image->GetWidth(), image->GetHeight());
      }
         
      image = this->game->imageLibrary.get(this->foregroundPath);
      if (image)
      {
         this->foregroundSprite = new wsp::Sprite();
         this->foregroundSprite->SetImage(image, image->GetWidth(), image->GetHeight());
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
      this->backgroundSprite->Draw();      
   
      for (list<Ennemies::Ennemy*>::iterator it = this->ennemies.begin(); it != this->ennemies.end(); it++)
         (*it)->render();
         
      for (list<Players::Player*>::iterator it = this->players.begin(); it != this->players.end(); it++)
         (*it)->render();
         
      for (list<Pets::Pet*>::iterator it = this->pets.begin(); it != this->pets.end(); it++)
         (*it)->render();
         
      for (list<Bullets::Bullet*>::iterator it = this->bullets.begin(); it != this->bullets.end(); it++)
         (*it)->render();
      
      this->foregroundSprite->Draw();
   }
   
   /*************************************************/
   void Level::nextStep()
   {
      list<Actor*> actorsToDelete;
   
      WPAD_ScanPads();
      
      // Each actors reacts to current situation
      for (list<Actor*>::iterator it = this->actors.begin(); it != this->actors.end(); it++)
      {
         (*it)->nextStep();
         if ((*it)->is(dead))
            actorsToDelete.push_back(*it);
      }
      
      // Delete all dead actors
      for (list<Actor*>::iterator it = actorsToDelete.begin(); it != actorsToDelete.end(); it++)
         delete *it;
      
      
      float32 timeStep = 1.0f / 60.0f;
      int32 iterations = 10;         
      this->world->Step(timeStep, iterations); // TODO these variables should be in Constants class
   }
   
   /*************************************************/
   bool Level::isFinished() const
   {
      // Each actors reacts to current situation
      for (list<Ennemies::Ennemy*>::const_iterator it = this->ennemies.begin(); it != this->ennemies.end(); it++)      
         if ((*it)->isTarget())
            return false;
            
      return true;
   }

} /* End of namespace Polukili */

