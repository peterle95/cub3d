/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:01:36 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:47:59 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_strlcpy copies up to size - 1 characters from the given
	string src to the given string dst, nul-terminating the result.

	Note : space for the terminating \0 character must be included in dstsize.

	RETURN VALUE :
	The total length of the string that it tried to create : the length of
	src, with the goal to facilitate truncaction detection.
*/

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

/*int main(void)
{
	char dst[10];
	const char src[] = "Wawaweewa!";
	size_t dstsize = sizeof(dst);

	size_t srclen = ft_strlcpy(dst, src, dstsize);

	printf("dst: %s\n", dst);
	printf("src: %s\n", src);
	printf("srclen: %zu\n", srclen);

	return 0;
}*/
