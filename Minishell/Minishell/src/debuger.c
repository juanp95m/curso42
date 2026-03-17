#include "minishell.h"

/**
 @brief Print the list of tokens for debugging
 @param head Pointer to the head of the token list
 */
void	debug_print_tokens(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("Token: [%s], Type: %d, Quote: %d, Expand: %d Nesting: %d\n",
			tmp->value, tmp->type, tmp->quote, tmp->expandable, tmp->nesting);
		tmp = tmp->next;
	}
}

/**
 * @brief Print the list of commands for debugging
 * @param head Pointer to the head of the command list
 */
void	debug_print_commands(t_command *head)
{
	t_command	*tmp;
	int			cmd_index;
	int			arg_index;

	cmd_index = 0;
	tmp = head;
	while (tmp)
	{
		printf("Command %d:\n", cmd_index);
		printf("Builtin ?: %d (if > 8 Yes, 1 External)\n", tmp->builtin_type);
		arg_index = 0;
		while (tmp->args && tmp->args[arg_index])
		{
			printf("  Arg %d: %s\n", arg_index, tmp->args[arg_index]);
			arg_index++;
		}
		if (tmp->infile)
			printf("  Infile: %s\n", tmp->infile);
		if (tmp->heredoc_delim_count > 0)
		{
			arg_index = 0;
			while (arg_index < tmp->heredoc_delim_count)
			{
				printf("  Heredoc Delimiter %d: %s\n", arg_index,
					tmp->heredoc_delimiters[arg_index]);
				arg_index++;
			}
		}
		{
			int	oi = 0;
			while (oi < tmp->outfile_count)
			{
				printf("  Outfile[%d]: %s (append=%d)\n",
					oi, tmp->outfiles[oi], tmp->append_modes[oi]);
				oi++;
			}
		}
		printf("  Nesting: %d\n", tmp->nesting);
		printf("  Fullpath: %s\n", tmp->fullpath);
		tmp = tmp->next;
		cmd_index++;
	}
}

/**
 * @brief Helper to print indentation based on depth
 */
static void	print_indent(int level)
{
	while (level > 0)
	{
		printf("    ");
		level--;
	}
}

/**
 * @brief Recursive function to visualize the AST
 * Prints the tree structure with indentation
 */
void	debug_print_ast(t_node *node, int level)
{
	int	i;

	if (!node)
		return ;
	print_indent(level);
	if (node->type == NODE_PIPE)
		printf("\033[1;35m[PIPE]\033[0m\n");
	else if (node->type == NODE_AND)
		printf("\033[1;32m[&&]\033[0m\n");
	else if (node->type == NODE_OR)
		printf("\033[1;31m[||]\033[0m\n");
	else if (node->type == NODE_CMD)
	{
		printf("\033[1;36m[CMD]\033[0m ");
		if (node->cmd && node->cmd->args)
		{
			i = 0;
			while (node->cmd->args[i])
			{
				printf("'%s' ", node->cmd->args[i]);
				i++;
			}
			if (node->cmd->infile)
				printf("< %s ", node->cmd->infile);
			{
				int	oi = 0;
				while (oi < node->cmd->outfile_count)
				{
					if (node->cmd->append_modes[oi])
						printf(">> %s ", node->cmd->outfiles[oi]);
					else
						printf("> %s ", node->cmd->outfiles[oi]);
					oi++;
				}
			}
			if (node->cmd->heredoc_delim_count > 0)
				printf("<< %s ",
					node->cmd->heredoc_delimiters[
					node->cmd->heredoc_delim_count - 1]);
		}
		else
			printf("(empty)");
		printf("\n");
		return ;
	}
	debug_print_ast(node->left, level + 1);
	debug_print_ast(node->right, level + 1);
}
