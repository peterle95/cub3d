/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:00:44 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/13 12:00:47 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	DESCRIPTION :
	The function ft_strlen measures the length of the given string str,
	excluding the terminating \0 character.

	RETURN VALUE :
	The number of bytes in the string str.
*/

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/*#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(void)
{
    char str[] = "12345"; // 5
    char str2[] = "abcdefghi"; // 9
    printf("%i\n", ft_strlen(str));
    printf("%i", ft_strlen(str2));
    return (0);
}*/
