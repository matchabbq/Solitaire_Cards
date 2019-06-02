#include "Stack.h"

struct stack* stack_create(void) {
	struct stack* rv = (stack*)malloc(sizeof(struct stack));
	if (rv) {
		rv->content = (card*)malloc(sizeof(struct card) * 5);
		rv->len = 0;
		rv->cap = 5;
		return rv;
	}
	else {
		printf("Create_Stack failed.\n");
		EXIT_FAILURE;
		return;
	}
}

void stack_destroy(struct stack* stk) {
	if (stk) {
		free(stk->content);
		free(stk);
	}
	else {
		printf("Destroy_stack failed.\n");
		EXIT_FAILURE;
	}
}

void stack_push(struct stack* stk, struct card c) {
	assert(stk);
	if (stk->len == stk->cap) {
		stk->cap *= 2;
		stk->content = (card*)realloc(stk->content,
			sizeof(struct card) * stk->cap);
	}
	stk->content[stk->len] = c;
	stk->len += 1;
}

struct card stack_pop(struct stack* stk) {
	assert(stk);
	if (stk->len == 0) {
		printf("Stack_pop failed.\n");
		EXIT_FAILURE;
	}
	else {
		stk->len -= 1;
		return stk->content[stk->len];
	}
}

struct card stack_top(const struct stack* stk) {
	assert(stk);
	if (stk->len == 0) {
		printf("Stack_pop failed.\n");
		EXIT_FAILURE;
	}
	else {
		return stk->content[stk->len - 1];
	}
}

int stack_length(struct stack* stk) {
	assert(stk);
	return stk->len;
}

bool stack_is_empty(const struct stack* stk) {
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