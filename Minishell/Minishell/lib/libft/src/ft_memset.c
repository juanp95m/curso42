/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:10:33 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/04/21 20:10:36 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*r;

	i = 0;
	r = s;
	while (i < n)
	{
		r[i] = c;
		i++;
	}
	return (s);
}
// s = (void *)r;

/*
#include "libft.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    printf("\n################### ft_memset ###################\n");
    char buffer[20 + 1];
    char *string;
    ft_memset(buffer, 0, sizeof(buffer));
    string = (char *) ft_memset(buffer,'A', 10);
    printf("\nBuffer contents: %s\n", string);
    ft_memset(buffer+10, 'B', 10);
    printf("\nBuffer contents: %s\n", buffer);

    printf("\n####### original memset \n");
    char buffer1[20 + 1];
    char *string1;
    memset(buffer1, 0, sizeof(buffer1));
    string1 = (char *) memset(buffer1,'A', 10);
    printf("\nBuffer contents: %s\n", string1);
    memset(buffer1+10, 'B', 10);
    printf("\nBuffer contents: %s\n", buffer1);
}
*//*
MEMSET(3)			      Linux Programmer's Manual
MEMSET(3)

NAME
       memset - fill memory with a constant byte

SYNOPSIS
       #include <string.h>

       void _memset(void _s, int c, size_t n);

DESCRIPTION
       The memset() function fills the first n bytes of the memory
       area pointed to by s with the con‐ stant byte c.

RETURN VALUE
       The memset() function returns a pointer to the memory area s.

ATTRIBUTES
       For an explanation of the terms used in this section,
       see attributes(7).

       ┌──────────┬───────────────┬─────────┐
       │Interface │ Attribute	  │ Value   │
       ├──────────┼───────────────┼─────────┤
       │memset()  │ Thread safety │ MT-Safe │
       └──────────┴───────────────┴─────────┘
CONFORMING TO
       POSIX.1-2001, POSIX.1-2008, C89, C99, SVr4, 4.3BSD.

SEE ALSO
       bstring(3), bzero(3), swab(3), wmemset(3)

COLOPHON
       This page is part of release 5.10 of the  Linux	man-pages
       project.   A  description  of  the project,  information
       about reporting bugs, and the latest version of this page,
       can be found at https:_www.kernel.org_doc_man-pages_.

GNU					      2017-03-13
MEMSET(3)
*/
