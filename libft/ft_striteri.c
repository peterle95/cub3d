/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:15:11 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:42:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_striteri applies the given function f to each
	character in the given string s.

	RETURN VALUE :
	None.
*/

#include "libft.h"
// #include <stdio.h>
// #include <stdlib.h>

/*void to_upper(unsigned int i, char* c)
{
    *c = toupper(*c);
}*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*int main(int argc, char** argv)
{
	char str[100];

	printf("Enter a string: ");
	scanf("%s", str);

	ft_striteri(str, toupper);

	return 0;
}*/
