/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:19:58 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/08/28 15:11:42 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst -> next;
	}
	return (i);
}

// int	main(void)
// {
// 	t_list *node;

// 	node = ft_lstnew("hi");
// 	printf("%d", ft_lstsize(node));
// 	return (0);
// }
