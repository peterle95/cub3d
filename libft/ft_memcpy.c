/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42 Header_ft_memcpy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:54:21 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 11:54:29 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_memcpy copies n bytes from memory area src to memory
	area dst.
	Does not account for memory overlaps. Use ft_memmove if the memory areas
	overlap or might overlap.

	RETURN VALUE :
	A pointer to dst. NULL if src and dst are both NULL.
*/

#include "libft.h"
// #include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*p_dest;
	const char	*p_src;

	if (!dst && !src)
		return (0);
	if (n == 0 || (dst == src))
		return (dst);
	p_dest = (char *)dst;
	p_src = (const char *)src;
	while (n != 0)
	{
		if (*p_dest != *p_src)
			*p_dest = *p_src;
		p_dest++;
		p_src++;
		n--;
	}
	return (dst);
}

/*int main() {
    char src[50] = "Hello, World!";
    char dest[50];

    ft_memcpy(dest, src, 50);

    printf("Copied string: %s\n", dest);

    return 0;
}*/
