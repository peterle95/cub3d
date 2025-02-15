/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:36 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	member_of_set(char c, char *set)
{
	if (!set)
		return (false);
	while (*set)
	{
		if (*set == c)
			return (true);
		set++;
	}
	return (false);
}

int	array_len(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}
