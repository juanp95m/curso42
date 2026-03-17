/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:29:56 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/08/19 18:23:06 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	long long int	i;
	long long int	k;
	int				sign;

	i = 0;
	k = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || \
nptr[i] == '\v' || nptr[i] == '\n' || \
nptr[i] == '\r' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		k = k * 10 + nptr[i] - '0';
		i++;
	}
	return (k * sign);
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	printf("%d vs %d\n", atoi("123"), ft_atoi("123"));
// 	printf("%d vs %d\n", atoi("-123"), ft_atoi("-123"));
// 	printf("%d vs %d\n", atoi("12x3"), ft_atoi("12x3"));
// 	printf("%d vs %d\n", atoi("1234567891"), ft_atoi("1234567891"));
// 	printf("%d vs %d\n", atoi("12345678912"), ft_atoi("12345678912"));
// 	printf("%d vs %d\n", atoi(" \t\v\n\r\f123"), ft_atoi(" \t\v\n\r\f123"));
// 	printf("%d vs %d\n", atoi("   123"), ft_atoi("   123"));
// 	printf("%d vs %d\n", atoi("---123"), ft_atoi("---123"));

// 	return (0);
// }

/*
ATOI(3)				      Linux Programmer's Manual
ATOI(3)

NAME
	   atoi, atol, atoll - convert a string to an integer

SYNOPSIS
	   #include <stdlib.h>

	   int atoi(const char _nptr); long atol(const char _nptr);
	   long long atoll(const char _nptr);

   Feature Test Macro Requirements for glibc (see
   feature_test_macros(7)):

	   atoll():
	   _ISOC99_SOURCE ||
		   || _ Glibc versions <= 2.19: _ _BSD_SOURCE ||
		   _SVID_SOURCE

DESCRIPTION
	   The atoi() function converts the initial portion of the
	   string pointed to by nptr to int.  The behavior is the same as

	   strtol(nptr, NULL, 10);

	   except that atoi() does not detect errors.

	   The atol() and atoll() functions behave the same as atoi(),
	   except that they convert the  ini‐ tial portion of the
	   string to their return type of long or long long.

RETURN VALUE
	   The converted value or 0 on error.

ATTRIBUTES
	   For an explanation of the terms used in this section,
	   see attributes(7).

	   ┌────────────────────────┬───────────────┬────────────────┐
	   │Interface		│
	   Attribute   │ Value		    │
	   ├────────────────────────┼───────────────┼────────────────┤
	   │atoi(), atol(), atoll() │
	   Thread safety │ MT-Safe locale │
	   └────────────────────────┴───────────────┴────────────────┘
CONFORMING TO
	   POSIX.1-2001,  POSIX.1-2008,  C99,  SVr4,  4.3BSD.  C89 and
	   POSIX.1-1996 include the functions atoi() and atol() only.

NOTES
	   POSIX.1 leaves the return value of atoi() on error
	   unspecified.   On  glibc,  musl	libc,  and uClibc, 0 is
	   returned on error.

BUGS
	   errno  is  not set on error so there is no way to distinguish
	   between 0 as an error and as the converted value.  No checks
	   for overflow or underflow are done.  Only  base-10  input
	   can  be converted.  It is recommended to instead use the
	   strtol() and strtoul() family of functions in new programs.

SEE ALSO
	   atof(3), strtod(3), strtol(3), strtoul(3)

COLOPHON
	   This page is part of release 5.10 of the  Linux	man-pages
	   project.   A  description  of  the project,  information
	   about reporting bugs, and the latest version of this page,
	   can be found at https:_www.kernel.org_doc_man-pages_.

GNU					      2020-08-13
ATOI(3)
*/
