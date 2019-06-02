#include "stack.h"

// This module will create a stack

struct stack* create_stack(void){
    struct stack *s =  malloc(sizeof(struct stack));
    s->cap = 10;
    s->len = 0;
    s->data = malloc(sizeof(int) * s->cap);
    return s;
}

void destory_stack(struct stack *s){
    free(s->cap);
    free(s->len);
    free(s->data);
    free(s);
}

bool is_empty(struct stack *s){
    if(s->len == 0){
        return true;
    } else {
        return false;
    }
}

void stack_push(int p, struct stack *s){
    assert(s);
    if (s->len == s->cap){
        s->cap *= 2;
        s->data = realloc(s->data, sizeof(int) * s->cap);
    }
    s->len ++;
    s->data[s->len] == p;
}

int stack_pop(struct stack *s){
    assert(s);
    int current = s->data[s->len];
    s->len --;
    return current;
}

int stack_top(struct stack *s){
    assert(s);
    return s->data[s->len];
}

void stack_print(struct stack *s){
    if (s == NULL) {
        printf("empty stack");
    } else {
        for (int i = s->len; i > 0; i ++) {
            printf("The %dth: %d\n", s->data[i], s->data[i]);
        }
    }
}