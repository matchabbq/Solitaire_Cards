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
		
		card* temp = new card[stk->cap];

		for (int i = 0; i < stk->len; i++) {
			temp[i] = stk->content[i];
		}
		delete stk->content;
		stk->content = temp;
	}
	
	assert(stk->len < stk->cap);
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

struct card stack_top(const stack* stk) {
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

