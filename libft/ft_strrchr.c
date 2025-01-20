/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:03:23 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:50:42 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_strrchr finds the last occurrence of character c in
	string str.

	RETURN VALUE :
	A pointer to the last occurrence of c in str.
	NULL if c is not found.
*/

#include "libft.h"
// #include <stdio.h>

char	*ft_strrchr(const char *str, int c)
{
	char			*p;
	unsigned char	ch;
	size_t			offset;

	ch = c;
	offset = ft_strlen(str);
	p = (char *)str + offset;
	if (ch == '\0')
		return (p++);
	while (p >= str)
	{
		if (*p == ch)
			return (p);
		p--;
	}
	p = NULL;
	return (p);
}

/* int main() {
    char str[] = "Hello, World!";
    char ch = 'l';

    char *ptr = ft_strrchr(str, ch);

    if (ptr) {
        printf("Last occurrence of '%c' in \"%s\" is found.", ch, str, *ptr);
    } else {
        printf("Character '%c' not found in \"%s\"\n", ch, str);
    }

    return 0;
}*/
