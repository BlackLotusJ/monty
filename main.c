#include "monty.h"
#include <stdio.h>
#include <stdlib.h>


void monty_push(stack_t **stack, unsigned int line)
{
	int i;
	stack_t *temp, *new;

	new = malloc(sizeof(stack_t));

	if (new == NULL)
	{
		set_op_tok_error(malloc_error());
		return;
	}
	

	if (op_toks[1] == NULL)
	{
		set_op_tok_error(no_int_error(line));
		return;
	}
	for (i = 0; op_toks[1][i]; i++)
	{
		if (op_toks[1][i] == '-' && i==0)
			continue;
		if (op_toks[1][i] < '0' || op_toks[1][i] > '9')
		{
			set_op_tok_error(no_int_error(line));
			return;
		}
	}
	new->n = atoi(op_toks[1]);

	if (check_mode(*stack) == STACK)
	{
		tmp = (*stack)->next;
		new->prev = *stack;
		new->next = tmp;
		if (tmp)
			tmp->prev = new;
		(*stack)->next = new;
	}
	else
	{
		tmp = *stack;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		new->next = NULL;
		tmp->next = new;
	}
}

/**
 * monty_pall - Prints the values of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line: The current working line number of a Monty bytecodes file.
 */
void monty_pall(stack_t **stack, unsigned int line)
{
	stack_t *tmp = (*stack)->next;

	while (tmp)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
	(void)line;
}

/**
 * monty_pint - Prints the top value of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line: The current working line number of a Monty bytecodes file.
 */
void monty_pint(stack_t **stack, unsigned int line)
{
	if ((*stack)->next == NULL)
	{
		set_op_tok_error(pint_error(line));
		return;
	}

	printf("%d\n", (*stack)->next->n);
}


/**
 * monty_pop - Removes the top value element of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line: The current working line number of a Monty bytecodes file.
 */
void monty_pop(stack_t **stack, unsigned int line)
{
	stack_t *next = NULL;

	if ((*stack)->next == NULL)
	{
		set_op_tok_error(pop_error(line));
		return;
	}

	next = (*stack)->next->next;
	free((*stack)->next);
	if (next)
		next->prev = *stack;
	(*stack)->next = next;
}

/**
 * monty_swap - Swaps the top two value elements of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line: The current working line number of a Monty bytecodes file.
 */
void monty_swap(stack_t **stack, unsigned int line)
{
	stack_t *tmp;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		set_op_tok_error(short_stack_error(line, "swap"));
		return;
	}

	tmp = (*stack)->next->next;
	(*stack)->next->next = tmp->next;
	(*stack)->next->prev = tmp;
	if (tmp->next)
		tmp->next->prev = (*stack)->next;
	tmp->next = (*stack)->next;
	tmp->prev = *stack;
	(*stack)->next = tmp;
}

