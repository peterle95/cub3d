/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:12:46 by pmolzer           #+#    #+#             */
/*   Updated: 2023/11/22 12:26:26 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION :
The function ft_itoa converts the integer n into a string of characters.

RESULT VALUE :
The string of the converted integer.
*/

#include "libft.h"
// #include <stdio.h>

static size_t	ft_itoa_len(long num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num >= 1)
	{
		len++;
		num /= 10;
	}
	return (len);
}

static char	*ft_num_to_str(long num, char *str, size_t len)
{
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	len--;
	while (len)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	if (str[0] != '-')
		str[0] = (num % 10) + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	long	num;
	size_t	len;
	char	*str;

	num = n;
	len = ft_itoa_len(num);
	str = 0;
	str = ft_num_to_str(num, str, len);
	if (!str)
		return (NULL);
	return (str);
}

/*int main()
{
	int n;
	char *str;

	printf("Enter an integer: ");
	scanf("%d", &n);

	str = ft_itoa(n);
	if (!str)
	{
		printf("Error: Unable to convert integer to string.\n");
		return (1);
	}

	printf("The integer %d converted to a string is: %s\n", n, str);
	free(str);

	return (0);
}*/
