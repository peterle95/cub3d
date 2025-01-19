/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:00:21 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/13 12:00:22 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*
int main()
{
  char c;

  printf("Enter a character: ");
  scanf("%c", &c);

  if (ft_isascii(c)) {
    printf("%c is part of ASCII.\n", c);
  } else {
    printf("%c is not part of ASCII.\n", c);
  }

  return 0;
}
*/