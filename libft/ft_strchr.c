/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:03:09 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:35:17 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_strchr finds the first occurence of character c in
	string str.

	RETURN VALUE :
	A pointer to the first occurence of c in str.
	NULL if c is not found.
*/

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = c;
	if (ch == '\0')
	{
		i = ft_strlen(str);
		return ((char *)str + i++);
	}
	while (str[i])
	{
		if (str[i] == ch)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

/*int main()
{
	char str[] = "Hello, world!";
	char c = 'l';
	char *ptr = ft_strchr(str, c);

	if (ptr)
		printf("The character '%c' is found
	       	at position %ld in the string \"%s\".\n", c, ptr - str, str);
	else
		printf("The character '%c' is not found in the string \"%s\".\n", c, str);

	return 0;
}*/
