/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:15:31 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:29:51 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_putchar_fd writes the given character to the given
	file descriptor.

	RETURN VALUE :
	None.
*/

#include "libft.h"
// #include <stdio.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*int main()
{
  char c = 'A';
  int fd = 1; // stdout

  ft_putchar_fd(c, fd);

  return 0;
}*/
