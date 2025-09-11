// push_swap.h

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h> //  malloc, free, atoi
# include <stdio.h>  // printf (temporal, para debugging)
# include <unistd.h> // write
# include <stddef.h> // NULL
# include <limits.h>
# include "./libft/libft.h"

// DEFINITION OF STACK NODES STRUCTURE 
typedef struct s_stack
{
    int             value;       // integer num
    int             index;       // simply index for Radix
    struct s_stack  *next;       // poniter to the next node
}   t_stack;

// --- PROTOTIPES OF FUNCTIONS ---

// main.c


// parsing.c

void parse_arguments(int argc, char **argv, t_stack **stack_a);


// operations_*.c
void    sa(t_stack **stack_a, int print);
void    pb(t_stack **stack_a, t_stack **stack_b, int print);
// ...  ...

// algorithm.c
void    sort_stack(t_stack **stack_a, t_stack **stack_b);

// utils_*.c
t_stack *ft_stack_new(int value);
void    ft_stack_add_back(t_stack **stack, t_stack *new_node);
int     ft_stack_size(t_stack *stack);
void    free_stack(t_stack **stack);
// ... more prototipes ...

#endif