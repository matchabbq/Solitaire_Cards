// a header file for stack
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

struct stack {
    int len;
    int cap;
    int* data;
};

// create a new stack in heap
struct stack* create_stack(void);

// destory a stack and relase memory
void destory_stack(struct stack *s);

// is_empty checks whether a stack is empty. 
// returns true if it is.
bool is_empty(struct stack *s);

// stack_push add p to the front of s.
// require: s cannot be empty
// effect: will modify s
// runtime: O(1)
void stack_push(int p, struct stack *s);

// stack_pop removes the first value in s, and returns its value.
// require: s cannot be empty
// effect: will modify s
// runtime: O(1)
int stack_pop(struct stack *s);

// stack_top returns the top value of a stack;
// require: s cannot be empty
int stack_top(struct stack *s);

// stack_print print a stack, if it is empty, print empty stack
void stack_print(struct stack *s);
