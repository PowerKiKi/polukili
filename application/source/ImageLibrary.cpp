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
      for (map<string, wsp::Image*>::iterator it = this->images.begin(); it != this->images.end(); it++)
         delete it->second;
      this->images.clear();
   }
   
   /*************************************************/
   wsp::Image* ImageLibrary::get(const string& filename)
   {
      map<string, wsp::Image*>::iterator it = this->images.find(filename);
      
      if (it != this->images.end())
         return it->second;
         
         
      Console::log(LOG_INFO, "loading %s", filename.c_str());
      wsp::Image* image = new wsp::Image();
      IMG_LOAD_ERROR err = image->LoadImage(filename.c_str());
      if (err == IMG_LOAD_ERROR_NONE)
      {
         Console::log(LOG_INFO, "ok");
         this->images.insert(make_pair(filename, image));
      }
      else
      {
         Console::log(LOG_INFO, "FAILED !");
         delete image;
         image = 0;
      }
      
      return image;
   }
   
   /*************************************************/
   void ImageLibrary::remove(const string& filename)
   {
      Console::log(LOG_INFO, "unloading %s", filename.c_str());
      map<string, wsp::Image*>::iterator it = this->images.find(filename);
      if (it != this->images.end())
      {
         delete it->second;
         this->images.erase(it);
      }
   }
   
} /* End of namespace Polukili */

