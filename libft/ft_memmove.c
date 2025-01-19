/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:01:23 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:28:27 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_memmove copies n bytes from memory area src to memory
	area dst. The memory areas may overlap: if the dst pointer is found
	to be between the src pointer and the index n, copying will be done
	back to front to prevent data being modified before being copied.
	Otherwise it will be done front to back	to preserve data.

	RETURN VALUE :
	A pointer to dst.
*/

#include "libft.h"
// #include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*p_dest;
	const char	*p_src;

	if (src == dst)
		return (dst);
	p_dest = (char *)dst;
	p_src = (const char *)src;
	if (p_src < p_dest && p_src + len > p_dest)
		while (len--)
			*(p_dest + len) = *(p_src + len);
	else
	{
		while (len--)
		{
			*p_dest = *p_src;
			p_src++;
			p_dest++;
		}
	}
	return (dst);
}

/* int main() {
    char src[] = "I like programming!";
    char dst[22];

    ft_memmove(dst, src, sizeof(src));

    printf("Destination string after memmove: %s\n", dst);

    return 0;
}*/
