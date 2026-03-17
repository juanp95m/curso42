/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:11:14 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/01 18:11:17 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char s[] = "String to be copied";
// 	char *dst;

// 	dst = ft_strdup(s);
// 	printf("%s - %p\n", s, &s);
// 	printf("%s - %p\n", dst, &dst);

// }

/*
STRDUP(3)			      Linux Programmer's Manual
STRDUP(3)

NAME
       strdup, strndup, strdupa, strndupa - duplicate a string

SYNOPSIS
       #include <string.h>

       char _strdup(const char _s);

       char _strndup(const char _s, size_t n); char _strdupa(const
       char _s); char _strndupa(const char _s, size_t n);

   Feature Test Macro Requirements for glibc (see
   feature_test_macros(7)):

       strdup():
	   _XOPEN_SOURCE >= 500
	       || _ Since glibc 2.12: _ _POSIX_C_SOURCE >= 200809L
	       || _ Glibc versions <= 2.19: _ _BSD_SOURCE ||
	       _SVID_SOURCE
       strndup():
	   Since glibc 2.10:
	       _POSIX_C_SOURCE >= 200809L
	   Before glibc 2.10:
	       _GNU_SOURCE
       strdupa(), strndupa(): _GNU_SOURCE

DESCRIPTION
       The  strdup() function returns a pointer to a new string which
       is a duplicate of the string s.	Memory for the new string
       is obtained with malloc(3), and can be freed with free(3).

       The strndup() function is similar, but copies at most
       n bytes.  If s is longer than n, only  n bytes are copied,
       and a terminating null byte ('\0') is added.

       strdupa()  and  strndupa()  are	similar,  but use alloca(3)
       to allocate the buffer.	They are available only when using
       the GNU GCC suite, and suffer from the same limitations
       described in alloca(3).

RETURN VALUE
       On success, the strdup() function returns a pointer to the
       duplicated string.  It returns NULL if insufficient memory was
       available, with errno set to indicate the cause of the error.

ERRORS
       ENOMEM Insufficient memory available to allocate duplicate
       string.

ATTRIBUTES
       For an explanation of the terms used in this section,
       see attributes(7).

       ┌────────────────────────────────┬───────────────┬─────────┐
       │Interface			│
       Attribute   │ Value	     │
       ├────────────────────────────────┼───────────────┼─────────┤
       │strdup(), strndup(), strdupa(), │ Thread
       safety │ MT-Safe │ │strndupa()
       │	       │	 │
       └────────────────────────────────┴───────────────┴─────────┘

CONFORMING TO
       strdup()  conforms  to  SVr4,  4.3BSD,  POSIX.1-2001.
       strndup()  conforms  to	POSIX.1-2008.  strdupa() and
       strndupa() are GNU extensions.

SEE ALSO
       alloca(3), calloc(3), free(3), malloc(3), realloc(3),
       string(3), wcsdup(3)

COLOPHON
       This  page  is  part  of  release  5.10	of the Linux
       man-pages project.  A description of the project, information
       about reporting bugs, and the latest version of this page,
       can  be	found at https:_www.kernel.org_doc_man-pages_.

GNU					      2019-03-06
STRDUP(3)
*/
