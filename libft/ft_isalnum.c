/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:00:05 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:21:09 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (c);
	else
		return (0);
}

/* int main() {
    char c;

    printf("Enter a character: ");
    scanf("%c", &c); 

    if (ft_isalnum(c)) {
        printf("%c is an alphanumeric character.\n", c);
    } else {
        printf("%c is not an alphanumeric character.\n", c);
    }

    return (0);
}*/
