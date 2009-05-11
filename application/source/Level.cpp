#include "Level.h"

#include <mxml.h>

namespace Polukili 
{
   /*************************************************/
   Level::Level()
   : Actor(this)
   {
   
   }

   /*************************************************/
   void Level::loadFromXML(const char* filename)
   {
      FILE *fp;
      mxml_node_t *tree;
      mxml_node_t *data;
      mxml_node_t *group;
      
         
      fp = fopen(filename, "r");
      tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
      fclose(fp);


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

