/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:00:34 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:26:00 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}

/*
int main()
{
    char c;

    printf("Enter printable character: ");
    scanf("%c", &c);

     if (ft_isprint(c)) {
    printf("%d is printable.\n", c);
  } else {
    printf("%d is not printable.\n", c);
  }

  return 0;

}*/
