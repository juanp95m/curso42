// push_swap.h

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h> //  malloc, free, atoi
# include <stdio.h>  // printf (debugging)
# include <unistd.h> // write
# include <stddef.h> // NULL
# include <limits.h>
# include "./libft/libft.h"

// DEFINITION OF STACK NODES STRUCTURE 
typedef struct s_stack
{
    int             value;       // integer num
    int             index;       // simply index for Radix
    struct s_stack  *next;       // pointer to the next node
}   t_stack;

// --- PROTOTIPES OF FUNCTIONS ---
//main
void    print_stack(t_stack *stack);

// parsing.c

void parse_arguments(int argc, char **argv, t_stack **stack_a);
void process_split_args(char **args, t_stack **stack_a);
int is_valid_integer(const char *str);
int has_duplicates(t_stack *stack);
void free_stack_and_error(t_stack **stack);
long ft_atol(const char *str);
void free_split_local(char **arr);


// operations_*.c

void    sa(t_stack **stack_a, int print);
void    sb(t_stack **stack_b, int print);
void    ss(t_stack **stack_a, t_stack **stack_b, int print);
void    pa(t_stack **stack_a, t_stack **stack_b, int print);
void    pb(t_stack **stack_a, t_stack **stack_b, int print);
void    ra(t_stack **stack_a, int print);
void    rb(t_stack **stack_b, int print);
void    rr(t_stack **stack_a, t_stack **stack_b, int print);
void    rra(t_stack **stack_a, int print);
void    rrb(t_stack **stack_b, int print);
void    rrr(t_stack **stack_a, t_stack **stack_b, int print);

// algorithm.c
void    sort_stack(t_stack **stack_a);
void    radix_sort(t_stack **a, t_stack **b);
void    sort_three(t_stack **a);
void    sort_five(t_stack **a, t_stack **b);
int     is_sorted(t_stack *stack);
int     find_min_value(t_stack *stack);
int     find_node_position(t_stack *stack, int value);

// utils_*.c
t_stack *ft_stack_new(int value);
void    ft_stack_add_back(t_stack **stack, t_stack *new_node);
int     ft_stack_size(t_stack *stack);
t_stack *ft_stack_last(t_stack *stack);
void    free_stack(t_stack **stack);

#endif