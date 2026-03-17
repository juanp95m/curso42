/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:22:05 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/09 14:15:33 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new_node;
	t_list	*modified;

	if (!lst)
		return (NULL);
	head = NULL;
	while (lst != NULL)
	{
		modified = f(lst -> content);
		new_node = ft_lstnew(modified);
		if (!new_node)
		{
			del(modified);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, new_node);
		lst = lst -> next;
	}
	return (head);
}

// static void *duplicate_content(void *content)
// {
// 	return ft_strdup((char *)content);
// }

// static void print_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("%s\n", (char *)lst->content);
// 		lst = lst->next;
// 	}
// }

// int main(void) {
// 	t_list *original = NULL;
// 	t_list *mapped = NULL;

// 	ft_lstadd_back(&original, ft_lstnew(ft_strdup("apple")));
// 	ft_lstadd_back(&original, ft_lstnew(ft_strdup("banana")));
// 	ft_lstadd_back(&original, ft_lstnew(ft_strdup("cherry")));

// 	mapped = ft_lstmap(original, duplicate_content, free);

// 	printf("Original list:\n");
// 	print_list(original);

// 	printf("\nMapped list:\n");
// 	print_list(mapped);

// 	ft_lstclear(&original, free);
// 	ft_lstclear(&mapped, free);

// 	return 0;
// }
