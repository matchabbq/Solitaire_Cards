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
static struct spider * spider_init_stacks(void) {
	struct spider* s = new (struct spider);
	s->stock = stack_create();
	for (int i = 0; i < 10; i++) {
		s->tableau_down[i] = stack_create();
		s->tableau_up[i] = stack_create();
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
static struct card get_random_card(int* card_count) {
	assert(card_count);
	
	int card_random = rand() % CARD_COUNT_SIZE; // returns 0 - 51
	while (card_count[card_random] == 0) {
		card_random = rand() % CARD_COUNT_SIZE;
	}
	card_count[card_random] -= 1; // Modify card_counter
	int suit = card_random / 13; // 0-12=>0, 13-25 =>1, 26-38=>2, 39-51=>3
	int cardnum = card_random % 13 + 1;
	card rv = {cardnum,0};
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

int suit_to_num(char s) {
	if (s == 'S') {
		return 0;
	}
	else if (s == 'H') {
		return 1;
	}
	else if (s == 'C') {
		return 2;
	}
	else {
		return 3;
	}
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
	int *card_count) {

	assert(s);
	assert(card_count);
	assert(0 <= index);
	assert(index <= 9);
	assert(num_down == 4 || num_down == 5);
	assert(num_up == 1);

	for (int i = 0; i < num_down; i++) {
		card random_card = get_random_card(card_count);
		stack_push(s->tableau_down[index], random_card);
	}
	for (int i = 0; i < num_up; i++){
		card random_card = get_random_card(card_count);
		stack_push(s->tableau_up[index], random_card);
	}
}

struct spider* spider_init_random(int level, int seed) {
	assert(level == 1 || level == 2 || level == 3);
	struct spider* s;
	const int STOCK_SIZE_INITIAL = 50;
	
	int card_count[52] = { 0 };
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
		card random_card = get_random_card(card_count);
		stack_push(s->stock, random_card);
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

void spider_print(struct spider* s) {
	assert(s);
	std::cout << "The number of cards left in the stock pile: " << s->stock_size << std::endl;
	std::cout << "The number of completed decks: " << s->comp_decks << std::endl;

	stack* temp = stack_create();
	card top;

	//Face down. Pops a tableau_down to temp until empty, cout " _", then push them back.
	for (int i = 0; i < 10; i++) {
		std::cout << i << ":";
		while (!stack_is_empty(s->tableau_down[i])) {
			stack_push(temp, stack_pop(s->tableau_down[i]));
			std::cout << " _";
		}
		while (!stack_is_empty(temp)) {
			stack_push(s->tableau_down[i], stack_pop(temp));
		}

		//Faceup
		while (!stack_is_empty(s->tableau_up[i])) {
			stack_push(temp, stack_pop(s->tableau_up[i]));
		}
		while (!stack_is_empty(temp)) {
			top = stack_pop(temp);
			// push them back + cout
			std::cout << " " << top.suit;
			if (top.num == 1) {
				std::cout << "A";
			}
			else if (top.num == 11) {
				std::cout << "J";
			}
			else if (top.num == 12) {
				std::cout << "Q";
			}
			else if (top.num == 13) {
				std::cout << "K";
			}
			else {
				std::cout << top.num;
			}
			stack_push(s->tableau_up[i], top);
		}
		std::cout << std::endl;
	}
}

void spider_get_stock(struct spider* s) {
	assert(s);

	// Error messages:
	// Check for stock
	if (stack_is_empty(s->stock)) {
		std::cout << "Error getting cards from the stock. The stock is empty" << std::endl;
		return;
	}
	//Check for empty tableau
	for (int i = 0; i < 10; i++) {
		if (stack_is_empty(s->tableau_down[i]) &&
			stack_is_empty(s->tableau_up[i])) {
			std::cout << "Error getting cards from the stock. Tableau " << i << " is empty." << std::endl;
			return;
		}
	}

	// When everything's fine, distribute 10 cards:
	for (int i = 0; i < 10; i++) {
		stack_push(s->tableau_up[i], stack_pop(s->stock));
	}
	s->stock_size -= 10;
}


bool spider_find_seq(stack* s_src_up, stack* temp, card chosencard) {
	assert(s_src_up);
	assert(s_src_up);
	assert(temp);
	assert(!stack_is_empty(s_src_up));

	bool flag = 0;
	card mytop = {};
	card lasttop = {};

	while (1) {
		if (stack_is_empty(s_src_up)) {
			return false;
		}

		// If this is the first one.
		if (flag == 0) {
			mytop = stack_pop(s_src_up);
			flag = 1;
			stack_push(temp, mytop);
			if (mytop.suit == chosencard.suit &&
				mytop.num == chosencard.num) {
				return true;
			}
			continue;
		}

		lasttop = mytop;
		mytop = stack_pop(s_src_up);
		stack_push(temp, mytop);

		if (lasttop.suit != mytop.suit ||
			lasttop.num != mytop.num - 1) {
			stack_push(s_src_up, stack_pop(temp));
			return false;
		}
		if (mytop.suit == chosencard.suit &&
			mytop.num == chosencard.num) {
			return true;
		}
	}
	return false;
}

bool cardcmp(card c1, card c2) {
	return (c1.suit == c2.suit && c1.num == c2.num);
}

void move_back(stack* temp, stack* origin) {
	assert(temp);
	assert(origin);
	while (!stack_is_empty(temp)) {
		stack_push(origin, stack_pop(temp));
	}
}

void check_flip(struct spider* s) {
	assert(s);
	for (int i = 0; i < 10; i++) {
		if (stack_is_empty(s->tableau_up[i])) {
			if (stack_is_empty(s->tableau_down[i])) {
				continue;
			}
			else {
				stack_push(s->tableau_up[i],stack_pop(s->tableau_down[i]));
			}
		}
	}
}

void check_remove(struct spider* s, int dest) {
	assert(s);
	stack* temp = stack_create();

	card S1 = { 1, 'S' };
	card H1 = { 1, 'H' };
	card C1 = { 1, 'C' };
	card D1 = { 1, 'D' };
	card S13 = { 13, 'S' };
	card H13 = { 13, 'H' };
	card C13 = { 13, 'C' };
	card D13 = { 13, 'D' };
	if (cardcmp(stack_top(s->tableau_up[dest]), S1)) {
		if (spider_find_seq(s->tableau_up[dest], temp, S13) == 1) {
			s->comp_decks++;
			stack_destroy(temp);
			return;
		}
		move_back(temp, s->tableau_up[dest]);
	}
	if (cardcmp(stack_top(s->tableau_up[dest]), H1)) {
		if (spider_find_seq(s->tableau_up[dest], temp, H13) == 1) {
			s->comp_decks++;
			stack_destroy(temp);
			return;
		}
		move_back(temp, s->tableau_up[dest]);
	}
	if (cardcmp(stack_top(s->tableau_up[dest]), C1)) {
		if (spider_find_seq(s->tableau_up[dest], temp, C13) == 1) {
			s->comp_decks++;
			stack_destroy(temp);
			return;
		}
		move_back(temp, s->tableau_up[dest]);
	}
	if (cardcmp(stack_top(s->tableau_up[dest]), D1)) {
		if (spider_find_seq(s->tableau_up[dest], temp, D13) == 1) {
			s->comp_decks++;
			stack_destroy(temp);
			return;
		}
		move_back(temp, s->tableau_up[dest]);
	}
}

void spider_move(struct spider* s,
	int src, card chosen, int dest) {
	assert(s);

	stack* temp = stack_create();
	card temp_top;
	card dest_top;

	// This is very not likely to happen, but if source is empty.
	if (stack_is_empty(s->tableau_up[src])) {
		std::cout << "Invalid move." << std::endl;
		return;
	}

	// Here the tops of src are moved into temp.
	if (spider_find_seq(s->tableau_up[src], temp, chosen)) {
		// If the required sequence can be obtained, we start checking for match.
		if (stack_is_empty(s->tableau_up[dest])) {
			move_back(temp, (s->tableau_up[dest]));
			check_flip(s);
		}
		else {
			// If dest is not empty, then check if they are consecutive
			temp_top = stack_top(temp);
			dest_top = stack_top(s->tableau_up[dest]);
			if (temp_top.num == dest_top.num - 1) {
				// If matched, push the cards from temp back to dest.
				// Note that suit does not matter here.
				move_back(temp, s->tableau_up[dest]);
				// Check for complete set and flipping.
				check_remove(s, dest);
				check_flip(s);
			}
			else {
				// When the required sequence can be found, but doesn't match.
				move_back(temp, s->tableau_up[src]);
				return;
			}
		}
	}

	else {
		// when the required sequence cannot even be found
		move_back(temp, s->tableau_up[src]);
		std::cout << "Invalid move.\n" << std::endl;
		return;
	}		
}
