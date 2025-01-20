/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:04:16 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:49:29 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION :
The function ft_strnstr searches the first n bytes of the given string
s1 for the first occurence of the full string s2.
Characters that appear after \0 are not searched.

RETURN VALUE :
A pointer to the first character of the first occurrence of s2.
A pointer to s1 if s2 is empty.
NULL if s2 occurs nowhere in s1.
*/

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	s2len;
	size_t	i;
	size_t	j;

	s2len = ft_strlen(s2);
	if (s1 == s2 || s2len == 0)
		return ((char *)s1);
	i = 0;
	while (i < n && s1[i] != '\0')
	{
		j = 0;
		while (s1[i + j] != '\0' && s2[j] != '\0'
			&& (i + j) < n && s1[i + j] == s2[j])
		{
			j++;
			if ((j == n && j == s2len) || j == s2len)
				return ((char *)(s1 + i));
		}
		i++;
	}
	return (0);
}

/* int main()
{
	char haystack[] = "Great Success, I Like!";
	char needle[] = "Success";
	size_t haystack_size = ft_strlen(haystack);
	size_t needle_size = ft_strlen(needle);

	char *result = ft_strnstr(haystack, needle, haystack_size);
	if (result)
	{
		printf("The needle \"%s\" was found in the
	       	haystack \"%s\" at index %ld\n", needle, haystack, result - haystack);
	}
	else
	{
		printf("The needle \"%s\" was not found in the 
		haystack \"%s\"\n", needle, haystack);
	}

	return 0;
}*/
