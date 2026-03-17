/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:16:45 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/04/22 17:21:09 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_c;
	unsigned char	*src_c;

	i = 0;
	src_c = (unsigned char *)src;
	dest_c = (unsigned char *)dest;
	if (dest_c == NULL && src_c == NULL)
	{
		return (NULL);
	}
	if (src_c < dest_c)
	{
		while (i < n)
		{
			n--;
			dest_c[n] = src_c[n];
		}
	}
	else
	{
		dest_c = ft_memcpy(dest_c, src_c, n);
	}
	dest = (void *)dest_c;
	return (dest);
}

/*
#include "libft.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    printf("\n################### ft_memmove ###################\n");
    char s1[ ] = "ABCDEFGHIJKLMOP";
	char s2[ ] = "abcdefghijklmnop";
    int c = 5;
	int where = 0;

    printf("---ft:\n");
    printf( "Target before move: %s\n", s1);
    ft_memmove(s1+where, s2, c);
    printf( "Target after move (%d) : %s\n",c, s1 );

    printf("---original:\n");
    printf( "Target before move: %s\n", s1);
    memmove(s1+where, s2, c);
    printf( "Target after move (%d) : %s\n",c, s1 );
}
*/

/*
MEMMOVE(3)			      Linux Programmer's Manual
MEMMOVE(3)

NAME
       memmove - copy memory area

SYNOPSIS
       #include <string.h>

       void _memmove(void _dest, const void _src, size_t n);

DESCRIPTION
       The  memmove()  function  copies n bytes from memory area src
       to memory area dest.  The memory areas may overlap: copying
       takes place as though the bytes in src are first copied into
       a tem‐ porary	array that does not overlap src or dest,
       and the bytes are then copied from the tempo‐ rary array
       to dest.

RETURN VALUE
       The memmove() function returns a pointer to dest.

ATTRIBUTES
       For an explanation of the terms used in this section,
       see attributes(7).

       ┌──────────┬───────────────┬─────────┐
       │Interface │ Attribute	  │ Value   │
       ├──────────┼───────────────┼─────────┤
       │memmove() │ Thread safety │ MT-Safe │
       └──────────┴───────────────┴─────────┘
CONFORMING TO
       POSIX.1-2001, POSIX.1-2008, C89, C99, SVr4, 4.3BSD.

SEE ALSO
       bcopy(3), bstring(3), memccpy(3), memcpy(3), strcpy(3),
       strncpy(3), wmemmove(3)

COLOPHON
       This page is part of release 5.10 of the  Linux	man-pages
       project.   A  description  of  the project,  information
       about reporting bugs, and the latest version of this page,
       can be found at https:_www.kernel.org_doc_man-pages_.

GNU					      2017-03-13
MEMMOVE(3)
*/