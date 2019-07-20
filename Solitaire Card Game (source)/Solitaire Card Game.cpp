// Solitaire Card Game.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Reference:
#include "Stack.h"
#include "Spider.h"
#include <string>
#include <iostream>
#include "Tests.h"

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
	spider_test_find_seq();
	std::cout << "Type \"HELP\" to read game commands." << std::endl;
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
		//	std::cout << "HI";
			s = spider_init_random(level, seed);
		//	std::cout << "HI";
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
				std::cout << "You have not won yet, keep playing or input \"QUIT\" to quit." << std::endl;
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
		else if (cmd == "HELP") {
			std::cout << "Game Commands:" << std::endl << std::endl;
			std::cout << "1. INIT: + seed(int) + level(int): Choose random seed and choose level." << std::endl;
			std::cout << "	Level 1: Single suit" << std::endl;
			std::cout << "	Level 2: Double suits" << std::endl;
			std::cout << "	Level 3: Full suits" << std::endl;
			std::cout << "2. WON: Tells if you have won or not." << std::endl;
			std::cout << "3. PRINT: Print current game." << std::endl;
			std::cout << "4. GETSTOCK: Distribute  10 cards from stock." << std::endl;
			std::cout << "5. MOVE: + source tableau(int) + suit(char) + number (i) + destination tableau(int):" << std::endl;
			std::cout << "	Move a sequence of cards starting from chosen card, from source tableau to destination tableau." << std::endl;
			std::cout << "6. QUIT: Quit the game. The game will not be saved." << std::endl;
			std::cout << "7. HELP: Open game commands helper log." << std::endl;
		}
		else {
			std::cout << "Invalid Command = ";
			std::cout << cmd << std::endl;
			std::cout << "Enter \"QUIT\" to quit the game." << std::endl;
		}
	}
}