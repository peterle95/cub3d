/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:57:11 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 17:39:31 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

// oder of mlx_destroy funcs important
// afrer calling mlx_destroy_image() can
// then free mem allocated for struct t_img_data
int	terminator(t_data *data, int error)
{
	free_data(data);
	// mlx_loop_end(data->mlx); // is this required?
	if (data->mlx && data->img_data0->img)
	{
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

void	init_colour_fade(t_data *data)
{
	data->t = 0;
	data->r = 255;
	data->g = 0;
	data->b = 0;
}

int	set_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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
