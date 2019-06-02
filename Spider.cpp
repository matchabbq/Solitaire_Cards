#include "Spider.h"

static const int TABLEAU_SIZE = 10;
static const int DECK_SIZE_1 = 13;
static const int DECK_SIZE_2 = 26;
static const int DECK_SIZE_3 = 52;
static const int CARD_COUNT_SIZE = 52;
static const int NUM_DECK = 8;
const int Spade = 0;
const int Heart = 1;
const int Club = 2;
const int Diamond = 3;

// spider_init_stacks(s) initializes all
// the stacks in the spider struct, and returns the spider struct.
static struct spider* spider_init_stacks(void) {
	struct spider* s = (spider*)malloc(sizeof(struct spider));
	s->stock = stack_create();
	for (int i = 0; i < 10; i++) {
		s->tableau_down[i] = (stack*)malloc(sizeof(struct stack));
		s->tableau_up[i] = (stack*)malloc(sizeof(struct stack));
	}
	s->stock_size = 5;
	s->comp_decks = 0;
	return s;
}

// get_random_card(card_count) repeatedly generates
// a random card value from 1 to 13 with different suit until 
// the number of cards left for that value is 
// negative according to card_count.
// Spade: 1-13
// Heart: 14-26
// Club: 27-39
// Diamond: 40-52
// requires: card_count is a valid pointer.
//           length of card_count is 52.
static struct card get_random_card(int card_count[]) {
	assert(card_count);

	int card_random = rand() % CARD_COUNT_SIZE + 1;
	while (card_count[card_random - 1] == 0) {
		card_random = rand() % CARD_COUNT_SIZE + 1;
	}
	int suit = (card_random - 1) / 13;
	struct card rv = { card_random,0 };
	if (suit == Spade) {
		rv.suit = 'S';
	}
	else if (suit == Heart) {
		rv.suit = 'H';
	}
	else if (suit == Club) {
		rv.suit = 'C';
	}
	else if (suit == Diamond) {
		rv.suit = 'D';
	}
	return rv;
}

// init_tableau(s,index,num_down,num_up,card_count)
// initialize the index-th tableau randomly by 
// putting num_down cards in the face-down pile and
// num_up cards in the face-up pile.
// requires: s and card_count are valid pointers.
//           0 <= index <= 9
//           4 <= num_down <= 5
//           num_up == 1
//           length of card_count is 13.
// effects: mutates *s

static void init_tableau(struct spider* s,
	int index,
	int num_down,
	int num_up,
	int card_count[]) {

	assert(s);
	assert(card_count);
	assert(0 <= index);
	assert(index <= 9);
	assert(num_down == 4 || num_down == 5);
	assert(num_up == 1);

	for (int i = 0; i < num_down; i++) {
		struct card random_card = get_random_card(card_count);
		stack_push(s->tableau_down[index], random_card);
		card_count[random_card.suit * 10 + random_card.num - 1] -= 1;
	}
	for (int i = 0; i < num_up; i++) {
		struct card random_card = get_random_card(card_count);
		stack_push(s->tableau_up[index], random_card);
		card_count[random_card.suit * 10 + random_card.num - 1] -= 1;
	}
}

struct spider* spider_init_random(int level, int seed) {
	assert(level == 1 || level == 2 || level == 3);
	struct spider* s;
	const int STOCK_SIZE_INITIAL = 50;

	int card_count[51] = { 0 };
	int deck_size = 0;
	int deck_count = 0;
	if (level == 1) {
		deck_size = DECK_SIZE_1;
		deck_count = 8;
	}
	else if (level == 2) {
		deck_size = DECK_SIZE_2;
		deck_count = 4;
	}
	else if (level == 3) {
		deck_size = DECK_SIZE_3;
		deck_count = 2;
	}

	for (int i = 0; i < deck_size; i++) {
		card_count[i] = deck_count;
	}

	srand(seed);

	// initialize the stacks
	s = spider_init_stacks();

	// initialize stock pile;
	s->stock_size = STOCK_SIZE_INITIAL; // 50
	for (int i = 0; i < STOCK_SIZE_INITIAL; i++) {
		struct card random_card = get_random_card(card_count);
		stack_push(s->stock, random_card);
		card_count[random_card.suit * 10 + random_card.num - 1] -= 1;
	}

	// init the tableaus
	for (int i = 0; i < 4; ++i) {
		init_tableau(s, i, 5, 1, card_count);
	}
	for (int i = 4; i <= TABLEAU_SIZE - 1; ++i) {
		init_tableau(s, i, 4, 1, card_count);
	}

	s->comp_decks = 0;
	return s;
}

bool spider_has_won(const struct spider* s) {
	assert(s);
	return (s->comp_decks == NUM_DECK);
}

