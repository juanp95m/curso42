#ifndef VBC_MY_H
# define VBC_MY_H

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node    *new_node(node n);
void    destroy_tree(node *n);
void    unexpected(char c);
int     accept(char **s, char c);
int     expect(char **s, char c);
node    *parse_term(char **s);
node    *parse_factor(char **s);
int     eval_tree(node *tree);
node    *parse_expr(char **s);

#endif
