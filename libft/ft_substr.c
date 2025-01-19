/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:11:51 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/13 12:11:52 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_substr extracts a substring from the given string by
	allocating sufficient memory for the new string starting at index start
	and ending at len characters.

	RETURN VALUE :
	A pointer to the new string.
	NULL if the memory allocation fails.
*/

#include "libft.h"
// #include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p_sub;
	char	*p_start_sub;
	size_t	sublen;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	p_start_sub = (char *)s + start;
	if (ft_strlen(p_start_sub) < len)
		sublen = ft_strlen(p_start_sub) + 1;
	else
		sublen = len + 1;
	p_sub = malloc(sublen * sizeof(char));
	if (!p_sub)
		return (NULL);
	ft_strlcpy(p_sub, p_start_sub, sublen);
	return (p_sub);
}

/*int main(void)
{
	char *original = "Hello, world!";
	unsigned int start = 5;
	size_t len = 5;

	char *substring = ft_substr(original, start, len);
	if (!substring)
	{
		fprintf(stderr, "Error: Failed to allocate memory for substring.\n");
		return 1;
	}

	printf("Original string: %s\n", original);
	printf("Substring: %s\n", substring);

	free(substring);

	return 0;
}*/