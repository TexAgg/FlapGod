/*
*Screens.cpp
*/

#include "Screens.h"
 
using namespace Graph_lib;

/*
*All these initializers are unsightly
*There may be so many that it causes an error when I add more
*i.e.: 'glibc detected'
*/
    Game_screen::Game_screen(Point pt, int width, int height, const string& win_name):
    Window(pt,width,height,win_name),
    txt(Point(300,300),"Flap God"),
	group_num(Point(15,15),"Group 32"),
    names1(Point(15,30),"Matt Gaikema"),
    names2(Point(15,45),"Jared Cambell"),
    names3(Point(15,60),"Adam Espinoza"),
    main_menu(Point(310,325),80,30,Menu::vertical,"Menu"),
    butt(Point(300,400),80,30,"CLICK",butt_callback),
	r2s(Point(width-80,height-30),80,30,"Back",r2s_callback),
	rules(Point(200,200),"rules.jpg",Suffix::Encoding::jpg),
	ready(Point(200,500),80,30,"Ready!",ready_callback),
	diff(Point(50,500),80,30,Menu::horizontal,"Difficulty"),
	initials(Point(200,110),80,40,"Initials:"),
	obox(Point(325,150),300,45,"Error:"),
	confirm_name(Point(200,150),100,30,"Confirm name",confirm_name_cb)
    {
        //splash_shapes.push_back(bg);
        splash_shapes.push_back(txt);
        splash_shapes.push_back(names1);
        splash_shapes.push_back(names2);
        splash_shapes.push_back(names3);
		splash_shapes.push_back(group_num);
		splash_shapes.push_back(new Textangle(Point(310,325),80,30,"New game"));
		splash_shapes.push_back(new Textangle(Point(310,355),80,30,"Rules"));
		splash_shapes.push_back(new Textangle(Point(310,385),80,30,"Scores"));
		splash_shapes.push_back(new Textangle(Point(310,415),80,30,"Exit"));
         
        widges.push_back(main_menu);
        //widges.push_back(butt);
     
        txt.set_font_size(36);
         
        //main_menu.attach(butt);
        main_menu.attach(new Button{pt,400,400,"New Game",newgame_callback});
        main_menu.attach(new Button{pt,400,400,"Rules",rules_callback});
        main_menu.attach(new Button{pt,0,0,"Scores",scores_callback});
        main_menu.attach(new Button{pt,0,0,"Exit",exitgame_callback});
        main_menu.attach(*this);
		
		diff.attach(new Button{pt,0,0,"2",diff2_callback});
		diff.attach(new Button{pt,0,0,"3",diff3_callback});
		diff.attach(new Button{pt,0,0,"4",diff4_callback});
		diff.attach(new Button{pt,0,0,"5",diff5_callback});
		diff.attach(new Button{pt,0,0,"6",diff6_callback});
		diff.attach(new Button{pt,0,0,"7",diff7_callback});
		diff.attach(new Button{pt,0,0,"8",diff8_callback});
		diff.attach(new Button{pt,0,0,"9",diff9_callback});
		
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
     
	void Game_screen::remove_pancakes()
	{
		for(int i = 0; i<pcakes.size();i++)
			detach(*pcakes[i]);
		
		for(int i = 0; i < flip_buttons.size();i++)
		{
			detach(*flip_buttons[i]);
		}
		
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
			cout << "Congrats! " << turn << " turns! " << endl;
			
			pancakes_ordered = true;
			
			Graph_lib::Text gg(Point(300,300),"Congrats!");
			gg.set_font_size(24);
			attach(gg);
			
			redraw();
			Fl::flush();
			Fl::redraw();
			
			detach(gg);
			
			system("sleep 2");
			
			r2s_pressed();//Back to the main menu
			
			ordered_ints.clear();
			
			output.open("scores.txt",ios::app);
			output << score << " " << player_name << endl;
			cout << score << " " << player_name << endl;
			
			//Is this neccesary?
			output.flush();
			output.close();
			
			//scores.push_back(new Score(score,player_name));
		}
		
		if(score < 0)
		{
			r2s_pressed();
			
			cout << "You lose!" << endl;
		}
	}
	 
    void Game_screen::butt_callback(Address, Address data)
    {
        Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.butt_pressed();
    }
     
    void Game_screen::butt_pressed()
    {
        cout << "Hi" << endl;
         
        attach_splash();
    }
     
    void Game_screen::newgame_callback(Address w, Address data)
    {
        //Remove widgets
		Fl_Widget* pw = static_cast<Fl_Widget*>(w);
        auto allButtons = pw->parent()->array();
        int size = pw->parent()->children();
        for (int i = 0; i < size; ++i)
            allButtons[i]->hide();
        pw->parent()->redraw();
		
        Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.newgame_pressed();
    }
     
    void Game_screen::newgame_pressed()
    {
        //Start a new game
        cout << "Time for a new game!" << endl;
         
        detach_splash();
		
		attach(initials);
		attach(r2s);
		attach(rules);

		initials_attached = true;
		
		attach(confirm_name);
		confirm_attached = true;
    }
     
    void Game_screen::rules_callback(Address w, Address data)
    {
        //Remove widgets
		Fl_Widget* pw = static_cast<Fl_Widget*>(w);
        auto allButtons = pw->parent()->array();
        int size = pw->parent()->children();
        for (int i = 0; i < size; ++i)
            allButtons[i]->hide();
        pw->parent()->redraw();
		
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.rules_pressed();
    }
     
    void Game_screen::rules_pressed()
    {
        //Explain the rules
        cout << "These are the rules" << endl;
         
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
        //Exit the game
        cout << "Bye!" << endl;
        hide();
    }
     
    void Game_screen::scores_callback(Address, Address data)
    {
        Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.scores_pressed();
    }
     
	//Fix this: Prints every score twice
	//Weird stuff happens whenever you start with an empty file
    void Game_screen::scores_pressed()
    {
        //Display the high scores
        cout << "These are the scores" << endl;
		
		int a;
		string b;
		
		input.open("scores.txt");
		
		while(input)
		{	
			input>>a>>b;
			
			/*
			if(a==0 && b.empty())
				continue;
			*/
			
			//cout << a << " " << b << endl;
			
			cout << "Pusing back" << endl;
			scores.push_back(new Score(a,b));
		}
		sort(scores.begin(), scores.end(),score_compare);
		reverse(scores.begin(),scores.end());				//sort sorts into ascending order. Reverse to get highest to lowest
		
		//cout<<scores.size()<<endl;
		
		input.close();
		
		output.open("scores.txt",ios::trunc);
		
		if(scores.size()!=0)
		{
		for (int i = 0; i<scores.size() && i <5; i++)
		{
			//if(!(*scores[i]==Score(0,"")))
			output << *scores[i] << endl;
			
			cout << i+1 << ": "<< *scores[i] << endl;
		}
		output.close();
		}
		
		scores.clear();
    }
	
	void Game_screen::r2s_callback(Address, Address data)
	{
        Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.r2s_pressed();
	}
	
	/*
	*Maybe let objects detach themselves when they go out of scope instead of 
	*dealing with this many messy booleans.
	*But that causes a segmentation fault
	*/
	void Game_screen::r2s_pressed()
	{
		cout<<"Returning to main menu\n" << endl;
		attach_splash();
		r2s.hide();
		detach(rules);
		if (diff_attached)
		{
			//detach(choose_diff);
			diff.hide();
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
			//attach(ready);
			//ready_attached=true;
			
			if(obox_attached)
			{
				detach(obox);
				obox_attached = false;
			}
			
			detach(confirm_name);
			confirm_attached = false;
			
			ready_pressed();
		}
		
		/*
		*Tell the user that the name they have entered is invalid
		*Tell them valid options
		*Possibly use an error window?
		*/
		else
		{
			//Error_window err(Point(300,300),300,300,"ERROR!");
			//err.redraw();
			
			if(!obox_attached)
			{
				attach(obox);
				obox.put("Enter a valid name! (2-3 alpha characters)");
				obox_attached = true;
			}	
			
			/*
			Graph_lib::Text badname(Point(300,130),"Enter a valid name! (2-3 alpha characters)");
			attach(badname);
			
			
			//When invalid name entered, attach Text 
			//Remove text when a valid name is entered
			
			
			redraw();
			Fl::flush();
			Fl::redraw();
			system("sleep 2");
			
			detach(badname);
			*/
		}
		
		cout << "Your name is " << player_name << endl;
	}
	
	void Game_screen::ready_callback(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.ready_pressed();
	}
	
	//Move from the rules to the difficulty selection
	void Game_screen::ready_pressed()
	{
		cout << "OK! Let's begin" << endl;
		
		//detach(obox);
		detach(rules);
		detach(initials);
		initials_attached = false;
		
		if(ready_attached)
		{
			detach(ready);
			ready_attached = false;
		}
		
		//attach(choose_diff);
		
		/*
		attach(obox);
		obox_attached = true;
		obox.put("Choose a difficulty");
		*/
		
		attach(diff);
		diff_attached = true;
		
		cout << "Hello, " << player_name << endl;
	}
	
	void Game_screen::diff2_callback(Address, Address data)
	{
		Game_screen& spc = *static_cast<Game_screen*>(data);
        spc.diff2();
	}
	
	void Game_screen::diff2()
	{
		cout << "Difficulty 2" << endl;
		
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
		cout << "Difficulty 3" << endl;
		
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
		cout << "Difficulty 4" << endl;
		
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
		cout << "Difficulty 5" << endl;
		
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
		cout << "Difficulty 6" << endl;
		
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
		cout << "Difficulty 7" << endl;
		
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
		cout << "Difficulty 8" << endl;
		
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
		cout << "Difficulty 9" << endl;
		
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
		cout << "First pancake" << endl;
		
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
		cout << "Second pancake" << endl;
		
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
		cout << "Third pancake" << endl;

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
		cout << "Fourth pancake" << endl;	

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
		cout << "Fifth pancake" << endl;

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
		cout << "Sixth pancake" << endl;	

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
		cout << "Seventh pancake" << endl;

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
		cout << "Eight pancake" << endl;	

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
		cout << "Ninth pancake" << endl;		
		
		pstop=9;
		flip_time();	
		
		check_pancakes();
	}													
     
    void Game_screen::attach_splash()
    {
        for(int i = 0; i < widges.size(); i++)
            attach(widges[i]);
         
        for(int i = 0; i < splash_shapes.size(); i++)
            attach(splash_shapes[i]);
         
        redraw();
    }
     
    void Game_screen::detach_splash()
    {
        //main_menu.hide();
        /*cout << widges.size();
        for(int i = 0; i < widges.size(); i++)
        {
            //detach(widges[i]);
            widges[i].hide();
        }*/
         
        for(int i = 0; i < splash_shapes.size(); i++)
            detach(splash_shapes[i]);
         
        redraw();
    }
	
	void Game_screen::pancake_maker()
	{
		turn = 0; //Reset the game
		
		//Make the points in order to place the buttons
		for(int i = 0; i < difficulty; i++)
		{
			pons.push_back(new Point(400,25+55*i));
		}
		for(int i = 0; i < difficulty;i++)
		{
			flip_buttons.push_back(new Button(Point(pons[i]->x+300,pons[i]->y),80,25,to_string(i),pc_cb[i]));
		}
		
		//Delete all the points and then make them in a random order
		pons.clear();
		
		for (int i = 0; i < difficulty; i++)
		{
			positions.push_back(i);
			ordered_ints.push_back(i);
			
			//pons.push_back(new Point(400,25+55*positions[i]));
		}
	
		random_shuffle(positions.begin(),positions.end());
		//Make sure the pancakes don't start out in order
		while(positions==ordered_ints)
		{
			random_shuffle(positions.begin(),positions.end());
			
			cout << "Shuffling pancakes" << endl;
		}
		
		pancakes_ordered=false;
		
		for(int i = 0; i<positions.size();i++)
			positions[i]++;
		
		solutions=find_solution(positions);
		
		for(int i = 0; i<positions.size();i++)
			positions[i]--;
		
		cout <<"Can be done in " << solutions->size() << " turns" << endl;
		
		for (int i = 0; i<positions.size(); i++)
		{
			//pons.push_back(new Point(400,25+55*positions[i]));
			pons.push_back(new Point(400,25+55*i));
		}
		
		//reverse(pons.begin(), pons.end());
		
		//Make the pancakes
		for (int i = 0; i < difficulty; i++)
		{
			//pcakes.push_back(new Pancake(*pons[i],75+25*i,25));
			pcakes.push_back(new Pancake(*pons[i],75+25*positions[i],25));
		}
		
		for(int i = 0; i < pcakes.size();i++)
		{
			pcakes[i]->set_position(positions[i]);
			
			//Rank smallest (0) to bigest
			pcakes[i]->set_rank(i);
		}
		
		//Detach other stuff
		if(diff_attached)
		{
			diff.hide();
			diff_attached=false;
		}
		/*
		if(obox_attached)
		{
			detach(obox);
			obox_attached = false;
		}
		*/
		
		for(int i = 0; i < pcakes.size();i++)
		{
			pcakes[i]->set_fill_color(5*positions[i]);
			attach(*pcakes[i]);
		}
		
		for(int i = 0; i < flip_buttons.size(); i++)
		{
			attach(*flip_buttons[i]);
		}
		
		pancakes_attached=true;
		redraw();
		
		/*
		//Where are the pancakes
		for(int i = 0; i<difficulty; i++)
		{
			cout << "Pancake " << i <<": (" << pcakes[i]->center().x << "," << pcakes[i]->center().y << ") has rank " << pcakes[i]->get_rank();
			cout << " and position " << pcakes[i]->get_position() << endl;
		}	
		cout<<"\n";
		*/
	}

	void Game_screen::flip_time()
	{	
		turn++;
		cout << "Turn " << turn << endl;
		
		/*
		cout << "Before reverse:" << endl;
		for(int i = 0; i < positions.size();i++)
			cout << positions[i] <<",";
		cout<<"\n";	
		*/
		
		//Switch the positions of the pancakes in the vector and then use that to move them on screen
		reverse(positions.begin(), positions.begin()+pstop );
		
		/*
		cout << "After reverse:" << endl;
		for(int i = 0; i < positions.size();i++)
			cout << positions[i] <<",";
		cout<<"\n"
		*/;	
		
		for(int i = 0; i<difficulty;i++)
		{
			detach(*pcakes[i]);
		}
		pcakes.clear();
		pons.clear();
		for(int i = 0; i < difficulty; i++)
		{
			//pons.push_back(new Point(400,25+55*positions[i]));
			pons.push_back(new Point(400,25+55*i));
		}
		for (int i = 0; i < difficulty; i++)
		{
			//pcakes.push_back(new Pancake(*pons[i],75+25*i,25));
			pcakes.push_back(new Pancake(*pons[i],75+25*positions[i],25));
		}
		for(int i = 0; i < pcakes.size();i++)
		{
			//cout << "Moving pancake " << i << endl; 
			
			pcakes[i]->set_fill_color(5*positions[i]);
			
			attach(*pcakes[i]);
		}
		
		for(int i = 0; i < difficulty; i++)
		{
			pcakes[i]->set_position(positions[i]);
			
			pcakes[i]->set_rank(i);
		}
		
		//Input the solutions vector into the find_solution function
		
		redraw();
		
		/*
		//Where are the pancakes
		for(int i = 0; i<difficulty; i++)
		{
			cout << "Pancake " << i <<": (" << pcakes[i]->center().x << "," << pcakes[i]->center().y << ") has rank " << pcakes[i]->get_rank();
			cout << " and position " << pcakes[i]->get_position() << endl;
		}	
		cout<<"\n";
		*/
		
		score = (100 - 10 * (turn - solutions->size())) * difficulty;
		
		cout << "The score is " << score << endl;
	}

