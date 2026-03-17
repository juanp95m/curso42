/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:15:09 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/04/23 13:15:17 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src || !dst)
		return (ft_strlen(src));
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		return (ft_strlen(src));
	}
	else
		return (ft_strlen(src));
}

/*
STRLCPY(3bsd)					LOCAL
STRLCPY(3bsd)

NAME
     strlcpy, strlcat — size-bounded string copying and
     concatenation

LIBRARY
     Utility functions from BSD systems (libbsd, -lbsd)

SYNOPSIS
     #include <string.h> (See libbsd(7) for include usage.)

     size_t strlcpy(char _dst, const char _src, size_t size);

     size_t strlcat(char _dst, const char _src, size_t size);

DESCRIPTION
     The strlcpy() and strlcat() functions copy and concatenate
     strings respectively.  They are de‐ signed to be safer, more
     consistent, and less error prone replacements for strncpy(3)
     and strncat(3).  Unlike those functions, strlcpy() and strlcat()
     take the full size of the buffer (not just the length) and
     guarantee to NUL-terminate the result (as long as size is
     larger than 0 or, in the case of strlcat(), as long as there
     is at least one byte free in dst).  Note that a byte for the
     NUL should be included in size.  Also note that strlcpy() and
     strlcat() only oper‐ ate on true “C” strings.  This means
     that for strlcpy() src must be NUL-terminated and for strlcat()
     both src and dst must be NUL-terminated.

     The strlcpy() function copies up to size - 1 characters from the
     NUL-terminated string src to dst, NUL-terminating the result.

     The strlcat() function appends the NUL-terminated string src
     to the end of dst.  It will append at most size - strlen(dst)
     - 1 bytes, NUL-terminating the result.

RETURN VALUES
     The strlcpy() and strlcat() functions return the total length of
     the string they tried to cre‐ ate.  For strlcpy() that means
     the length of src.  For strlcat() that means the initial length
     of dst plus the length of src.  While this may seem somewhat
     confusing, it was done to make truncation detection simple.

     Note, however, that if strlcat() traverses size characters
     without finding a NUL, the length of the string is considered to
     be size and the destination string will not be NUL-terminated
     (since there was no space for the NUL).  This keeps strlcat()
     from running off the end of a string.  In practice this should
     not happen (as it means that either size is incorrect or that
     dst is not a proper “C” string).  The check exists to
     prevent potential security problems in incorrect code.

EXAMPLES
     The following code fragment illustrates the simple case:

	   char _s, _p, buf[BUFSIZ];

	   ...

	   (void)strlcpy(buf, s, sizeof(buf)); (void)strlcat(buf,
	   p, sizeof(buf));

     To detect truncation, perhaps while building a pathname,
     something like the following might be used:

	   char _dir, _file, pname[MAXPATHLEN];

	   ...

	   if (strlcpy(pname, dir, sizeof(pname)) >= sizeof(pname))
		   goto toolong;
	   if (strlcat(pname, file, sizeof(pname)) >= sizeof(pname))
		   goto toolong;

     Since it is known how many characters were copied the first
     time, things can be sped up a bit by using a copy instead of
     an append:

	   char _dir, _file, pname[MAXPATHLEN]; size_t n;

	   ...

	   n = strlcpy(pname, dir, sizeof(pname)); if (n >=
	   sizeof(pname))
		   goto toolong;
	   if (strlcpy(pname + n, file, sizeof(pname) - n) >=
	   sizeof(pname) - n)
		   goto toolong;

     However, one may question the validity of such optimizations,
     as they defeat the whole purpose of strlcpy() and strlcat().
     As a matter of fact, the first version of this manual page
     got it wrong.

SEE ALSO
     snprintf(3), strncat(3), strncpy(3)

HISTORY
     The strlcpy() and strlcat() functions first appeared in OpenBSD
     2.4, and made their appearance in FreeBSD 3.3.

BSD					     May 31, 2007
BSD
*/
