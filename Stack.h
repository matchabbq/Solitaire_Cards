// Header file for Stack ADT
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <iostream>

//#ifndef, #define and #endif prevents redefinition of structures
#ifndef card_stack_struct
#define card_stack_struct
struct card {
	int num;
	char suit;
};

struct stack {
	struct card* content;
	int len;
	int cap;
};
#endif

struct stack* stack_create(void);

void stack_destroy(struct stack* stk);

void stack_push(struct stack* stk, struct card c);

struct card stack_top(const struct stack* stk);

struct card stack_pop(struct stack* stk);

int stack_length(struct stack* stk);

bool stack_is_empty(const struct stack* stk);

void stack_test();
