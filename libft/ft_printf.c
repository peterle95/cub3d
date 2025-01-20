/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:29:30 by pmolzer           #+#    #+#             */
/*   Updated: 2024/01/12 21:08:21 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_format(va_list va, char *str, size_t *counter)
{
	if (*str == 'c')
		ft_putchar_printf(va_arg(va, int), counter);
	else if (*str == 's')
		ft_putstr_printf(va_arg(va, char *), counter);
	else if (*str == 'p')
		ft_putptr_printf(va_arg(va, void *), counter);
	else if (*str == 'i' || *str == 'd')
		ft_putnbr_printf(va_arg(va, int), counter);
	else if (*str == 'u')
		ft_putuint_printf(va_arg(va, unsigned int), counter);
	else if (*str == 'x' || *str == 'X')
	{
		if (*str == 'x')
			ft_puthex_printf(va_arg(va, unsigned int), counter, HEX_LOW_BASE);
		else
			ft_puthex_printf(va_arg(va, unsigned int), counter, HEX_UPP_BASE);
	}
	else if (*str == '%')
		ft_putchar_printf(*str, counter);
}

int	ft_printf(char const *str, ...)
{
	va_list		va;
	size_t		counter;

	if (!str)
		return (0);
	counter = 0;
	va_start(va, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_format(va, (char *)str, &counter);
		}
		else
			ft_putchar_printf(*str, &counter);
		str++;
	}
	va_end(va);
	return (counter);
}

/* int main()
{
    ft_printf("%c - Expected: A\n", 'A');
    ft_printf("%s - Expected: Hello, world!\n", "Hello, world!");
    ft_printf("%p - Expected: (pointer address)\n", "This is a pointer");
    ft_printf("%d - Expected: 15\n", 15);
    ft_printf("%x - Expected: f\n", 15);
    ft_printf("%X - Expected: F\n", 15);
    ft_printf("%u - Expected: 255\n", 255);
    ft_printf("%% - Expected: %%\n");

    return 0;
} */