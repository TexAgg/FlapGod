/*
*flap_god.cpp
*/

#include "std_lib_facilities_4.h"
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Simple_window.h"
#include "Window.h"

#include "Screens.h"

/*
*TO DO:
*1. Fix scores.txt so it only shows each score once
*2. Make pretty.
*3. Extra credit options (maybe)
*4.Debug/test
*5. Report. Make sure nothing in the project description was missed
*6 Buy a fucking C.D. 
*/

//http://www.cs.fsu.edu/~jestes/howto/g++compiling.txt

//Splash screen

//Explain rules

//Ask for initials
//Display scores (from a file)

//Ask for difficulty level
//Display pancakes

//Flip shit

//If in order, display score
//Update, sort scores file
//Play again?

int main()
{
  try
  {
	Game_screen spl(Point (100,100),800,600,"Flap God");
    
    return gui_main();
  }
  catch(exception& e)
  {
  	cerr << "error: " << e.what() << endl;
  }
  catch(...)
  {
  	cerr << "unknown error." << endl;
  }
}
