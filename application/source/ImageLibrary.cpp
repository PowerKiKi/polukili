#include <ImageLibrary.h>

#include <Console.h>

namespace Polukili 
{

   /*************************************************/
   ImageLibrary::ImageLibrary()
   {
      // Nothing to do here
   }
   
   /*************************************************/
   ImageLibrary::~ImageLibrary()
   {      
      for (map<string, GRRLIB_texImg*>::iterator it = this->images.begin(); it != this->images.end(); it++)
    	  GRRLIB_FreeTexture(it->second);
      this->images.clear();
   }
   
   /*************************************************/
   GRRLIB_texImg* ImageLibrary::get(const string& filename)
   {
      map<string, GRRLIB_texImg*>::iterator it = this->images.find(filename);
      
      if (it != this->images.end())
         return it->second;
         
         
      Console::log(LOG_INFO, "loading %s", filename.c_str());
      GRRLIB_texImg* image = GRRLIB_LoadTextureFromFile(filename.c_str());
      if (image != 0)
      {
         Console::log(LOG_INFO, "ok");
         this->images.insert(make_pair(filename, image));
      }
      else
      {
         Console::log(LOG_INFO, "FAILED !");
      }
      
      return image;
   }
   
   /*************************************************/
   void ImageLibrary::remove(const string& filename)
   {
      Console::log(LOG_INFO, "unloading %s", filename.c_str());
      map<string, GRRLIB_texImg*>::iterator it = this->images.find(filename);
      if (it != this->images.end())
      {
    	 GRRLIB_FreeTexture(it->second);
         this->images.erase(it);
      }
   }
   
} /* End of namespace Polukili */

