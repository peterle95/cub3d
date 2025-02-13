/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:00:43 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 17:01:28 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_string_array(char **array, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		if (array[i] != NULL)
			printf("%s\n", array[i]);
		else
			printf("(null)\n");
		i++;
	}
}
