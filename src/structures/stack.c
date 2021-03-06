/*----- Includes -----*/

#include <stdlib.h>
#include "stack.h"
#include "list.h"

/*----- Type Definitions -----*/

struct stack {
  list_t *lst;
};

/*----- Function Implementations -----*/

stack_t *create_stack(void (*destruct) (void *), int elem_len) {
  stack_t *stack = malloc(sizeof(stack_t));

   if (stack) stack->lst = create_list(elem_len, destruct);
   if (!stack->lst) {
     free(stack);
     stack = NULL;
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

int stack_peek(stack_t *stack, void *buf) {
  if (!stack || !buf) return STACK_INVAL;
  if (lhead(stack->lst, buf) == LIST_EMPTY) return STACK_EMPTY;
  else return STACK_SUCCESS;
}

stack_t *stack_dup(stack_t *stack, void (*destruct) (void *)) {
  stack_t *dup = create_stack(destruct, lelem_len(stack->lst));
  char *voidbuf = malloc(lelem_len(stack->lst));

  list_iterator_t *it = literate_start(stack->lst, 0);
  while (literate_next(it, voidbuf) == LIST_SUCCESS) rpush(dup->lst, voidbuf);
  literate_stop(it);

  free(voidbuf);
  return dup;
}

void destroy_stack(stack_t *stack) {
  destroy_list(stack->lst);
  free(stack);
}
