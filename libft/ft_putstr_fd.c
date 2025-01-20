/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:27 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:32:13 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_putstr_fd writes the given string to the given
	file descriptor.

	RETURN VALUE :
	None.
*/

#include "libft.h"
// #include <stdio.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s != '\0')
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

/*int main()
{
	char *str = "Hello, world!";
	int fd = 1; // Standard output file descriptor

	ft_putstr_fd(str, fd);

	return 0;
}*/
