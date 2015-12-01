#Makefile for Flap God

all: Main

Main: Graph.o GUI.o Window.o Simple_window.o Screens.o flipflaps.o Pancakes.o
	g++ -std=c++14 -g Graph.o GUI.o Window.o Simple_window.o Screens.o find_solution.o flipflaps.o Pancakes.o -o a.out -lfltk -lfltk_images
Graph.o: Graph.cpp
	g++ -std=c++14 -g -c Graph.cpp -o Graph.o -lfltk -lfltk_images
GUI.o: GUI.cpp
	g++ -std=c++14 -g -c GUI.cpp -o GUI.o -lfltk -lfltk_images
Window.o: Window.cpp
	g++ -std=c++14 -g -c Window.cpp -o Window.o -lfltk -lfltk_images
Simple_window.o: Simple_window.cpp
	g++ -std=c++14 -g -c Simple_window.cpp -o Simple_window.o -lfltk -lfltk_images
Screens.o: Screens.cpp
	g++ -std=c++14 -g -c Screens.cpp -o Screens.o -lfltk -lfltk_images
flipflaps.o: flap_god.cpp
	g++ -std=c++14 -g -c flap_god.cpp -o flipflaps.o -lfltk -lfltk_images
Pancakes.o: Pancakes.cpp
	g++ -std=c++14 -g -c Pancakes.cpp -o Pancakes.o -lfltk -lfltk_images
	
clean:
	rm Graph.o GUI.o Window.o Simple_window.o Screens.o flipflaps.o Pancakes.o a.out

run:
	./a.out
