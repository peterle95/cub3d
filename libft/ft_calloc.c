/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:05:01 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:20:01 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_calloc allocates memory for an array of count elements
	of size bytes each and sets the memory to zero.

	RETURN VALUE :
	The pointer to the allocated memory. NULL if the memory allocation fails.
*/

#include "libft.h"

// #include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*x;

	x = malloc(count * size);
	if (!x)
		return (NULL);
	ft_bzero(x, count * size);
	return (x);
}

/*int main(void)
{
	void	*ptr;

	ptr = ft_calloc(10, sizeof(int));
	if (!ptr)
	{
		printf("Memory allocation failed.\n");
		return (-1);
	}
	free(ptr);
	printf("Memory freed successfully.\n");
	return (0);
}*/
