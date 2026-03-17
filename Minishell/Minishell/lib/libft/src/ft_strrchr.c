/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:40:41 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/07/14 13:49:48 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cc;
	char	*str;

	i = ft_strlen(s);
	cc = (char )c;
	str = (char *)s;
	while (i != 0)
	{
		if (str[i] == cc)
			return (&str[i]);
		i--;
	}
	if (str[i] == cc)
		return (&str[i]);
	else
		return (NULL);
}

// #include <stdio.h>
// int	main(void)
// {
// 	//char s[] = "Bonjour";
// 	//char s[] = "\0";
// 	char s[] = "";
// 	printf("Original: %s\n", s);
// 	printf("%s\n", ft_strrchr(s, 'o'));
// 	return (0);
// }

/*
STRCHR(3)			      Linux Programmer's Manual
STRCHR(3)

NAME
       strchr, strrchr, strchrnul - locate character in string

SYNOPSIS
       #include <string.h>

       char _strchr(const char _s, int c);

       char _strrchr(const char _s, int c);

       #define _GNU_SOURCE	   _ See feature_test_macros(7)
       _ #include <string.h>

       char _strchrnul(const char _s, int c);

DESCRIPTION
       The  strchr()  function	returns  a  pointer to the first
       occurrence of the character c in the string s.

       The strrchr() function returns a pointer to the last
       occurrence of  the  character  c  in  the string s.

       The  strchrnul() function is like strchr() except that if
       c is not found in s, then it returns a pointer to the null
       byte at the end of s, rather than NULL.

       Here "character" means "byte"; these functions do not work
       with wide or multibyte characters.

RETURN VALUE
       The strchr() and strrchr() functions return a pointer to the
       matched character or NULL if  the character  is	not found.
       The terminating null byte is considered part of the string,
       so that if c is specified as '\0', these functions return
       a pointer to the terminator.

       The strchrnul() function returns a pointer to the matched
       character, or a pointer to the  null byte at the end of s
       (i.e., s+strlen(s)) if the character is not found.

VERSIONS
       strchrnul() first appeared in glibc in version 2.1.1.

ATTRIBUTES
       For an explanation of the terms used in this section,
       see attributes(7).

       ┌─────────────────────────────────┬───────────────┬─────────┐
       │Interface			 │
       Attribute   │ Value   │
       ├─────────────────────────────────┼───────────────┼─────────┤
       │strchr(), strrchr(), strchrnul()
       │ Thread safety │ MT-Safe │
       └─────────────────────────────────┴───────────────┴─────────┘
CONFORMING TO
       strchr(), strrchr(): POSIX.1-2001, POSIX.1-2008, C89, C99,
       SVr4, 4.3BSD.

       strchrnul() is a GNU extension.

SEE ALSO
       index(3),  memchr(3),  rindex(3),  string(3),  strlen(3),
       strpbrk(3),  strsep(3),	strspn(3), strstr(3), strtok(3),
       wcschr(3), wcsrchr(3)

COLOPHON
       This page is part of release 5.10 of the  Linux	man-pages
       project.   A  description  of  the project,  information
       about reporting bugs, and the latest version of this page,
       can be found at https:_www.kernel.org_doc_man-pages_.

GNU					      2019-03-06
STRCHR(3)
*/
