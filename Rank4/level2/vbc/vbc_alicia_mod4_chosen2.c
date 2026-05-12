#include <stdio.h>
#include <stdlib.h> //cambiar malloc.h por stdlib.h
#include <ctype.h>

typedef struct node { //no changes
	enum {
		ADD,
		MULTI,
		VAL
	}   type;
	int val;
	struct node *l;
	struct node *r;
}	node;

node	*new_node(node n) //no changes
{
	node *ret = calloc(1, sizeof(n));
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

void    destroy_tree(node *n) //no changes
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void    unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n"); //swap in the message file for input
}

int accept(char **s, char c)
{
	if (**s == c) //add == c
	{
		(*s)++;
		return (1);
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

node	*val(char **s); //add this function

node *dt(node *n) //add this function
{
	destroy_tree(n);
	return (NULL);
}

node *create_node(int type, node *ret, node *right, char **s) //add this function
{
	if (type == VAL)
		return (new_node((node){.type = VAL, .val = **s - '0'}));
	else if (type == ADD)
		return (new_node((node){.type = ADD, .l = ret, .r = right}));
	else if (type == MULTI)
		return (new_node((node){.type = MULTI, .l = ret, .r = right}));
	return (NULL);
}

node *operation(char **s, int op_type)
{
	// Si estamos en ADD, el siguiente nivel es MULTI. Si estamos en MULTI, es VAL.
	int next_op = (op_type == ADD) ? MULTI : VAL;
	char symbol = (op_type == ADD) ? '+' : '*';

	// Evaluamos el primer elemento (o la primera multiplicación)
	node *ret = (next_op == VAL) ? val(s) : operation(s, next_op);
	node *right;

	while (ret && accept(s, symbol))
	{
		right = (next_op == VAL) ? val(s) : operation(s, next_op);
		if (!right)
			return (dt(ret));
		if (!(ret = create_node(op_type, ret, right, s)))
			return (dt(right));
	}
	return (ret);
}

node	*val(char **s) //add this function
{
	node	*ret;
	
	if (isdigit(**s))
	{
		ret = create_node(VAL, NULL, NULL, s);
		(*s)++;
		return (ret);
	}
	if (accept(s, '('))
	{
		ret = operation(s, ADD);
		if (!ret || !expect(s, ')'))
			return(dt(ret));
		return (ret);
	}
	unexpected(**s);
	return (NULL);
}

node    *parse_expr(char *s)
{
	node	*ret = operation(&s, ADD); //add this line

	if (ret && *s) //add ret &&
	{
		unexpected(*s); //add this line
		return(dt(ret));
	}
	return (ret);
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
	return (0); //add this line
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	node *tree = parse_expr(argv[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0); //add this line
}
