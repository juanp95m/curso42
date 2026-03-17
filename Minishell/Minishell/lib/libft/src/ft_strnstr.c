/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:57:27 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/04 11:15:23 by miguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t			lenlittle;

	lenlittle = ft_strlen(little);
	if (lenlittle == 0)
		return ((char *)big);
	while (*big && len >= lenlittle)
	{
		if (*big == *little && ft_strncmp(big, little, lenlittle) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (0);
}
// int	main(void)
// {
// 	// const char *largestring = "Foo Bar Baz";
// 	// const char *smallstring = "Bar";
// 	// char *ptr;
// 	// ptr = ft_strnstr(largestring, smallstring, 10);
// 	// printf("%s\n", ptr);
// 	char	src[] = "hola que tal";
// 	char	src2[] = "que";
// 	printf("%s", ft_strnstr(src, src2, 10));
// 	return (0);
// }

/*
STRSTR(3bsd)					LOCAL
STRSTR(3bsd)

NAME
     strnstr — locate a substring in a string

LIBRARY
     Utility functions from BSD systems (libbsd, -lbsd)

SYNOPSIS
     #include <string.h> (See libbsd(7) for include usage.)

     char _ strnstr(const char _big, const char _little, size_t len);

DESCRIPTION
     The strnstr() function locates the first occurrence of the
     null-terminated string little in the string big, where not more
     than len characters are searched.	Characters that appear after
     a ‘\0’ character are not searched.  Since the strnstr()
     function is a FreeBSD specific API, it should only be used
     when portability is not a concern.

RETURN VALUES
     If little is an empty string, big is returned; if little occurs
     nowhere in big, NULL is re‐ turned; otherwise a pointer
     to the first character of the first occurrence of little is
     re‐ turned.

EXAMPLES
     The following sets the pointer ptr to NULL, because only the
     first 4 characters of largestring are searched:

	   const char _largestring = "Foo Bar Baz"; const char
	   _smallstring = "Bar"; char _ptr;

	   ptr = strnstr(largestring, smallstring, 4);

SEE ALSO
     strstr(3), strcasestr(3), memchr(3), memmem(3), strchr(3),
     strcspn(3), strpbrk(3), strrchr(3), strsep(3), strspn(3),
     strtok(3), wcsstr(3)

BSD					   October 11, 2001
BSD
*/
