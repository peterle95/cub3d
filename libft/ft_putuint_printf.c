/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_printf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:03:36 by pmolzer           #+#    #+#             */
/*   Updated: 2024/01/12 21:08:21 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putuint_printf(unsigned int num, size_t *counter)
{
	char	*str;

	str = ft_aux_printf(num, "0123456789");
	ft_putstr_printf(str, counter);
	free(str);
	str = NULL;
}
