/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:48:42 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/12 19:52:56 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

// int	main(void)
// {
// 	t_list *to_delete;
// 		t_list *node;

// 	node = generate_lst(7);
// 	printf("Size of list: %d\n", ft_lstsize(node));

// 	printf("Before deletion:\n");
// 	print_list(node);

// 	to_delete = node->next; // e.g., delete the second node
// 	node->next = to_delete->next; // unlink it from the list

// 	ft_lstdelone(to_delete, free); // now safely delete it

// 	printf("\nAfter deletion:\n");
// 	print_list(node);
// }
