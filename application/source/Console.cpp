/*
	Console class

	console (printf) support for libwiisprite
*/
#include <Console.h>

#include <sys/iosupport.h>
#include <wiisprite.h>

#include <Constants.h>
#include <Logger.h>


fstream Console::logFile;

static const int tabSize = 4;
static const int maximumRows = 24;
static const int maximumColumns = 80;
static int cursor_row = 0;
static int cursor_col = 0;
static char the_console[maximumRows][maximumColumns + 1];

ssize_t Console_write(struct _reent* rUnused, int fdUnused, const char* ptr, size_t len)
{
   // Get timestamp
   const int l = 50;
   char timeBuffer[l];
   tm * pt;
   time_t t;
   time(&t);
   pt = localtime(&t);
   strftime(timeBuffer, l, "%Y-%m-%d %H:%M:%S ", pt);
   
   // Log message in logfile
   Console::logFile << timeBuffer << ptr << endl;
   Console::logFile.flush();


	
	char *tmp = (char*)ptr;

	if (!tmp || len<=0)
		return -1;

	size_t i = 0;
	while(*tmp != '\0' && i < len)
	{		
      char chr = *tmp++;
		i++;
		if ( (chr == 0x1b) && (*tmp == '[') )
		{
			/* escape sequence found */
			int k;

			tmp++;
			i++;
			k = 0; //__console_parse_escsequence(tmp);		//!!! Ignore.
			tmp += k;
			i += k;
		}
		else
		{
         the_console[cursor_row][cursor_col] = '\0'; // Default the character to end of string to avoid overflow when reading
			switch(chr)
			{
				case '\n':
					cursor_row++;
					cursor_col = 0;
					break;
				case '\r':
					cursor_col = 0;
					break;
				case '\b':
					cursor_col--;
					if(cursor_col < 0)
					{
						cursor_col = 0;
					}
					break;
				case '\f':
					cursor_row++;
					break;
				case '\t':
               // Fill the gap for tab with spaces, but do not overflow if tab is the last character of the line
               {
                  int gapSize = (cursor_col % tabSize) ? (cursor_col % tabSize) : tabSize;               
                  for (int g = 0; g < gapSize && cursor_col < maximumColumns; g++)
                     the_console[cursor_row][cursor_col++] = ' ';
               }
               the_console[cursor_row][cursor_col] = '\0';
                  
					break;
				default:
					the_console[cursor_row][cursor_col] = chr;
					cursor_col++;

					if (cursor_col >= maximumColumns)
					{
						/* if right border reached wrap around */
						cursor_row++;
						cursor_col = 0;
					}
			}
		}

		if (cursor_row >= maximumRows)
		{
			// Copy data up after reaching bottom.
			for (int i = 0; i < maximumRows - 1; i ++)
			{
				for (int j = 0; j < maximumColumns; j ++)
				{
					the_console [i] [j] = the_console [i + 1] [j];
				}
			}

			for (int j = 0; j < maximumColumns; j ++)
			{
				the_console [maximumRows - 1] [j] = 0;
			}

			cursor_row--;
		}
	}

	return i;
}


const devoptab_t wsp_dotab_stdout =
{
//---------------------------------------------------------------------------------
	"stdout",	// device name
	0,			// size of file structure
	NULL,		// device open
	NULL,		// device close
	Console_write,	// device write
	NULL,		// device read
	NULL,		// device seek
	NULL,		// device fstat
	NULL,		// device stat
	NULL,		// device link
	NULL,		// device unlink
	NULL,		// device chdir
	NULL,		// device rename
	NULL,		// device mkdir
	0,			// dirStateSize
	NULL,		// device diropen_r
	NULL,		// device dirreset_r
	NULL,		// device dirnext_r
	NULL,		// device dirclose_r
	NULL		// device statvfs_r
};

/*************************************************/
void Console::initialize(BibScreenFont* font)
{
   this->font = font;
   cursor_row = 0;
   cursor_col = 0;

   devoptab_list[STD_OUT] = &wsp_dotab_stdout;
   devoptab_list[STD_ERR] = &wsp_dotab_stdout;

   setvbuf(stdout, NULL , _IONBF, 0);
   
   Console::logFile.open(Polukili::Constants::logFilename.data(), ios::out);
   this->clear();
}

/*************************************************/
void Console::render()
{

Console::logFile << "char size=" <<  this->font->getCharacterHeight() << endl;
	for (int i = 0; i < maximumRows; i ++)
	{
      this->font->DisplayText(0, i * this->font->getCharacterHeight(), the_console[i]);
   }
}

/*************************************************/
void Console::clear()
{
	for (int i = 0; i < maximumRows; i ++)
	{
      the_console[i][0] = '\0';
      the_console[i][maximumColumns] = '\0';
   }   
}
