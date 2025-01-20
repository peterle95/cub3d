/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:05:13 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:39:16 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_strdup duplicates the given string s1 by allocating 
	memory and performing a copy of the given string.

	RETURN VALUE :
	A pointer to the new string. NULL if the memory allocation fails.
*/

#include "libft.h"
// #include <stdio.h>

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1) + 1;
	s2 = malloc(len * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, len);
	return (s2);
}

/*int main() {
  char *original = "Hello, world!";
  char *duplicate = ft_strdup(original);

  printf("Original string: %s\n", original);
  printf("Duplicate string: %s\n", duplicate);

  free(duplicate); // Free the allocated memory for the duplicate string

  return 0;
}*/
