/*
	wsp_console class

	console (printf) support for libwiisprite
*/

#include <wiisprite.h>

#include <Console.h>

#include <Constants.h>
#include <Logger.h>

#include <sys/iosupport.h>

#define MAX_CON_ROWS	24
#define MAX_CON_COLS	80
#define X_PIXELS_PER_CHAR	(640/MAX_CON_COLS)
#define Y_PIXELS_PER_CHAR	(480/MAX_CON_ROWS)
#define TAB_SIZE		4

fstream wsp_Console::logFile; 

static int cursor_row = 0;
static int cursor_col = 0;
static int con_rows = MAX_CON_ROWS;
static int con_cols = MAX_CON_COLS;
static char the_console [MAX_CON_ROWS] [MAX_CON_COLS];

ssize_t wsp_console_write(struct _reent* rUnused, int fdUnused, const char* ptr, size_t len)
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
   wsp_Console::logFile << timeBuffer << ptr << endl;
   wsp_Console::logFile.flush();


	size_t i = 0;
	char *tmp = (char*)ptr;
	char chr;

	if (!tmp || len<=0)
		return -1;

	i = 0;
	while(*tmp!='\0' && i<len)
	{
		chr = *tmp++;
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
					if(cursor_col%TAB_SIZE)
						cursor_col += (cursor_col%TAB_SIZE);
					else 
						cursor_col += TAB_SIZE;
					break;
				default:
					the_console [cursor_row] [cursor_col] = chr;
					cursor_col++;

					if (cursor_col >= con_cols)
					{
						/* if right border reached wrap around */
						cursor_row++;
						cursor_col = 0;
					}
			}
		}

		if( cursor_row >= con_rows)
		{
			// Copy data up after reaching bottom.
			for (int i = 0; i < MAX_CON_ROWS - 1; i ++)
			{
				for (int j = 0; j < MAX_CON_COLS; j ++)
				{
					the_console [i] [j] = the_console [i + 1] [j];
				}
			}

			for (int j = 0; j < MAX_CON_COLS; j ++)
			{
				the_console [MAX_CON_ROWS - 1] [j] = 0;
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
	wsp_console_write,	// device write
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

void wsp_Console::InitConsole(BibScreenFont* font)
{
   this->font = font;
   cursor_row = 0;
   cursor_col = 0;

   //const unsigned int nSave = (unsigned int) (devoptab_list[STD_OUT]);

   devoptab_list[STD_OUT] = &wsp_dotab_stdout;
   devoptab_list[STD_ERR] = &wsp_dotab_stdout;

   setvbuf(stdout, NULL , _IONBF, 0);
   
   wsp_Console::logFile.open(Polukili::Constants::logFilename.data(), ios::out | ios::app);
}

void wsp_Console::RenderConsole (void)
{
int i, j;
char twoBuf [2];

	twoBuf [1] = 0;
	for (i = 0; i < MAX_CON_ROWS; i ++)
	{
		for (j = 0; j < MAX_CON_COLS; j ++)
		{
			if (the_console [i] [j])
			{
				twoBuf [0] = the_console [i] [j];
				this->font->DisplayText (j * X_PIXELS_PER_CHAR, i * Y_PIXELS_PER_CHAR, twoBuf);
			}
		}
	}

}
