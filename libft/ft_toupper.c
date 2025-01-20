/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:02:48 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/23 12:26:36 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

/*int main()
{
  char c;

  printf("Enter a lowercase character: ");
  scanf("%c", &c);

  if (ft_toupper(c)) {
    printf("%c is a lowercase character.\n", c);
  } else {
    printf("%c (input is not lowercase character).\n", c);
  }

  return 0;
}*/
