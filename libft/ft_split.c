/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:12:33 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:33:12 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION :
The function ft_split allocates and copies an array of strings by 
splitting the given string s using the given separator c.

RETURN VALUE :
An array of strings resulting from the split. NULL if the memory
allocation fails.
*/

#include "libft.h"
// #include <stdio.h>

static int	ft_count_words(const char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			words++;
		if (i > 0 && s[i] != c && s[i - 1] == c)
			words++;
		i++;
	}
	return (words);
}

static char	**ft_malloc_strs(char **strs, const char *s, char c)
{
	int	count;
	int	i;
	int	x;

	count = 0;
	i = 0;
	x = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		if ((s[i] == c && i > 0 && s[i - 1] != c)
			|| (s[i] != c && s[i + 1] == '\0'))
		{
			strs[x] = malloc(sizeof(char) * (count + 1));
			if (!strs[x])
				return (NULL);
			count = 0;
			x++;
		}
		i++;
	}
	return (strs);
}

static char	**ft_cpy_strs(char **strs, const char *s, char c)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (s[i])
	{
		if (s[i] != c)
			strs[x][y++] = s[i];
		if (s[i] != c && s[i + 1] == '\0')
			strs[x][y] = '\0';
		if (s[i] == c && i > 0 && s[i - 1] != c)
		{
			strs[x][y] = '\0';
			x++;
			y = 0;
		}
		i++;
	}
	return (strs);
}

static char	**ft_merror(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		wordcount;

	if (!s)
	{
		strs = malloc(sizeof(char) * 1);
		if (!strs)
			return (NULL);
		*strs = NULL;
		return (strs);
	}
	wordcount = ft_count_words(s, c);
	strs = malloc(sizeof(*strs) * (wordcount + 1));
	if (!strs)
		return (NULL);
	if (ft_malloc_strs(strs, s, c))
	{
		ft_cpy_strs(strs, s, c);
		strs[wordcount] = NULL;
	}
	else
		strs = ft_merror(strs);
	return (strs);
}

/*int main() {
  char str[] = "I want to split this string";
  char delimiter = ' ';

  char **split_strings = ft_split(str, delimiter);

  if (split_strings) {
    int i = 0;
    while (split_strings[i]) {
      printf("%s\n", split_strings[i]);
      i++;
    }

    free(split_strings);
  } else {
    printf("Error splitting string\n");
  }

  return 0;
}*/
