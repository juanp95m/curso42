/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:48:49 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/09 14:19:13 by mlermo-j         ###   ########.fr       */
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
// 	while (lst -> next != NULL)
// 	{
// 		printf("Node %d\n", *(int *)(lst->content));
// 		lst = lst -> next;
// 	}
// }
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = ft_lstlast(*lst);
	current -> next = new;
}
// int	main(void)
// {
// 	t_list *node;
// 	t_list *new;

// 	new = ft_lstnew((void*)8);
// 	node = generate_lst(7);
// 	printf("Size of list: %d\n", ft_lstsize(node));
// 	ft_lstadd_back(&node, new);
// 	print_list(node);
// 	return (0);
// }
