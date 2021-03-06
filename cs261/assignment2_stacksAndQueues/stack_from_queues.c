/*
 * This is the file in which you'll write the functions required to implement
 * a stack using two queues.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Kathleen Ashley
 * Email: ashleyk@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"
#include "stack_from_queues.h"

/*
 * This function should allocate and initialize all of the memory needed for
 * your stack and return a pointer to the stack structure.
 */
struct stack_from_queues* stack_from_queues_create() 
{
  struct stack_from_queues* holder= malloc(sizeof(struct stack_from_queues));

  holder->q1 = queue_create();
  holder->q2 = queue_create();

  return holder;
}

/*
 * This function should free all of the memory allocated to a stack, including
 * the memory associated with each queue.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.  The function should
 *     exit the program with an error if stack is NULL.
 */
void stack_from_queues_free(struct stack_from_queues* stack) 
{
  if(stack == NULL)
  {
    printf("Error: Stack is NULL.\n");
    exit(1);
  }

  queue_free(stack->q1);
  queue_free(stack->q2);
  free(stack);
}

/*
 * This function should return 1 if a stack is completely empty or 0 if there
 * is at least one element stored in the stack.
 *
 * Params:
 *   stack - the stack whose emptiness is to be checked.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *
 * Return:
 *   Should return 1 if the stack is empty or 0 otherwise.
 */
int stack_from_queues_isempty(struct stack_from_queues* stack) 
{
  int returnVal = 1;
  if(stack == NULL)
  {
    printf("Error: Stack is NULL.\n");
    exit(1);
  }

  if(queue_isempty(stack->q1) == 1 && queue_isempty(stack->q2) == 1)
  {
    returnVal = 1;
  }
  else if(queue_isempty(stack->q1) == 0 || queue_isempty(stack->q2) == 0)
  {
    returnVal = 0;
  }

  return returnVal;
}

/*
 * Should push a new value onto a stack.
 *
 * Params:
 *   stack - the stack onto which to push a value.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *   value - the new value to be pushed onto the stack
 */

void swappy(struct queue* first, struct queue* second)
{
  while(queue_isempty(first) == 0)
  {
    queue_enqueue(second, queue_dequeue(first));
  }
}

void stack_from_queues_push(struct stack_from_queues* stack, int value) 
{
  if(stack == NULL)
  {
    printf("Error: Stack is NULL.\n");
    exit(1);
  }
  // put the newest element in queue 2.
  queue_enqueue(stack->q2, value);
  // move everything from q1 to q2 to ensure the newest
  // element is at the top.
  swappy(stack->q1, stack->q2);
  // move everything back to queue 1, leaving q2 empty.
  swappy(stack->q2,stack->q1);
}

/*
 * Should return a stack's top value without removing that value from the
 * stack.
 *
 * Params:
 *   stack - the stack from which to read the top value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack.
 */
int stack_from_queues_top(struct stack_from_queues* stack) 
{
  if(stack == NULL || stack_from_queues_isempty(stack) == 1)
  {
    printf("Error: Stack is NULL or empty.\n");
    exit(1);
  }

  // the newest element would be on top of q1.
  return queue_front(stack->q1);
}

/*
 * Should remove the top element from a stack and return its value.
 *
 * Params:
 *   stack - the stack from which to pop a value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack before that value
 *   is popped.
 */
int stack_from_queues_pop(struct stack_from_queues* stack) 
{
  if(stack == NULL  || stack_from_queues_isempty(stack))
  {
    printf("Error: Stack is NULL or empty.\n");
    exit(1);
  }

  return queue_dequeue(stack->q1);
}
