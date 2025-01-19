/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:01:47 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:46:48 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION :
The function ft_strlcat appends the given string src to the end of 
dst. It will append at most dstsize - ft_strlen(dst) - 1 and 
nul-terminate the result.

Note : space for the terminating \0 character must be included in dstsize.

RETURN VALUE :
The total length of the string that it tried to create : the initial
length of dst + the length of src, with the goal to facilitate
truncaction detection.
*/

#include "libft.h"

// #include <string.h>
// #include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	d_size;
	size_t	s_size;

	d_size = ft_strlen(dst);
	s_size = ft_strlen(src);
	if (dstsize <= d_size)
		return (dstsize + s_size);
	i = d_size;
	j = 0;
	while ((i + j) < (dstsize - 1) && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (d_size + s_size);
}

/*int main()
{
	char dst[27] = "This string +";
	const char src[] = " this string.";
	size_t dstsize = sizeof(dst);

	size_t len = ft_strlcat(dst, src, dstsize);
	printf("Destination string: %s\n", dst);
	printf("Length: %zu\n", len);

	return 0;
}*/
