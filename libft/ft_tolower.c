/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:02:57 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:52:32 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}

/*int main()
{
  char c;

  printf("Enter an uppercase character: ");
  scanf("%c", &c);

  if (ft_tolower(c)) {
    printf("%c is a uppercase character.\n", c);
  } else {
    printf("%c (input is not uppercase character).\n", c);
  }

  return 0;
}*/
