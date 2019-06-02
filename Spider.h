#pragma once
#include "Stack.h"
struct card {
	int num;
	char suit;
};

struct stack {
	struct card* content;
	int len;
	int cap;
};

struct spider {
	struct stack* stock;
	struct stack* tableau_down[10];
	struct stack* tableau_up[10];
	int stock_size;
	int comp_decks;
};

extern const int Spade;
extern const int Heart;
extern const int Club;
extern const int Diamond;


// spider_init_random(s, seed) randomly initializes
// a valid beginning of a spider game by mutating *s
// The seed is for the random number generator. 
// Given a seed, the initialized game is deterministic.
// effects: modifies *s
struct spider* spider_init_random(int level, int seed);


// spider_has_won(s) returns true if the player has won the game
// i.e. the foundation piles contain 8 complete decks of 13 cards
// and returns false otherwise.
bool spider_has_won(const struct spider* s);


// read_card(card_read) reads at most two characters representing
// the value of a playing card.  If the first character is E,
// then it returns true.  Otherwise, it returns false and
// mutates *card_read to be the integer value of the card.
// A is read as 1, J is read as 11, 
// Q is read as 12 and K is read as 13.
// If an error occurs reading in the value, the function
// prints out an error message and terminates the program.
// effects: reads input and modifies *card_read
bool read_card(int* card_read);

// spider_print(s) prints out the statue of the game including
// the number of cards left in the stock pile
// the face-down and face-up cards in each tableau pile
// the number of complete decks in the foundation piles
// effects: produces output
void spider_print(struct spider* s);


// spider_get_stock(s) removes 10 cards from the stock pile
// and places 1 card face-up on top of each tableau pile.
// effects: may produce output and may mutate *s
void spider_get_stock(struct spider* s);

// spider_find_seq(s_src_up,temp,card) attempts
// to find a descending sequence of cards starting 
// with the provided card on top of s_src_up.  
// If such a sequence does not exist, 
// this function finds the longest descending sequence
// of cards on top of s_src_up.  After finding
// such a sequence, the function moves this sequence
// to temp in reverse order.  Then, the function
// returns true if the descending sequence ends with 
// the provided card.  It returns false otherwise.
// requires: s_src_up is non-empty.
//           s_src_up and temp are valid pointers.
//           1 <= card <= 13
bool spider_find_seq(struct stack* s_src_up,
	struct stack* temp,
	int card);

// spider_test_find_seq() tests the find seq helper function
// using assertion testing
void spider_test_find_seq(void);