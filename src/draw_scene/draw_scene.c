/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:50:37 by jludt             #+#    #+#             */
/*   Updated: 2021/11/14 16:43:48 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

extern int	worldMap[MAP_WIDTH][MAP_HEIGHT];

static void	raycaster(t_data *data)
{
	t_rc	rc;

	rc.x = -1;
	while (++rc.x < SCREEN_WIDTH)
	{
		calc_initial_state(data, &rc);
		calc_step_and_side_dist(data, &rc);
		perform_dda(&rc);
		calc_texturing(data, &rc);
		draw_texture(data, &rc);
	}
}

int	draw_scene(t_data *data)
{
	draw_ceiling(data);
	draw_floor(data);
	raycaster(data);
	draw_minimap(data);
	return (0);
}