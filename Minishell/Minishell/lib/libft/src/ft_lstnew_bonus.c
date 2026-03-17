/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:36:17 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/09/08 20:25:19 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node -> content = content;
	node -> next = NULL;
	node -> prev = NULL;
	node -> cost_a = 0;
	node -> cost_b = 0;
	node -> total_cost = 0;
	node -> is_cheapest = 0;
	node -> idx = 0;
	node -> target_idx = 0;
	return (node);
}

// int	main(void)
// {
// 	t_list *node;

// 	node = ft_lstnew("hi");
// 	printf("%s", (char *)(node -> content));
// 	return (0);
// }