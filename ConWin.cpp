//--------------------------------------------------------------------
// $Id: ConWin.cpp 4592 2005-03-12 17:11:36Z cjm $
//--------------------------------------------------------------------
//
//   VBinDiff
//   Copyright 1997 by Christopher J. Madsen
//
//   Support class for console mode applications
//
//--------------------------------------------------------------------

#include <stdlib.h>

#include "ConWin.hpp"

enum ColorPair {
  pairWhiteBlue= 1,
  pairBlackWhite,
  pairRedBlue,
  pairYellowBlue
};

static const ColorPair colorStyle[] = {
  pairWhiteBlue,   // cBackground
  pairWhiteBlue,   // cPromptWin
  pairWhiteBlue,   // cPromptKey
  pairWhiteBlue,   // cPromptBdr
  pairBlackWhite,  // cLocked
  pairBlackWhite,  // cFileName
  pairWhiteBlue,   // cFileWin
  pairRedBlue,     // cFileDiff
  pairYellowBlue   // cFileEdit
};

static const attr_t attribStyle[] = {
           COLOR_PAIR(colorStyle[ cBackground ]),
           COLOR_PAIR(colorStyle[ cPromptWin  ]),
  A_BOLD | COLOR_PAIR(colorStyle[ cPromptKey  ]),
  A_BOLD | COLOR_PAIR(colorStyle[ cPromptBdr  ]),
           COLOR_PAIR(colorStyle[ cLocked     ]),
           COLOR_PAIR(colorStyle[ cFileName   ]),
           COLOR_PAIR(colorStyle[ cFileWin    ]),
  A_BOLD | COLOR_PAIR(colorStyle[ cFileDiff   ]),
  A_BOLD | COLOR_PAIR(colorStyle[ cFileEdit   ])
};

//====================================================================
// Class ConWindow:
//--------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////
// Static Member Functions:
//--------------------------------------------------------------------
// Start up the window system:
//
// Allocates a screen buffer and sets input mode:
//
// Returns:
//   true:   Everything set up properly
//   false:  Unable to initialize

bool ConWindow::startup()
{
  if (!initscr()) return false; // initialize the curses library
  atexit(ConWindow::shutdown);  // just in case

  keypad(stdscr, TRUE);  /* enable keyboard mapping */
  nonl();         /* tell curses not to do NL->CR/NL on output */
  cbreak();       /* take input chars one at a time, no wait for \n */
  noecho();         /* echo input - in color */

  if (!has_colors()) return false; // FIXME

  start_color();

  /*
   * Simple color assignment, often all we need.  Color pair 0 cannot
   * be redefined.  This example uses the same value for the color
   * pair as for the foreground color, though of course that is not
   * necessary:
   */
  init_pair(pairWhiteBlue,  COLOR_WHITE,  COLOR_BLUE);
  init_pair(pairBlackWhite, COLOR_BLACK,  COLOR_WHITE);
  init_pair(pairRedBlue,    COLOR_RED,    COLOR_BLUE);
  init_pair(pairYellowBlue, COLOR_YELLOW, COLOR_BLUE);

  return true;
} // end ConWindow::startup

//--------------------------------------------------------------------
// Shut down the window system:
//
// Deallocate the screen buffer and restore the original input mode.

void ConWindow::shutdown()
{
  if (!isendwin()) {
    showCursor();
    endwin();
  }
} // end ConWindow::shutdown

//////////////////////////////////////////////////////////////////////
// Member Functions:
//--------------------------------------------------------------------
// Constructor:

ConWindow::ConWindow()
: pan(NULL),
  win(NULL)
{
} // end ConWindow::ConWindow

//--------------------------------------------------------------------
// Destructor:

ConWindow::~ConWindow()
{
  close();
} // end ConWindow::~ConWindow

//--------------------------------------------------------------------
// Initialize the window:
//
// Must be called only once, before any other functions are called.
// Allocates the data structures and clears the window buffer, but
// does not display anything.
//
// Input:
//   x,y:           The position of the window in the screen buffer
//   width,height:  The size of the window
//   attrib:        The default attributes for the window

void ConWindow::init(short x, short y, short width, short height, Style attrib)
{
  if ((win = newwin(height, width, y, x)) == 0)
    exit(98);                   // FIXME

  if ((pan = new_panel(win)) == 0)
    exit(99);                 // FIXME

  wbkgdset(win, attribStyle[attrib] | ' ');

  keypad(win, TRUE);            // enable keyboard mapping

  clear();
} // end ConWindow::init

//--------------------------------------------------------------------
void ConWindow::close()
{
  if (pan) {
    del_panel(pan);
    pan = NULL;
  }

  if (win) {
    delwin(win);
    win = NULL;
  }
} // end ConWindow::close

//--------------------------------------------------------------------
// Write a string using the current attributes:
//
// Input:
//   x,y:  The start of the string in the window
//   s:    The string to write

//void ConWindow::put(short x, short y, const char* s)

///void ConWindow::put(short x, short y, const String& s)
///{
///  PCHAR_INFO  out = data + x + size.X * y;
///  StrConstItr  c = s.begin();
///
///  while (c != s.end()) {
///    out->Char.AsciiChar = *c;
///    out->Attributes = attribs;
///    ++out;
///    ++c;
///  }
///} // end ConWindow::put

//--------------------------------------------------------------------
// Change the attributes of characters in the window:
//
// Input:
//   x,y:    The position in the window to start changing attributes
//   color:  The attribute to set
//   count:  The number of characters to change

void ConWindow::putAttribs(short x, short y, Style color, short count)
{
  mvwchgat(win, y, x, count, attribStyle[color], colorStyle[color], NULL);
  touchwin(win);
} // end ConWindow::putAttribs

//--------------------------------------------------------------------
// Write a character using the current attributes:
//
// Input:
//   x,y:    The position in the window to start writing
//   c:      The character to write
//   count:  The number of characters to write

void ConWindow::putChar(short x, short y, char c, short count)
{
  wmove(win, y, x);

  while (count--) {
    waddch(win, c);
  }
} // end ConWindow::putAttribs

//--------------------------------------------------------------------
// Read the next key down event:
//
// Output:
//   event:  Contains a key down event

int ConWindow::readKey()
{
  update_panels();
  doupdate();

  return wgetch(win);
} // end ConWindow::readKey

//--------------------------------------------------------------------
void ConWindow::setAttribs(Style color)
{
  wattrset(win, attribStyle[color]);
} // end ConWindow::setAttribs

//--------------------------------------------------------------------
// Position the cursor in the window:
//
// There is only one cursor, and each window does not maintain its own
// cursor position.
//
// Input:
//   x,y:    The position in the window for the cursor

void ConWindow::setCursor(short x, short y)
{
//  ASSERT((x>=0)&&(x<size.X)&&(y>=0)&&(y<size.Y));

  wmove(win, y, x);
} // end ConWindow::setCursor
