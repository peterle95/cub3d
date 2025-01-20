/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:03:20 by pmolzer           #+#    #+#             */
/*   Updated: 2024/01/12 21:08:21 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putptr_printf(void *ptr, size_t *counter)
{
	char			*str;
	unsigned long	ptr_address;

	if (!ptr)
	{
		ft_putstr_printf("(nil)", counter);
		return ;
	}
	ptr_address = (unsigned long)ptr;
	ft_putstr_printf("0x", counter);
	str = ft_aux_printf(ptr_address, HEX_LOW_BASE);
	ft_putstr_printf(str, counter);
	free(str);
	str = NULL;
}
