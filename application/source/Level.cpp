#include <Level.h>

#include <mxml.h>
#include <Box2D.h>


#include <Players/Player.h>
#include <Players/Poupa.h>
#include <Players/Luna.h>
#include <Players/Kiki.h>
#include <Players/Lila.h>
#include <Ennemies/Bee.h>
#include <Ennemies/Spider.h>

namespace Polukili 
{
   /*************************************************/
   Level::Level()
   : Actor(this), world(0)
   {
      // Nothing do to here
   }

   /*************************************************/
   void Level::loadFromXML(const char* filename)
   {
      if (this->world != 0) 
         delete this->world;
         
      FILE* fp;
      mxml_node_t* tree = 0;
      mxml_node_t* data = 0;
      mxml_node_t* child = 0;
      
      fp = fopen(filename, "r");
      tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
      fclose(fp);
      
      data = mxmlFindElement(tree, tree, "level", NULL, NULL, MXML_DESCEND);
      
      
      // Create the physic world and ground body
      b2AABB worldAABB;
      worldAABB.lowerBound.Set(0, 0);
      float width = (float)atof(mxmlElementGetAttr(data, "width"));
      float height = (float)atof(mxmlElementGetAttr(data, "height"));
      worldAABB.upperBound.Set(width, height);
      b2Vec2 gravity(0.0f, 10.0f);
      bool doSleep = false;      
      this->world = new b2World(worldAABB, gravity, doSleep);      
      b2BodyDef groundBodyDef;
      groundBodyDef.position.Set(0.0f, 0.0f);
      this->body = this->world->CreateBody(&groundBodyDef);
      
      
      // Create physic shape for the level's ground
      data = mxmlFindElement(tree, tree, "physics", NULL, NULL, MXML_DESCEND);
      for (child = data->child; child != 0; child = child->next)
      {
         if (strcmp(child->value.element.name, "circle") == 0)
         {
            float radius = (float)atof(mxmlElementGetAttr(child, "radius"));
            float x = (float)atof(mxmlElementGetAttr(child->child, "x"));
            float y = (float)atof(mxmlElementGetAttr(child->child, "y"));
            
            b2CircleDef def;
            def.radius = radius;
            def.localPosition.Set(x, y);

         }
         else if (strcmp(child->value.element.name, "polygon") == 0)
         {
            b2PolygonDef polygonDef;
            polygonDef.vertexCount = 0;
            for (mxml_node_t* point = data->child; point != 0; point = point->next)
            {
               float x = (float)atof(mxmlElementGetAttr(point, "x"));
               float y = (float)atof(mxmlElementGetAttr(point, "y"));
               polygonDef.vertices[polygonDef.vertexCount++].Set(x, y);
            }
            
            this->body->CreateShape(&polygonDef);
         }
      }
      
      // Create all actors
      data = mxmlFindElement(tree, tree, "actors", NULL, NULL, MXML_DESCEND);
      for (child = data->child; child != 0; child = child->next)
      {
         Actor* actor;
      
         const char* type = mxmlElementGetAttr(data, "type");
         
         if (strcmp(type, "poupa") == 0)
            actor = new Players::Poupa(this);/*
         else if (strcmp(type, "luna") == 0)
            actor = new Players::Luna();
         else if (strcmp(type, "kiki") == 0)
            actor = new Players::Kiki();
         else if (strcmp(type, "lila") == 0)
            actor = new Players::Lila();
            
         else if (strcmp(type, "bee") == 0)
            actor = new Ennemies::Bee();
         else if (strcmp(type, "spider") == 0)
            actor = new Ennemies::Spider();
         else if (strcmp(type, "bee") == 0)
            actor = new Ennemies::Bee();
         else if (strcmp(type, "bee") == 0)
            actor = new Ennemies::Bee();*/
                  
         
         (mxmlElementGetAttr(data, "isTarget"));
      }
      
      mxmlDelete(tree);
   }

   /*************************************************/
   void Level::initPhysic()
   {
      ; // Nothing to do, everything was done during xml reading
   }
   
   /*************************************************/
   void Level::loadGraphics()
   {
      
   }

   /*************************************************/
   void Level::unloadGraphics()
   {
      
   }

} /* End of namespace Polukili */

