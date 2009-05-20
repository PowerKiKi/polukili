#include <ImageLibrary.h>

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
         
      wsp::Image* image = new wsp::Image();
      if (image->LoadImage(filename.data()))
      {
         delete image;
         image = 0;
      }
      else
         this->images.insert(make_pair(filename, image));
      
      return image;
   }
   
   /*************************************************/
   void ImageLibrary::remove(const string& filename)
   {
      map<string, wsp::Image*>::iterator it = this->images.find(filename);
      if (it != this->images.end())
      {
         delete it->second;
         this->images.erase(it);
      }
   }
   
} /* End of namespace Polukili */

