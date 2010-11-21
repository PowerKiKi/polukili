#ifndef Polukili_ImageLibrary_h
#define Polukili_ImageLibrary_h

#include <map>
#include <string>

#include <grrlib.h>

using namespace std;

namespace Polukili 
{

   /** 
   *  A library containing Images and allowing to get Image from path with implicit load.
   */
   class ImageLibrary
   {
   
   public: 
      
      /*
      * Constructor.
      */
      ImageLibrary();
      
      /*
      * Destructor.
      */
      virtual ~ImageLibrary();
      
      /*
      * Get an image from path. It will be loaded if needed.
      */
      GRRLIB_texImg* get(const string& filename);
      
      /*
      * Remove the image from library if it exist (deallocate memory)
      * If the image is not present in library, do nothing.
      **/
      void remove(const string& filename);
      

      // Attributes
   private:
      map<string, GRRLIB_texImg* > images;

      //end of class Game
   };

} 

#endif 

