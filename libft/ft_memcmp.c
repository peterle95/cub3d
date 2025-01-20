/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:04:04 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:27:54 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_memcmp compares the first n bytes of the memory areas
	s1 and s2. The bytes are interpreted as unsigned char.

	RETURN VALUE :
	An integer less than, equal to, or greater than zero if the first
	n bytes of s1 is found to be less than, equal to, or greater than the 
	first n bytes of s2. Zero if n is equal to zero.
*/

#include "libft.h"
// #include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*str1;
	const char	*str2;
	size_t		i;

	if (n == 0)
		return (0);
	str1 = (const char *)s1;
	str2 = (const char *)s2;
	i = 0;
	while ((i < n - 1) && str1[i] == str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

/*int main() {
  const char s1[] = "Nice!";
  const char s2[] = "Nice!";
  size_t n = strelen(s1);

  int result = ft_memcmp(s1, s2, n);

  if (result == 0) {
    printf("The strings are equal.\n");
  } else if (result < 0) {
    printf("The first string is less than the second string.\n");
  } else {
    printf("The first string is greater than the second string.\n");
  }

  return 0;
}*/
