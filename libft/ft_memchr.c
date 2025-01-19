/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:03:52 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:27:08 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION :
The function ft_memchr searches n bytes of the memory area pointed to
by s for the first occurence of c. Both c and the bytes of s are
interpreted as unsigned char.

RETURN VALUE:
A pointer to the matching byte. NULL if the character does not occur
in the given memory area.
*/

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		ch;
	const unsigned char	*str;

	ch = c;
	str = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == ch)
			return ((void *)s + i);
		i++;
	}
	return (0);
}

/*int main() {
  const char *str = "This is fun!";
  char c = 'u';
  size_t n = ft_strlen(str);

  void *result = ft_memchr(str, c, n);

  if (result) {
    // Character found, calculate its position within the original string
    int foundPosition = 0;
    while (str[foundPosition] != c) {
      foundPosition++;
    }
    printf("Character '%c' found at position %d\n", c, foundPosition);
  } else {
    // Character not found, handle the error
    printf("Character '%c' not found in the string\n", c);
  }

  return 0;
}*/ 
