/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:27 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/13 12:16:28 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_putendl_fd writes the given string to the given
	file descriptor followed by a new line.

	RETURN VALUE :
	None.
*/

#include "libft.h"
// #include <stdio.h>

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

/*int main()
{
  char *s = "This is just a test";
  int fd = 1;

  ft_putendl_fd(s, fd);
  return 0;
}*/