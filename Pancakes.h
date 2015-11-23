/*
*Pancakes.h
*/

#include "std_lib_facilities_4.h"
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Simple_window.h"
#include "Window.h"

using namespace Graph_lib;

struct Pancake : Graph_lib::Ellipse
{
	Pancake(Point, int, int); //A center, width, and height
	
	void set_position(int);
	int get_position() const {return position;}
	
	void set_rank(int);
	int get_rank() const {return size_rank;}
	
private:

	//int h = 75;

	int position = 0; //Position on screen (0 being the top)
					 //center.y=25+55*position
	
	int size_rank = 0; //Rank by size from 0 to largest
};

//To cover up Buttons
struct Textangle : Graph_lib::Shape
{
	Textangle(Point, int, int, const String&);
	
	void draw_lines() const;
	
private:
	
	Graph_lib::Rectangle rec;
	//Graph_lib::Text* tech;
	Graph_lib::Text tech;	
};

/*
struct Error_window : Graph_lib::Window
{
	Error_window(int, int, const String&);
	
private:
		Graph_lib::Outbox ob;
		Graph_lib::Button bye;
};
*/

//Use this for reading/writing names and associated scores
struct Score
{ 
	Score(int, string);
	
	int score;
	string name;	
};

bool score_compare(Score*, Score*);

bool operator<(const Score&, const Score&);

//For inputting and outputting scores
istream& operator>>(istream&, Score&);
ostream& operator<<(ostream&, const Score&);


