/*----- Includes -----*/

#include <stdlib.h>
#include "stack.h"
#include "list.h"

/*----- Type Definitions -----*/

struct stack {
  list_t *lst;
};

stack_t *create_stack(void (*destruct) (void *), int elem_len) {
  stack_t *stack = malloc(sizeof(stack_t));

   if (stack) {
     stack->lst = create_list(elem_len, destruct);
   }

   return stack;
}

void stack_push(stack_t *stack, void *data) {
  if (!stack || !data) return;
  lpush(stack->lst, data);
}

int stack_pop(stack_t *stack, void *buf) {
  if (!stack || !buf) return STACK_INVAL;
  if (lpop(stack->lst, buf) == LIST_EMPTY) return STACK_EMPTY;
  else return STACK_SUCCESS;
}

void destroy_stack(stack_t *stack) {
  destroy_list(stack->lst);
  free(stack);
}