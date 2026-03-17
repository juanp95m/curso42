/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:53:55 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/04/22 12:55:12 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*copy;
	unsigned char	*dest_char;

	i = 0;
	copy = (unsigned char *)src;
	dest_char = (unsigned char *)dest;
	if (src == NULL && dest == NULL)
		return (dest);
	while (i < n)
	{
		dest_char[i] = copy[i];
		i++;
	}
	dest = (void *) dest_char;
	return (dest);
}

/*
#include "libft.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    printf("\n################### ft_memcpy ###################\n");
    char source[ ] = "Source should go to here";
    char target[ ] = "This is the target string";
    printf( "Source is: %s\n", source);
	printf( "Before memcpy, target is: %s\n", target);
    ft_memcpy(target+15, source, 6);
    printf( "After memcpy, target becomes: %s\n", target);
}
*/

/*
MEMCPY(3)			      Linux Programmer's Manual
MEMCPY(3)

NAME
       memcpy - copy memory area

SYNOPSIS
       #include <string.h>

       void _memcpy(void _dest, const void _src, size_t n);

DESCRIPTION
       The memcpy() function copies n bytes from memory area src
       to memory area dest.  The memory ar‐ eas must not overlap.
       Use memmove(3) if the memory areas do overlap.

RETURN VALUE
       The memcpy() function returns a pointer to dest.

ATTRIBUTES
       For an explanation of the terms used in this section,
       see attributes(7).

       ┌──────────┬───────────────┬─────────┐
       │Interface │ Attribute	  │ Value   │
       ├──────────┼───────────────┼─────────┤
       │memcpy()  │ Thread safety │ MT-Safe │
       └──────────┴───────────────┴─────────┘
CONFORMING TO
       POSIX.1-2001, POSIX.1-2008, C89, C99, SVr4, 4.3BSD.

NOTES
       Failure to observe the requirement that the memory areas
       do not overlap has been the source of significant  bugs.
       (POSIX and the C standards are explicit that employing
       memcpy() with over‐ lapping areas produces undefined
       behavior.)  Most notably, in glibc 2.13 a  performance
       opti‐ mization of memcpy() on some platforms (including
       x86-64) included changing the order in which bytes were
       copied from src to dest.

       This change revealed breakages in a number of applications
       that performed copying  with  over‐ lapping  areas.
       Under  the previous implementation, the order in which the
       bytes were copied had fortuitously hidden the bug, which was
       revealed when the copying order was  reversed.	In glibc
       2.14,  a  versioned  symbol  was added so that old binaries
       (i.e., those linked against glibc versions earlier than 2.14)
       employed a memcpy() implementation that safely  handles	the
       overlapping  buffers case (by providing an "older" memcpy()
       implementation that was aliased to memmove(3)).

SEE ALSO
       bcopy(3), bstring(3), memccpy(3), memmove(3), mempcpy(3),
       strcpy(3), strncpy(3), wmemcpy(3)

COLOPHON
       This page is part of release 5.10 of the  Linux	man-pages
       project.   A  description  of  the project,  information
       about reporting bugs, and the latest version of this page,
       can be found at https:_www.kernel.org_doc_man-pages_.

					      2017-09-15
					      MEMCPY(3)
*/
