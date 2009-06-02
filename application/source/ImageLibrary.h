#ifndef Polukili_ImageLibrary_h
#define Polukili_ImageLibrary_h


#include <map>
#include <string>

#include <wiisprite.h>

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
      * Desstructor.
      */
      virtual ~ImageLibrary();
      
      /*
      * Get an image from path. It will be loaded if needed.
      */
      wsp::Image* get(const string& filename);
      
      /*
      * Remove the image from library if it exist (deallocate memory)
      * If the image is not present in library, do nothing.
      **/
      void remove(const string& filename);
      

      // Attributes
   private:
      map<string, wsp::Image* > images;

      //end of class Game
   };

} /* End of namespace Polukili */

#endif 

