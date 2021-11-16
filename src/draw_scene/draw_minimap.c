/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:45:06 by jludt             #+#    #+#             */
/*   Updated: 2021/11/16 17:24:34 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

extern int	worldMap[MAP_WIDTH][MAP_HEIGHT];

// static void	draw_background(t_data *data)
// {
// 	int		i;
// 	int		j;
// 	int		color;

// 	color = create_trgb(0, 128, 128, 128);
// 	i = -1;
// 	while (++i < MAP_WIDTH * 5)
// 	{
// 		j = -1;
// 		while (++j < MAP_HEIGHT * 5)
// 			my_mlx_pixel_put(data, i, j, color);
// 	}
// }

static int		get_squre_size(int n)
{
	int	res;
	int	value;

	if (SCREEN_HEIGHT < SCREEN_WIDTH)
		value = SCREEN_HEIGHT;
	else
		value = SCREEN_WIDTH;
	res = value / (n * 3);
	if (res < 2)
		res = 2;	
	return (res);
}

static void	draw_player(t_data *data, int w, int h)
{
	int	i;
	int	j;

	i = 0;
	while (++i < w)
	{
		j = 0;
		while (++j < h)
			my_mlx_pixel_put(data, ((int)data->posY * w) + i,
						((int)data->posX * h) + j, 0x00FF0000);
	}
}

static void	draw_map(t_data *data, int w, int h, int color)
{
	int		x;
	int		y;
	int		i;
	int		j;

	y = -1;
	while (++y < MAP_HEIGHT)
	{
		x = -1;
		while (++x < MAP_WIDTH)
		{
			if (x == (int)data->posX && y == (int)data->posY)
				draw_player(data, w, h);
			if (worldMap[y][x] > 0)
			{
				i = 0;
				while (++i < w)
				{
					j = 0;
					while (++j < h)
						my_mlx_pixel_put(data, (x * w) + i, (y * h) + j, color);
				}
			}
		}
	}
}

void	draw_minimap(t_data *data)
{
	int	w;
	int	h;
	int	color;

	w = get_squre_size(MAP_WIDTH);
	h = get_squre_size(MAP_HEIGHT);
	color = create_trgb(0, 255, 255, 255);
	draw_map(data, w, h, color);
}
