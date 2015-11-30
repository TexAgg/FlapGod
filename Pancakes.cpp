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
		rec.set_fill_color(Color::white);
	}
	
	void Textangle::draw_lines() const
	{
		rec.draw_lines();
		
		tech.draw_lines();
	}
	
	Score::Score(int n, string s):
	score(n),
	name(s)
	{
		
	}
	
	string Score::to_string()
	{
		int b = score;
		string str = std::to_string(b);
		str.append(" ");
		str.append(name);
		return str;
	}
	
	bool operator<(const Score& sc1, const Score& sc2)
	{
		return sc1.score < sc2.score;
	}
	
	bool operator>(const Score& sc1, const Score& sc2)
	{
		return sc1.score > sc2.score;
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
		return (*a > *b);
	}
