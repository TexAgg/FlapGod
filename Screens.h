/*
*Screens.h
*/
 
#include "std_lib_facilities_4.h"
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "Simple_window.h"
#include "Window.h"

#include <sstream>

#include "Pancakes.h"
#include "find_solution.h"
 
using namespace Graph_lib;
 
struct Game_screen : Graph_lib::Window
{
    Game_screen(Point, int, int, const string&); //Constructor
	~Game_screen();
     
	//Attach and detach the splash screen 
    void attach_splash();
    void detach_splash();
	
	int get_difficulty() const {return difficulty;}
     
private:
     
	Graph_lib::Text choose_diff; //(Point(300,300),"Choose a difficulty!"); 
	 
    Vector_ref<Shape> splash_shapes; 		 //All of the shapes in the splash screen
    Vector_ref<Widget> widges;  	 		 //All of the widges in the splash screen	
	Vector<Pancake*> pcakes;				 //(Pointers to) the pancakes
	vector<int> positions;						
	Vector<Point*> pons; 					 //(Pointers to) all of the centers of the pancakes
	Vector<Graph_lib::Button*> flip_buttons; //The buttons used to flip the pancakes
	vector<int>* solutions = nullptr;
     
    Text txt; //The game name 
    Text names1, names2, names3; //Our names
	Text group_num;
     
    Graph_lib::Menu main_menu;				 //The splash screen's main menu
	Graph_lib::Button r2s; 					//Return to Splash Screen
	Graph_lib::Image rules;		
	Graph_lib::Button ready;				//For when the player is ready to start the game
	Graph_lib::Menu diff;					//Select the difficulty
	Graph_lib::In_box initials; 
	//Graph_lib::Menu flip_buttons;
	//Graph_lib::Text choose_diff;
	
	//These are so I don't try to detach something which isn't attached
	bool diff_attached = false;
	bool ready_attached = false;
	bool pancakes_attached = false;
	bool initials_attached = false;
	bool confirm_attached = false;
	bool choose_attached = false;
	bool obox_attached = false;
	
	int difficulty; //The difficulty/number of pancakes
	int turn = 0;
	int score = 0;
	string player_name="PLAYER";
	bool is_valid_name = false;	
	Graph_lib::Button confirm_name;
	Graph_lib::Out_box obox;
	
	void pancake_maker();					//Make the pancakes
	void remove_pancakes();					//Remove the pancakes from the screen
	
    //Actions
    void newgame_pressed();
    void rules_pressed();
    void scores_pressed();
    void exitgame_pressed();
	void r2s_pressed();
	void ready_pressed();
	
	////Actions associated with difficulty buttons
	void diff2();
	void diff3();
	void diff4();
	void diff5();
	void diff6();
	void diff7();
	void diff8();
	void diff9();
	
	//Actions associated with flip buttons
	void pc1();
	void pc2();
	void pc3();
	void pc4();
	void pc5();
	void pc6();
	void pc7();
	void pc8();
	void pc9();
	
	int pstop = 0; //The pancake selected
     
    //Callbacks
    static void newgame_callback(Address, Address data); 	//Start a new game
    static void rules_callback(Address, Address data);  	//Show the rules
    static void scores_callback(Address, Address data); 	//Display the high scores
    static void exitgame_callback(Address, Address data);	//Exit the game
	static void r2s_callback(Address, Address data);		//Return to the screen
	static void ready_callback(Address, Address data);		//Ready to start the game
	
	//Callbacks associated with difficulty buttons
	static void diff2_callback(Address, Address data);
	static void diff3_callback(Address, Address data);
	static void diff4_callback(Address, Address data);
	static void diff5_callback(Address, Address data);
	static void diff6_callback(Address, Address data);
	static void diff7_callback(Address, Address data);
	static void diff8_callback(Address, Address data);
	static void diff9_callback(Address, Address data);
	
	//Callbacks associated with flip buttons
	static void pc1_cb(Address, Address data);
	static void pc2_cb(Address, Address data);
	static void pc3_cb(Address, Address data);
	static void pc4_cb(Address, Address data);
	static void pc5_cb(Address, Address data);
	static void pc6_cb(Address, Address data);
	static void pc7_cb(Address, Address data);
	static void pc8_cb(Address, Address data);
	static void pc9_cb(Address, Address data);
	
	static void confirm_name_cb(Address, Address data);
	void confirm_name_action();
	
	Vector<Callback> pc_cb; //For the flip callbacks
    
	void flip_time();	//Flip the pancakes
	
	bool pancakes_ordered = false;   //Are the pancakes in order?
	vector<int> ordered_ints;		//Just the ints 1-difficulty, to compare the positions to
	void check_pancakes(); 			//Checks if the pancakes are flipped, and if they are, returns to the main menu
	
	void print_positions(); //For bug checking
	
	Graph_lib::Out_box* high_scores = nullptr; //high_scores(Point(300,200),250,350,"High scores!")
	Graph_lib::Text* showing_scores = nullptr; //showing_scores(Point(300,150),"These are the high scores!")
	bool show_scores_attached = false;
	
	//Input and output
	ofstream output;
	ifstream input;
	//stringstream sstream;
	
	Vector<Score*> scores; //Holds scores
};

