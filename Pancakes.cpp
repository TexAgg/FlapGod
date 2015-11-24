/*
*Pancakes.cpp
*/

#include "Pancakes.h"

using namespace Graph_lib;

	Pancake::Pancake(Point pt, int ww, int hh):
	Graph_lib::Ellipse(pt,ww,hh)
	{
		set_fill_color(165);
	}

	void Pancake::set_position(int n)
	{
		position = n;
	}
	
	void Pancake::set_rank(int n)
	{
		size_rank = n;
	}
	
	Textangle::Textangle(Point pt, int w, int h, const String& s):
	rec(pt, w, h),
	tech(Point(pt.x+7,pt.y+h-10),s)
	{
		//tech = new Graph_lib::Text(pt, s);
		rec.set_fill_color(Color::white);
	}
	
	void Textangle::draw_lines() const
	{
		rec.draw_lines();
		
		//tech->draw_lines();
		tech.draw_lines();
	}
	
	/*
	//Nothing attached shows up when the window is actually made for some reason
	Error_window::Error_window(Point pt, int w, int h, const String& s):
	Window(pt,w,h,s),
	ob(Point(pt.x+10,pt.y+10),100,70,"Invalid!"),
	bye(Point(pt.x+30,pt.y+30),80,30,"OK",error_cb)
	{
		attach(ob);
		ob.put("Invalid name: Please enter 2-3 alpha characters");
		//cout << "Invalid name: Please enter 2-3 alpha characters" << endl;
		
		attach(bye);
		
		cout << "Before error redraw" << endl;
		redraw();
		cout << "After error redraw" << endl;
	}
	
	void Error_window::error_cb(Address, Address data)
	{
		Error_window& spc = *static_cast<Error_window*>(data);
        spc.error_action();
	}
	
	void Error_window::error_action()
	{
		hide();
	}
	*/
	
	Score::Score(int n, string s):
	score(n),
	name(s)
	{
		
	}
	
	bool operator<(const Score& sc1, const Score& sc2)
	{
		return sc1.score < sc2.score;
	}
	
	bool operator==(const Score& sc1, const Score& sc2)
	{
		return (sc1.score==sc2.score && sc1.name==sc2.name);
	}
	
	ostream& operator<<(ostream& os, const Score& sc)
	{
		return os << sc.score << " " << sc.name;// << endl;
	}
	
	
	istream& operator>>(istream& is, Score& sc)
	{
		int a;
		string b;
		is >> a >> b;
		
		return is;
	}
	
	//To compare pointers to Scores
	bool score_compare(Score* a, Score* b)
	{
		return (*a < *b);
	}
