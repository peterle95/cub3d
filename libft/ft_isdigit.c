/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:59:49 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:25:13 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_isdigit(int x)
{
	if (x >= '0' && x <= '9')
		return (x);
	else
		return (0);
}

/*
int main()
{
    int x;

  printf("Enter a digit: ");
  scanf("%d", &x);

  if (ft_isdigit(x)) {
    printf("%d is a digit.\n", x);
  } else {
    printf("%d is not a digit.\n", x);
  }

  return 0;
}*/
