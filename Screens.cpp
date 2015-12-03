/*
*Screens.cpp
*/

#include "Screens.h"
 
using namespace Graph_lib;

    Game_screen::Game_screen(Point pt, int width, int height, const string& win_name):
    Window(pt,width,height,win_name),
    txt(Point(300,300),"Flap God"),
	group_num(Point(15,15),"Group 32"),
    names1(Point(15,30),"Matt Gaikema"),
    names2(Point(15,45),"Jared Cambell"),
    names3(Point(15,60),"Adam Espinoza"),
	r2s(Point(width-80,height-30),80,30,"Back",r2s_callback),
	rules(Point(200,200),"rules.jpg",Suffix::Encoding::jpg),
	ready(Point(200,500),80,30,"Ready!",ready_callback),
	initials(Point(200,110),80,40,"Initials:"),
	obox(Point(325,150),300,45,"Error:"),
	confirm_name(Point(200,150),100,30,"Confirm name",confirm_name_cb),
	choose_diff(Point(300,300),"Choose a difficuty!"),
	title_screen(Point(0,0),"FlapGod.jpg",Suffix::Encoding::jpg)
    {
		splash_shapes.push_back(title_screen);
		
		texties.push_back(new Textangle(Point(310,325),80,30,"New game"));
		texties.push_back(new Textangle(Point(310,355),80,30,"Rules"));
		texties.push_back(new Textangle(Point(310,385),80,30,"Scores"));
		texties.push_back(new Textangle(Point(310,415),80,30,"Exit"));
     
        txt.set_font_size(36);
         
        main_menu_vec.push_back(new Button{Point(310,325),80,30,"New Game",newgame_callback});
        main_menu_vec.push_back(new Button{Point(310,355),80,30,"Rules",rules_callback});
        main_menu_vec.push_back(new Button{Point(310,385),80,30,"Scores",scores_callback});
        main_menu_vec.push_back(new Button{Point(310,415),80,30,"Exit",exitgame_callback});
		
		diff_vec.push_back(new Button{Point(50,500),80,30,"2",diff2_callback});
		diff_vec.push_back(new Button{Point(130,500),80,30,"3",diff3_callback});
		diff_vec.push_back(new Button{Point(210,500),80,30,"4",diff4_callback});
		diff_vec.push_back(new Button{Point(290,500),80,30,"5",diff5_callback});
		diff_vec.push_back(new Button{Point(370,500),80,30,"6",diff6_callback});
		diff_vec.push_back(new Button{Point(450,500),80,30,"7",diff7_callback});
		diff_vec.push_back(new Button{Point(530,500),80,30,"8",diff8_callback});
		diff_vec.push_back(new Button{Point(610,500),80,30,"9",diff9_callback});
		
		pc_cb.push_back(pc1_cb);
		pc_cb.push_back(pc2_cb);
		pc_cb.push_back(pc3_cb);
		pc_cb.push_back(pc4_cb);
		pc_cb.push_back(pc5_cb);
		pc_cb.push_back(pc6_cb);
		pc_cb.push_back(pc7_cb);
		pc_cb.push_back(pc8_cb);
		pc_cb.push_back(pc9_cb);
     
        attach_splash();
    }
	
	//destructor
	Game_screen::~Game_screen()
	{	
		//Delete all pointers used
		for(auto k : diff_vec)
			delete k;
		for(auto k : texties)
			delete k;
		for (auto k : main_menu_vec)
			delete k;
		for(auto k : pcakes)
			delete k;
		for(auto k : pons)
			delete k;
		for(auto k : scores)
			delete k;
		for(auto k : flip_buttons)
			delete k;
		for(auto k : scores_text)
			delete k;
		delete solutions;
		delete showing_scores;
		delete so_far;
	}
    
    void Game_screen::print_positions()
    {
    	for (int k = 0; k < difficulty; k++)
    		cout << positions[k] << endl;
    }
     
	void Game_screen::remove_pancakes()
	{
		for(int i = 0; i<pcakes.size();i++)
			detach(*pcakes[i]);
		
		for(int i = 0; i < flip_buttons.size();i++)
			detach(*flip_buttons[i]);
		
		pcakes.clear();
		pons.clear();
		flip_buttons.clear();
		positions.clear();
			
		pancakes_attached=false;		
		redraw();
	} 
	
	void Game_screen::check_pancakes()//Called in each flip button's callback
	{
		if (positions==ordered_ints)
		{
			pancakes_ordered = true;
			
			Score scre(score,player_name);
			Graph_lib::Text scrnme(Point(300,240),scre.to_string());
			Graph_lib::Text gg(Point(300,300),"Congrats!");
			gg.set_font_size(24);
			scrnme.set_font_size(24);
			attach(scrnme);
			attach(gg);
			
			redraw();
			Fl::flush();
			Fl::redraw();
			
			detach(gg);
			detach(scrnme);
			
			system("sleep 2");
			
			r2s_pressed();//Back to the main menu
			
			ordered_ints.clear();
			
			output.open("scores.txt",ios::app);
			output << score << " " << player_name << endl;
			
			output.flush();
			output.close();
		}
		
		//If the player takes too long
		if(score < 0)
		{
			Score scre(0,player_name);
			Graph_lib::Text scrnme(Point(300,240),scre.to_string());
			Graph_lib::Text gg(Point(300,300),"You lose!");
			gg.set_font_size(24);
			scrnme.set_font_size(24);
			attach(scrnme);
			attach(gg);
			
			redraw();
			Fl::flush();
			Fl::redraw();
			
			detach(gg);
			detach(scrnme);

			system("sleep 2");
			
			r2s_pressed();
		}
	}
     
    void Game_screen::newgame_callback(Address, Address data)
    {
        Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.newgame_pressed();
    }
     
    void Game_screen::newgame_pressed()
    {
        //Start a new game
        detach_splash();
		
		attach(initials);
		attach(r2s);
		attach(rules);

		initials_attached = true;
		
		attach(confirm_name);
		confirm_attached = true;
    }
     
    void Game_screen::rules_callback(Address, Address data)
    {
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.rules_pressed();
    }
     
    void Game_screen::rules_pressed()
    {
        //Explain the rules
        detach_splash();
		
		attach(r2s);
		attach(rules);
    }
     
    void Game_screen::exitgame_callback(Address, Address data)
    {
        Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.exitgame_pressed();
    }
     
    void Game_screen::exitgame_pressed()
    {
		detach_splash();
		
		this->hide();
    }
     
    void Game_screen::scores_callback(Address, Address data)
    {
        Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.scores_pressed();
    }
     
    void Game_screen::scores_pressed()
    {
		scores_text.clear();
		
		detach_splash();
		attach(r2s);
		
		showing_scores = new Text(Point(300,150),"These are the high scores!");
		
		attach(*showing_scores);
		show_scores_attached = true;
		
		int a;
		string b;
		
		input.open("scores.txt");
		
		if(!input)//If there is no file
			{
				Text error_text(Point(200,200),"There are no scores! Try playing a game");
				attach(error_text);
				redraw();
				Fl::flush();
				Fl::redraw();
				detach(error_text);
				system("sleep 2");
				
				r2s_pressed();
			}
		
		else
		{
		while(input)
		{	
			input>>a>>b;
			
			scores.push_back(new Score(a,b));
		}
		scores.erase(scores.begin()+scores.size()-1); //Delete last element, since it is somehow duplicated
		
		sort(scores.begin(), scores.end(),score_compare); //sorts in descending order 
		
		for(int k = 0; k<scores.size() && k<5;k++)
		{
			ost << *scores[k];

			scores_text.push_back(new Text(Point(300,250+20*k),ost.str()));
			ost.str("");
		}
		
		for(auto k :scores_text)
			attach(*k);
		
		ost.str("");
		
		input.close();
		
		scores.clear();
	}
    }
	
	void Game_screen::scoresies()
	{
		scores_text.clear();
		
		showing_scores = new Text(Point(500,150),"These are the high scores!");
		
		attach(*showing_scores);
		show_scores_attached = true;
		
		int a;
		string b;
		
		input.open("scores.txt");
		
		if(!input)//If there is no file
			{
				
				Text error_text(Point(500,200),"There are no scores!");
				attach(error_text);
				redraw();
				Fl::flush();
				Fl::redraw();
				detach(error_text);
				detach(*showing_scores);
				system("sleep 2");
			}
		
		else
		{
			while(input)
			{	
				input>>a>>b;
				
				scores.push_back(new Score(a,b));
			}
			scores.erase(scores.begin()+scores.size()-1); //Delete last element, since it is somehow duplicated
			
			sort(scores.begin(), scores.end(),score_compare); //sorts in descending order 
			
			for(int k = 0; k<scores.size() && k<5;k++)
			{
				ost << *scores[k];
	
				scores_text.push_back(new Text(Point(500,250+20*k),ost.str()));
				ost.str("");
			}
			
			for(auto k :scores_text)
				attach(*k);
			
			redraw();
			Fl::flush();
			Fl::redraw();
			system("sleep 2");
			
			for(auto k :scores_text)
				detach(*k);
			
			detach(*showing_scores);
			ost.str("");
			input.close();
			scores.clear();
		}
	}
	
	void Game_screen::r2s_callback(Address, Address data)
	{
        Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.r2s_pressed();
	}
	
	//Detach everything that is attached
	void Game_screen::r2s_pressed()
	{
		attach_splash();
		r2s.hide();
		detach(rules);
		if (diff_attached)
		{	
			for(auto k : diff_vec)
				detach(*k);
			diff_attached = false;
		}
		if (ready_attached)
		{
			ready.hide();
			ready_attached = false;
		}	
		if(pancakes_attached)
		{
			remove_pancakes();
			pancakes_attached=false;
		}
		if(initials_attached)
		{
			initials.hide();
			initials_attached=false;
		}
		if(confirm_attached)
		{
			confirm_name.hide();
			confirm_attached = false;
		}
		if(obox_attached)
		{
			detach(obox);
			obox_attached = false;
		}
		if(choose_attached)
		{
			detach(choose_diff);
			choose_attached = false;
		}
		if(show_scores_attached)
		{
			detach(*showing_scores);
			for(auto k : scores_text)
				detach(*k);
			show_scores_attached = false;
		}
		if(so_far_attached)
		{
			detach(*so_far);
			so_far_attached = false;
		}
	}
	
	void Game_screen::confirm_name_cb(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
		spc.confirm_name_action();
	}
	
	void Game_screen::confirm_name_action()
	{
		player_name = initials.get_string();
		
		is_valid_name = (player_name.length() == 3 && isalpha(player_name.at(0)) && isalpha(player_name.at(1)) && isalpha(player_name.at(2))) || (player_name.length()==2 && isalpha(player_name.at(0)) && isalpha(player_name.at(1)));
		
		if(is_valid_name)
		{
			if(obox_attached)
			{
				detach(obox);
				obox_attached = false;
			}
			
			detach(confirm_name);
			confirm_attached = false;
	
			scoresies();
			
			ready_pressed();
		}
		
		else
		{
			if(!obox_attached)
			{
				attach(obox);
				obox.put("Enter a valid name! (2-3 alpha characters)");
				obox_attached = true;
			}	
		}
	}
	
	void Game_screen::ready_callback(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.ready_pressed();
	}
	
	//Move from the rules to the difficulty selection
	void Game_screen::ready_pressed()
	{
		detach(rules);
		detach(initials);
		initials_attached = false;
		
		if(ready_attached)
		{
			detach(ready);
			ready_attached = false;
		}
	
		attach(choose_diff);
		for(auto k : diff_vec)
			attach(*k);
		choose_attached = true;
		choose_diff.set_font_size(40);
		
		diff_attached = true;
	}
	
	void Game_screen::diff2_callback(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.diff2();
	}
	
	void Game_screen::diff2()
	{
		difficulty = 2;
		
		pancake_maker();
	}
	
	void Game_screen::diff3_callback(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.diff3();
	}
	
	void Game_screen::diff3()
	{
		difficulty = 3;
		
		pancake_maker();
	}
	
	void Game_screen::diff4_callback(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.diff4();
	}
	
	void Game_screen::diff4()
	{
		difficulty = 4;
		
		pancake_maker();
	}
	
	void Game_screen::diff5_callback(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.diff5();
	}
	
	void Game_screen::diff5()
	{
		difficulty = 5;
		
		pancake_maker();
	}
	
	void Game_screen::diff6_callback(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.diff6();
	}
	
	void Game_screen::diff6()
	{
		difficulty = 6;
		
		pancake_maker();
	}
	
	void Game_screen::diff7_callback(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.diff7();
	}
	
	void Game_screen::diff7()
	{
		difficulty = 7;
		
		pancake_maker();
	}

	void Game_screen::diff8_callback(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.diff8();
	}
	
	void Game_screen::diff8()
	{
		difficulty = 8;
		
		pancake_maker();
	}
	
	void Game_screen::diff9_callback(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.diff9();
	}
	
	void Game_screen::diff9()
	{
		difficulty = 9;
		
		pancake_maker();
	}
	
	void Game_screen::pc1_cb(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
	    spc.pc1();
	}
	
	void Game_screen::pc1()
	{
		pstop=1;
		flip_time();
		
		check_pancakes();
	}
		
	void Game_screen::pc2_cb(Address, Address data)
	{	
		Game_screen& spc = *static_cast<Game_screen*>(data);	      
		spc.pc2();
	}
	
	void Game_screen::pc2()
	{
		pstop=2;	
		flip_time();
		
		check_pancakes();
	}
	
	void Game_screen::pc3_cb(Address, Address data)
	{	
		Game_screen& spc = *static_cast<Game_screen*>(data);	      
		spc.pc3();
	}
	
	void Game_screen::pc3()
	{
		pstop=3;
		flip_time();
		
		check_pancakes();		
	}
	
	void Game_screen::pc4_cb(Address, Address data)
	{	
		Game_screen& spc = *static_cast<Game_screen*>(data);	      
		spc.pc4();
	}
	
	void Game_screen::pc4()
	{
		pstop=4;
		flip_time();
		
		check_pancakes();			
	}
	
	void Game_screen::pc5_cb(Address, Address data)
	{	
		Game_screen& spc = *static_cast<Game_screen*>(data);	      
		spc.pc5();
	}
	
	void Game_screen::pc5()
	{
		pstop=5;
		flip_time();	
		
		check_pancakes();		
	}
	
	void Game_screen::pc6_cb(Address, Address data)
	{	
		Game_screen& spc = *static_cast<Game_screen*>(data);	      
		spc.pc6();
	}
	
	void Game_screen::pc6()
	{
		pstop=6;
		flip_time();	
		
		check_pancakes();		
	}
	
	void Game_screen::pc7_cb(Address, Address data)
	{	
		Game_screen& spc = *static_cast<Game_screen*>(data);	      
		spc.pc7();
	}
	
	void Game_screen::pc7()
	{
		pstop=7;
		flip_time();	
		
		check_pancakes();		
	}	
	
	void Game_screen::pc8_cb(Address, Address data)
	{	
		Game_screen& spc = *static_cast<Game_screen*>(data);	      
		spc.pc8();
	}
	
	void Game_screen::pc8()
	{
		pstop=8;
		flip_time();	
		
		check_pancakes();
	}
	
	void Game_screen::pc9_cb(Address, Address data)
	{	
		Game_screen& spc = *static_cast<Game_screen*>(data);	      
		spc.pc9();
	}
	
	void Game_screen::pc9()
	{
		pstop=9;
		flip_time();	
		
		check_pancakes();
	}													
     
    void Game_screen::attach_splash()
    {
		for (auto k : main_menu_vec)
			attach(*k);
         
        for(int i = 0; i < splash_shapes.size(); i++)
            attach(splash_shapes[i]);
		 
		for (auto k : texties)
			attach(*k);
		
        redraw();
    }
     
    void Game_screen::detach_splash()
    {
        for(int i = 0; i < splash_shapes.size(); i++)
        	detach(splash_shapes[i]);

		for ( auto k : main_menu_vec)
			detach(*k);
		
		for (auto k : texties)
			detach(*k);
         
        redraw();
    }
	
	void Game_screen::pancake_maker()
	{
		detach(choose_diff);
		for(auto k : diff_vec)
			detach(*k);
		choose_attached = false;
		
		turn = 0; //Reset the game
		
		//Make the points in order to place the buttons
		for(int i = 0; i < difficulty; i++)
		{
			pons.push_back(new Point(400,25+55*i));
		}
		for(int i = 0; i < difficulty;i++)
			flip_buttons.push_back(new Button(Point(pons[i]->x+300,pons[i]->y),80,25,to_string(i+1),pc_cb[i]));//Make the buttons for flipping
		
		//Delete all the points and then make them in a random order
		pons.clear();
		
		for (int i = 0; i < difficulty; i++)
		{
			positions.push_back(i);
			ordered_ints.push_back(i);
		}
		
		random_shuffle(positions.begin(),positions.end());
	
		//Make sure the pancakes don't start out in order
		while(positions==ordered_ints)
			random_shuffle(positions.begin(),positions.end());
		
		pancakes_ordered=false;
		
		for(int i = 0; i<positions.size();i++)
			positions[i]++;
		
		//Find solution
		solutions=find_solution(positions);
		
		for(int i = 0; i<positions.size();i++)
			positions[i]--;

		for (int i = 0; i<positions.size(); i++)
			pons.push_back(new Point(400,25+55*i));
		
		//Make the pancakes
		for (int i = 0; i < difficulty; i++)
			pcakes.push_back(new Pancake(*pons[i],75+25*positions[i],25));
		
		for(int i = 0; i < pcakes.size();i++)
		{
			pcakes[i]->set_position(positions[i]);
			
			//Rank smallest (0) to bigest
			pcakes[i]->set_rank(i);
		}
		
		//Detach other stuff
		if(diff_attached)
		{
			for(auto k : diff_vec)
				k->hide();
			diff_attached=false;
		}
		
		for(int i = 0; i < pcakes.size();i++)
		{
			pcakes[i]->set_fill_color(5*positions[i]);
			attach(*pcakes[i]);
		}
		
		for(int i = 0; i < flip_buttons.size(); i++)
			attach(*flip_buttons[i]);
		
		pancakes_attached=true;
		redraw();
		
		string how_many_flips = "Can be done in ";
		how_many_flips.append(to_string(solutions->size()));
		how_many_flips.append(" flips");
		Text this_many(Point(75,75),how_many_flips);
		attach(this_many);
		redraw();
		Fl::flush();
		Fl::redraw();
		system("sleep 2");
		detach(this_many);
	}

	void Game_screen::flip_time()
	{	
		turn++;
		
		//Switch the positions of the pancakes in the vector and then use that to move them on screen
		reverse(positions.begin(), positions.begin()+pstop );
		
		for(int i = 0; i < difficulty; i++)
			detach(*pcakes[i]);
		
		pcakes.clear();
		pons.clear();
		for(int i = 0; i < difficulty; i++)
			pons.push_back(new Point(400,25+55*i));
		
		for (int i = 0; i < difficulty; i++)
			pcakes.push_back(new Pancake(*pons[i],75+25*positions[i],25));
		
		for(int i = 0; i < pcakes.size(); i++)
		{
			pcakes[i]->set_fill_color(5*positions[i]);
			attach(*pcakes[i]);
		}
		
		for(int i = 0; i < difficulty; i++)
		{
			pcakes[i]->set_position(positions[i]);
			pcakes[i]->set_rank(i);
		}

		redraw();
		
		if(so_far_attached)
		{
			detach(*so_far);
			so_far_attached = false;
		}
		
		score = (100 - 10 * (turn - solutions->size())) * difficulty;
	
		string counting = "Turn: ";
		counting.append(to_string(turn));
		counting.append(", Score:");
		counting.append(to_string(score));
		
		so_far = new Text(Point(75,300),counting);
		attach(*so_far);
		so_far_attached = true;
	}
