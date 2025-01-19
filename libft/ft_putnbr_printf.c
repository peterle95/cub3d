/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:03:13 by pmolzer           #+#    #+#             */
/*   Updated: 2024/01/12 21:08:21 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_printf(int num, size_t *counter)
{
	if (num == -2147483648)
	{
		ft_putnbr_printf((num / 10), counter);
		ft_putchar_printf('8', counter);
	}
	else if (num < 0)
	{
		ft_putchar_printf('-', counter);
		ft_putnbr_printf(-num, counter);
	}
	else
	{
		if (num > 9)
			ft_putnbr_printf((num / 10), counter);
		ft_putchar_printf(('0' + num % 10), counter);
	}
}
