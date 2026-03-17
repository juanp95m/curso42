/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:31:00 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/09 14:16:03 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}
// int	main(void)
// {
// 	t_list	*new;
// 	t_list	**old;
// 	old = ft_lstnewsize("hi", 3);
// 	new = ft_lstnew("new_content");
// 	printf("%s", old -> content);
// 	ft_lstadd_front(old, new);
// 	printf("%s", old -> content);
// 	return(0);
// }
