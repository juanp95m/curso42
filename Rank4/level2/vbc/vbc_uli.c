#include "vbc_uli.h"

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->l)
        destroy_tree(n->l);
    if (n->r)
        destroy_tree(n->r);
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
    if (**s)
    {
        if (**s != c)
            return (0);
        else if (**s == c)
        {
            (*s)++;
            return (1);
        }
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

node    *parse_term(char **s)
{
    node    *lhs = NULL;
    node    *rhs = NULL;
    
    lhs = parse_factor(s);
    while (accept(s, '*'))
    {
        rhs = parse_factor(s);
        if (!rhs || !lhs)
        {
            destroy_tree(lhs);
            return (NULL);
        }
        lhs = new_node((node){MULTI, 0, lhs, rhs});
    }
    return (lhs);
}

node    *parse_expr(char **s)
{
    node    *lhs = NULL;
    node    *rhs = NULL;

    lhs = parse_term(s);
    while (accept(s, '+'))
    {
        rhs = parse_term(s);
        if (!rhs || !lhs)
        {
            destroy_tree(lhs);
            return (NULL);
        }
        lhs = new_node((node){ADD, 0, lhs, rhs});
    }
    return (lhs);
}

node    *parse_factor(char **s)
{
    node *ret;

    ret = NULL;
    if (isdigit(*(*s)))
    {
        ret = new_node((node){VAL, *(*s) - '0', NULL, NULL});
        (*s)++;
        return (ret);
    }
    else if (*(*s) == '(')
    {
        (*s)++;
        ret = parse_expr(s);
        if (!expect(s, ')'))
        {
            destroy_tree(ret);
            return (NULL);
        }
        return (ret);
    }
    else
    {
        unexpected(*(*s));
        destroy_tree(ret);
        return (NULL);
    }
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
    return (0);
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("0\n");
        return (0);
    }
    if (argc > 2)
        return (1);
    node *tree = parse_expr(&argv[1]);
    if (!tree)
        return (1);
    if (*argv[1])
    {
        unexpected(*argv[1]);
        return (1);
    }
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    return (0);
}
