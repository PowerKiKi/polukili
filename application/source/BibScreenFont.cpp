/*

	BibScreenFont.cpp

*/

#include <wiisprite.h>
#include <Console.h>
#include "BibScreenFont.h"


void BibScreenFont::Initialize (wsp::Image * pImage, int innXLetterWidth, int innYLetterHeight, 
								const unsigned char * innCharWidths)
{
	nXLetterWidth = innXLetterWidth;
	nYLetterHeight = innYLetterHeight;
	nCharWidths = innCharWidths;
	AlphabetBitmap.SetImage (pImage, nXLetterWidth, nYLetterHeight);
}

/*
	Transparency has a range from 0x00 (invisible) to 0xFF (fully visible)
*/
void BibScreenFont::DisplayText (int nXScreenLoc, int nYScreenLoc, const char * szText, int nTransparency)
{
	// Loop for every character.
	for (int i = 0; szText [i]; i++)
	{
		char cChar = szText [i];
		if (cChar >= 128)
			cChar &= 0xEF;

		// Render each letter.
		AlphabetBitmap.SetPosition(nXScreenLoc, nYScreenLoc);
		AlphabetBitmap.SetFrame(cChar);
		AlphabetBitmap.SetTransparency (nTransparency);
		AlphabetBitmap.Draw();

		// Every time we blit a letter we need to move to the right 
		// for the start of the next blit
		nXScreenLoc += nCharWidths[(int)cChar];
	}
}

/*************************************************/
int BibScreenFont::getCharacterHeight() const
{
   return nYLetterHeight;
}
