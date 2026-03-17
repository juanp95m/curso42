/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:19:32 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/09 14:22:07 by mlermo-j         ###   ########.fr       */
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

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next != NULL)
	{
		lst = lst -> next;
	}
	return (lst);
}

// int	main(void)
// {
// 	t_list *node;
// 	t_list *last;

// 	node = generate_lst(7);
// 	printf("Size of list: %d\n", ft_lstsize(node));
// 	last = ft_lstlast(node);
// 	return (0);
// }
