/*

	BibScreenFont.h


	This class was designed around two ideas.
	1.  It uses LibWiiSprite for screen drawing details and assumes the 
		correct header file <wiisprite.h> is in place as well as the library.
	2.  It was designed to work with output of F2IBuilder ( http://sourceforge.net/projects/f2ibuilder/ ).


	F2IBuilder can output two files, a PNG and a Metrics file.
	This class expects the two files to be run through raw2c.exe (from DevKitPro)
	and included(.h) and compiled(.c) into the project.
	The png data should be loaded into a wsp Image class via LoadImage.
	The metrics data should be passed directly as the nCharWidths parameter to Initialize.
	
	
	Initialize() should be called first and only once.
	DisplayText() should be called to display text for the current frame.

*/


#ifndef _BIBSCREENFONT_H_
#define _BIBSCREENFONT_H_

#include <wiisprite.h>

class BibScreenFont
{
private:
	wsp::Sprite AlphabetBitmap;
	int nXLetterWidth;
	int nYLetterHeight;
	const unsigned char * nCharWidths;	// Array of [128]
	int nCharsPerLine;

public:

	void Initialize (wsp::Image * pImage, int nXLetterWidth, int nYLetterHeight, 
					const unsigned char * nCharWidths);
	void DisplayText(int nXScreenLoc, int nYScreenLoc, const char * szText, int nTransparency = 0xFF);
   
   /**
   * Returns the height in pixels of a character.
   */
   int getCharacterHeight() const;


};
#endif

