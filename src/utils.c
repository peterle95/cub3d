/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:57:11 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < N_TEXTURES)
	{
		if (data->textures.img[i].ptr)
			mlx_destroy_image(data->mlx, data->textures.img[i].ptr);
		i++;
	}
	return (0);
}

int	terminator(t_data *data, int error)
{
	free_data(data);
	if (data->mlx)
	{
		if (data->img_data0 && data->img_data0->img)
			mlx_destroy_image(data->mlx, data->img_data0->img);
		free(data->img_data0);
		data->img_data0 = NULL;
	}
	destroy_textures(data);
	if (data->mlx && data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	printf("Hasta la vista, baby!\n");
	exit(error);
}

void	free_2d_char_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}
