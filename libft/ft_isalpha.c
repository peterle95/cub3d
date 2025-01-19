/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:59:35 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:21:39 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DEFINITION:
checks  for  an  alphabetic  character; in the standard "C" locale, 
it is equivalent to (isupper(c) || islower(c)).  In some locales, 
there may be  additional  characters  for
which isalpha() is true—letters which are neither uppercase nor lowercase.
*/

#include "libft.h"
// #include <stdio.h>

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')); 
}

/*
int main()
{
  char c;

  printf("Enter a character: ");
  scanf("%c", &c);

  if (ft_isalpha(c)) {
    printf("%c is an alphabetic character.\n", c);
  } else {
    printf("%c is not an alphabetic character.\n", c);
  }

  return 0;
}*/
