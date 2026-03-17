/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:20:40 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/04/21 19:00:13 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
/*
STRLEN(3)			      Linux Programmer's Manual
STRLEN(3)

NAME
       strlen - calculate the length of a string

SYNOPSIS
       #include <string.h>

       size_t strlen(const char _s);

DESCRIPTION
       The  strlen() function calculates the length of the string
       pointed to by s, excluding the ter‐ minating null byte
       ('\0').

RETURN VALUE
       The strlen() function returns the number of bytes in the
       string pointed to by s.

ATTRIBUTES
       For an explanation of the terms used in this section,
       see attributes(7).

       ┌──────────┬───────────────┬─────────┐
       │Interface │ Attribute	  │ Value   │
       ├──────────┼───────────────┼─────────┤
       │strlen()  │ Thread safety │ MT-Safe │
       └──────────┴───────────────┴─────────┘
CONFORMING TO
       POSIX.1-2001, POSIX.1-2008, C89, C99, C11, SVr4, 4.3BSD.

SEE ALSO
       string(3), strnlen(3), wcslen(3), wcsnlen(3)

COLOPHON
       This page is part of release 5.10 of the  Linux	man-pages
       project.   A  description  of  the project,  information
       about reporting bugs, and the latest version of this page,
       can be found at https:_www.kernel.org_doc_man-pages_.

GNU					      2019-03-06
STRLEN(3)
*/
