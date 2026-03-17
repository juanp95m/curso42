/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:11:58 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/04/22 12:24:04 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

/*
#include "libft.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    char buffer[20 + 1];
    char *string1;
    ft_memset(buffer, 0, sizeof(buffer));
    string1 = (char *) ft_memset(buffer,'A', 10);
    printf("\n################### ft_bzero ###################\n");
    ft_bzero(string1+5, 5);
    printf("Printing previous buffer adding 5 nulls after pos 5: %s\n", buffer1);

}

*/