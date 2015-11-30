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

//Splash screen

//Explain rules

//Ask for initials
//Display scores (from a file)

//Ask for difficulty level
//Display pancakes

//Flip

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
