/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:40:09 by jludt             #+#    #+#             */
/*   Updated: 2021/11/13 12:01:20 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

extern int	worldMap[MAP_WIDTH][MAP_HEIGHT];

void	draw_floor(t_data *data)
{
	int		i;
	int		j;
	int		color;

	color = create_trgb(0, 139, 90, 43);
	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = SCREEN_HEIGHT / 2 - 1;
		while (++j < SCREEN_HEIGHT)
			my_mlx_pixel_put(data, i, j, color);
	}
}

void	draw_ceiling(t_data *data)
{
	int		i;
	int		j;
	int		color;

	color = create_trgb(0, 152, 245, 255);
	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = -1;
		while (++j < SCREEN_HEIGHT / 2)
			my_mlx_pixel_put(data, i, j, color);
	}
}
