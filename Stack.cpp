#include "Stack.h"

struct stack* stack_create(void) {
	stack* rv = new stack();
	if (rv) {
		rv->content = new card[5];
		rv->len = 0;
		rv->cap = 5;
		return rv;
	}
	else {
		std::cerr << "Create_Stack failed." << std::endl;
		_Exit(3);
	}
}

void stack_destroy(stack* stk) {
	if (stk) {
		delete stk->content;
		delete stk;
	}
	else {
		std::cerr << "stack_destory failed." << std::endl;
		_Exit(3);
	}
}

void stack_push(stack* stk, card c) {
	assert(stk);
	if (stk->len == stk->cap) {
		stk->cap *= 2;
		stack* new_stk = new stack();
		new_stk->content = new card[stk->cap];
		new_stk->len = stk->len;
		new_stk->cap = stk->cap;
		for (int i = 0; i < stk->len; i++) {
			new_stk->content[i] = stk->content[i];
		}
		delete stk->content;
		delete stk;
		stk = new_stk;
	}
	stk->content[stk->len] = c;
	stk->len += 1;
}

struct card stack_pop(stack* stk) {
	assert(stk);
	if (stk->len == 0) {
		std::cout << "Stack_pop failed." << std::endl;
		_Exit(2);
	}
	else {
		stk->len -= 1;
		return stk->content[stk->len];
	}
}

struct card stack_top(stack* stk) {
	assert(stk);
	if (stk->len == 0) {
		std::cout << "Stack_pop failed." << std::endl;
		_Exit(2);
	}
	else {
		return stk->content[stk->len - 1];
	}
}

int stack_length(stack* stk) {
	assert(stk);
	return stk->len;
}

bool stack_is_empty(const stack* stk) {
	assert(stk);
	return (!stk->len);
}
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

	printf("Stack Test passed.\n");
}

