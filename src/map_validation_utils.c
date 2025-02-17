/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:10:58 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/17 09:12:19 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Helper function to free a NULL-terminated array of strings.
void	free_split(char **tokens)
{
	int		k;

	k = 0;
	while (tokens[k])
	{
		free(tokens[k]);
		k++;
	}
	free(tokens);
}

int	validate_number_string(const char *str)
{
	int		j;

	if (str[0] == '\0')
		return (1);
	j = 0;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			return (1);
		j++;
	}
	return (0);
}

int	validate_rgb_value(const char *value)
{
	unsigned int	num;

	if (validate_number_string(value))
		return (1);
	num = ft_atoi(value);
	if (num > 255)
		return (1);
	return (0);
}

int	process_rgb_values(char **values, unsigned int rgb[3])
{
	int		i;

	i = 0;
	while (values[i])
		i++;
	if (i != 3)
		return (1);
	i = 0;
	while (i < 3)
	{
		if (validate_rgb_value(values[i]))
			return (1);
		rgb[i] = ft_atoi(values[i]);
		i++;
	}
	return (0);
}
