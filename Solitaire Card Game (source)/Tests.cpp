#include "Tests.h"

void stack_test() {
	struct card H3 = { 3,'H' };
	struct card D4 = { 4,'D' };
	struct card S13 = { 13, 'S' };
	struct card C1 = { 1,'C' };

	struct stack* stk = stack_create();
	assert(stack_is_empty(stk));
	assert(stack_length(stk) == 0);
	stack_push(stk, H3);
	assert(stack_top(stk).num == 3);
	assert(stack_top(stk).suit == 'H');
	assert(!stack_is_empty(stk));
	assert(stack_length(stk) == 1);
	assert(stack_pop(stk).num == 3);
	assert(stack_is_empty(stk));
	stack_destroy(stk);

	stk = stack_create();
	stack_push(stk, H3);
	stack_push(stk, D4);
	stack_push(stk, S13);
	assert(stack_length(stk) == 3);
	stack_pop(stk);
	assert(stack_top(stk).suit == 'D');
	assert(stack_length(stk) == 2);
	assert(!stack_is_empty(stk));
	stack_push(stk, C1);
	stack_push(stk, H3);
	assert(stack_top(stk).suit == 'H');
	assert(stack_pop(stk).num == 3);
	assert(stack_pop(stk).num == 1);
	assert(stack_length(stk) == 2);
	assert(stack_pop(stk).suit == 'D');
	assert(stack_pop(stk).suit == 'H');
	assert(stack_is_empty(stk));
	stack_destroy(stk);

	stk = stack_create();
	stack_push(stk, H3);
	stack_push(stk, H3);
	stack_push(stk, H3);
	stack_push(stk, H3);
	stack_push(stk, H3);
	stack_push(stk, H3);
	stack_pop(stk);
	stack_pop(stk);
	stack_pop(stk);
	stack_pop(stk);
	stack_destroy(stk);

	std::cout << "Stack Test passed." << std::endl;
}

void spider_test_find_seq(void) {
	stack* temp = stack_create();
	stack* src = stack_create();
	card chosen = {};
	card S1 = { 1, 'S' };
	card S2 = { 2, 'S' };
	card S3 = { 3, 'S' };
	card S4 = { 4, 'S' };
	card S5 = { 5, 'S' };
	card S6 = { 6, 'S' };
	card S7 = { 7, 'S' };
	card S8 = { 8, 'S' };
	card S9 = { 9, 'S' };
	card S10 = { 10, 'S' };
	card S11 = { 11, 'S' };
	card S12 = { 12, 'S' };
	card S13 = { 13, 'S' };

	card H1 = { 1, 'H' };
	card H2 = { 2, 'H' };
	card H3 = { 3, 'H' };
	card H4 = { 4, 'H' };
	card H5 = { 5, 'H' };
	card H6 = { 6, 'H' };
	card H7 = { 7, 'H' };
	card H8 = { 8, 'H' };
	card H9 = { 9, 'H' };
	card H10 = { 10, 'H' };
	card H11 = { 11, 'H' };
	card H12 = { 12, 'H' };
	card H13 = { 13, 'H' };

	// Marmoset public test
	stack_push(src, S1);
	chosen = S1;
	bool found = spider_find_seq(src, temp, chosen);
	assert(found);
	assert(cardcmp(stack_pop(temp),S1));
	assert(stack_is_empty(src));
	assert(stack_is_empty(temp));

	// The first example
	stack_push(src, S5);
	stack_push(src, S4);
	stack_push(src, S3);
	stack_push(src, S2);
	chosen = S2;
	found = spider_find_seq(src, temp, chosen);
	assert(found);
	assert(cardcmp(stack_pop(temp),S2));
	assert(stack_is_empty(temp));
	assert(cardcmp(stack_pop(src),S3));
	assert(cardcmp(stack_pop(src), S4));
	assert(cardcmp(stack_pop(src), S5));
	assert(stack_is_empty(src));

	// The second example
	stack_push(src, S5);
	stack_push(src, S4);
	stack_push(src, S3);
	stack_push(src, S2);
	chosen = S5;
	found = spider_find_seq(src, temp, chosen);
	assert(found);
	assert(cardcmp(stack_pop(temp), S5));
	assert(cardcmp(stack_pop(temp), S4));
	assert(cardcmp(stack_pop(temp), S3));
	assert(cardcmp(stack_pop(temp), S2));
	assert(stack_is_empty(temp));
	assert(stack_is_empty(src));

	// My first example
	// This is a "normal" condition.
	stack_push(src, H13);
	stack_push(src, H12);
	stack_push(src, S11);
	stack_push(src, S10);
	stack_push(src, S9);
	stack_push(src, S8);
	stack_push(src, S7);
	stack_push(src, S6);
	chosen = S9;
	found = spider_find_seq(src, temp, chosen);
	assert(found);
	assert(cardcmp(stack_pop(temp), S9));
	assert(cardcmp(stack_pop(temp), S8));
	assert(cardcmp(stack_pop(temp), S7));
	assert(cardcmp(stack_pop(temp), S6));
	assert(stack_is_empty(temp));
	assert(cardcmp(stack_pop(src), S10));
	assert(cardcmp(stack_pop(src), S11));
	assert(cardcmp(stack_pop(src), H12));
	assert(cardcmp(stack_pop(src), H13));
	assert(stack_is_empty(src));

	// My second example
	// When it src reaches empty.
	stack_push(src, S12);
	stack_push(src, S11);
	stack_push(src, S10);
	stack_push(src, S9);
	stack_push(src, S8);
	stack_push(src, S7);
	stack_push(src, S6);
	chosen = S13;
	found = spider_find_seq(src, temp, chosen);
	assert(!found);
	assert(cardcmp(stack_pop(temp), S12));
	assert(cardcmp(stack_pop(temp), S11));
	assert(cardcmp(stack_pop(temp), S10));
	assert(cardcmp(stack_pop(temp), S9));
	assert(cardcmp(stack_pop(temp), S8));
	assert(cardcmp(stack_pop(temp), S7));
	assert(cardcmp(stack_pop(temp), S6));
	assert(stack_is_empty(temp));

	// My third example
	// When bottom of src are arbitrary cards, but top are good
	stack_push(src, H3);
	stack_push(src, S7);
	stack_push(src, H2);
	stack_push(src, S5);
	stack_push(src, S11);
	stack_push(src, S10);
	stack_push(src, S9);
	stack_push(src, S8);

	chosen = S10;
	found = spider_find_seq(src, temp, chosen);
	assert(found);
	assert(cardcmp(stack_pop(temp), S10));
	assert(cardcmp(stack_pop(temp), S9));
	assert(cardcmp(stack_pop(temp), S8));
	assert(stack_is_empty(temp));
	assert(cardcmp(stack_pop(src), S11));
	assert(cardcmp(stack_pop(src), S5));
	assert(cardcmp(stack_pop(src), H2));
	assert(cardcmp(stack_pop(src), S7));
	assert(cardcmp(stack_pop(src), H3));
	assert(stack_is_empty(src));

	// My fourth example
	// When cards are not consecutive (edge)
	stack_push(src, H3);
	stack_push(src, S7);
	stack_push(src, H2);
	stack_push(src, S5);
	stack_push(src, S11);
	stack_push(src, S10);
	stack_push(src, S11);
	stack_push(src, S8);

	chosen = S10;
	found = spider_find_seq(src, temp, chosen);
	assert(!found);
	assert(cardcmp(stack_pop(temp), S8));
	assert(stack_is_empty(temp));
	assert(cardcmp(stack_pop(src), S11));
	assert(cardcmp(stack_pop(src), S10));
	assert(cardcmp(stack_pop(src), S11));
	assert(cardcmp(stack_pop(src), S5));
	assert(cardcmp(stack_pop(src), H2));
	assert(cardcmp(stack_pop(src), S7));
	assert(cardcmp(stack_pop(src), H3));
	assert(stack_is_empty(src));

	// My fifth example
	// When cards are not consecutive (normal)
	stack_push(src, H3);
	stack_push(src, S7);
	stack_push(src, H2);
	stack_push(src, S5);
	stack_push(src, S11);
	stack_push(src, S9);
	stack_push(src, S8);
	chosen = S11;
	found = spider_find_seq(src, temp, chosen);
	assert(!found);
	assert(cardcmp(stack_pop(temp), S9));
	assert(cardcmp(stack_pop(temp), S8));	
	assert(stack_is_empty(temp));
	assert(cardcmp(stack_pop(src), S11));
	assert(cardcmp(stack_pop(src), S5));
	assert(cardcmp(stack_pop(src), H2));
	assert(cardcmp(stack_pop(src), S7));
	assert(cardcmp(stack_pop(src), H3));
	assert(stack_is_empty(src));

	// My sixth example
	// When cards founded sequences is at the bottom of the src
	stack_push(src, H8);
	stack_push(src, H7);
	stack_push(src, H6);
	stack_push(src, H5);
	stack_push(src, S11);
	stack_push(src, S9);
	stack_push(src, S8);
	chosen = H6;
	found = spider_find_seq(src, temp, chosen);
	assert(!found);
	assert(cardcmp(stack_pop(temp), S9));
	assert(cardcmp(stack_pop(temp), S8));
	assert(stack_is_empty(temp));
	assert(cardcmp(stack_pop(src), S11));
	assert(cardcmp(stack_pop(src), H5));
	assert(cardcmp(stack_pop(src), H6));
	assert(cardcmp(stack_pop(src), H7));
	assert(cardcmp(stack_pop(src), H8));
	assert(stack_is_empty(src));

	// My Seventh example
	stack_push(src, S1);
	chosen = S1;
	found = spider_find_seq(src, temp, chosen);

	assert(found);
	assert(cardcmp(stack_pop(temp), S1));
	assert(stack_is_empty(temp));
	assert(stack_is_empty(src));

	std::cout << "Spider_find_seq Test passed." << std::endl;

}
