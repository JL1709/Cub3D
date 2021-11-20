/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:50:37 by jludt             #+#    #+#             */
/*   Updated: 2021/11/20 18:59:22 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	dda_norm_helper(t_data *data, t_rc *rc)
{
	rc->side_dist_x += rc->delta_dist_x;
	rc->map_x += rc->step_x;
	rc->side = 0;
	if (data->worldMap[rc->map_x][rc->map_y] > 0)
	{
		rc->hit = 1;
		if (rc->map_x > data->posX)
			rc->tex_num = 4;
		else
			rc->tex_num = 7;
	}
}

static void	raycaster(t_data *data)
{
	t_rc	rc;

	rc.x = -1;
	while (++rc.x < SCREEN_WIDTH)
	{
		calc_initial_state(data, &rc);
		calc_step_and_side_dist(data, &rc);
		perform_dda(data, &rc);
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
