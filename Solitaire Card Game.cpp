// Solitaire Card Game.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Reference:
#include "Stack.h"
#include "Spider.h"
#include <string>
#include <iostream>

// check_initialized (initialized) checks the flag and returns an error
// message if the game is not initialized
void check_initialized(int initialized) {
	if (!initialized) {
		std::cout<< "You must initialize the game first."<<std::endl;
		std::cout<< "Stopping Program" << std::endl;
		exit(1);
	}
}

int main() {
	// Run test of stack.cpp module
	stack_test();

	struct spider* s = NULL;

	int initialized = 0;

	while (1) {
		std::string cmd;
		std::cin >> cmd;
		
		if (cmd == "INIT") {
			int seed = 0;
			int level = 0;
			// Input 2 more int
			std::cin >> seed;
			std::cin >> level;
			spider_init_random(level, seed);
			spider_print(s);
			initialized += 1;
		}
		else if (cmd == "WON") {
			check_initialized(initialized);
			bool won = spider_has_won(s);
			if (won) {
				std::cout << "Congrats! You have won the game! Dude you rock!" << std::endl;
				break;
			}
			else {
				std::cout << "You have not won yet, keep playing or input \"quit\" to quit." << std::endl;
			}
		}
		else if (cmd == "PRINT") {
			check_initialized(initialized);
			spider_print(s);
		}
		/* In case we're writing this helper
		else if (cmd == "PRINTFACEUP") {
			check_initialized(initialized);
			spider_print_faceup(s);
		}
		*/
		else if (cmd == "GETSTOCK"){
			check_initialized(initialized);
			spider_get_stock(s);
			spider_print(s);
		}
		else if (cmd == "TESTFINDSEQ") {
			check_initialized(initialized);
			spider_test_find_seq();
		}
		else if (cmd == "MOVE") {
			check_initialized(initialized);
			int src = 0;
			std::cin >> src;
			// reads 2 inputs for card
			card c;
			std::cin >> c.suit;
			std::cin >> c.num;

			int dest = 0;
			std::cin >> dest;
			//move
			spider_move(s, src, c, dest);
			//print
			spider_print(s);
		}
		else if (cmd == "QUIT"){
			break;
		}
		else {
			std::cout << "Invalid Command = ";
			std::cout << cmd << std::endl;
			std::cout << "Stopping Program" << std::endl;
			exit(1);
		}
	}
}
