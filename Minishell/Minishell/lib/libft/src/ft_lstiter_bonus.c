/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:53:17 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/08 18:43:57 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//REDO THE MAIN TO UNDERSTAND THE PROCESS

#include "libft.h"

// static t_list *generate_lst(int size)
// {
// 	t_list	*head = NULL;
// 	t_list	*current = NULL;
// 	t_list	*new;
// 	int		*n;
// 	int		i = 0;

// 	while (i < size)
// 	{
// 		n = malloc(sizeof(int));
// 		if (!n)
// 			return NULL;
// 		*n = i;
// 		new = ft_lstnew(n);
// 		if (!new)
// 			return NULL;
// 		if (!head)
// 			head = new;
// 		else
// 			current->next = new;
// 		current = new;
// 		i++;
// 	}
// 	return head;
// }

// static void	print_list(t_list *lst)
// {
// 	while (lst->next != NULL)
// 	{
// 		if (lst->content)
// 			printf("Node %d\n", *(int *)(lst -> content));
// 		else
// 			printf("FREED\n");
// 		lst = lst -> next;
// 	}
// 	if (lst->content)
// 		printf("Node %d\n", *(int *)(lst -> content));
// 	else
// 		printf("FREED\n");
// }

// void	add_content(void *__ptr)
// {
// 	t_list *node;

// 	node = (t_list *)__ptr;
// 	node -> content = "content new";
// 	free(node);
// }

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst -> content);
		lst = lst -> next;
	}
}

// int	main(void)
// {
// 	t_list *node;

// 	node = generate_lst(7);
// 	printf("Size of list: %d\n", ft_lstsize(node));
// 	printf("Before change:\n");
// 	print_list(node);
// 	ft_lstiter(node, add_content);
// 	printf("\nAfter deletion:\n");
// 	print_list(node);
// }
