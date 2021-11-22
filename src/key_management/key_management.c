/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:48:00 by jludt             #+#    #+#             */
/*   Updated: 2021/11/22 11:12:28 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	move_left(t_data *data)
{
	if (data->world_map[(int)(data->pos_x \
		- data->plane_x * data->move_speed)][(int)data->pos_y] == 0)
		data->pos_x -= data->plane_x * data->move_speed;
	if (data->world_map[(int)data->pos_x][(int)(data->pos_y \
		- data->plane_y * data->move_speed)] == 0)
		data->pos_y -= data->plane_y * data->move_speed;
}

static void	move_right(t_data *data)
{
	if (data->world_map[(int)(data->pos_x \
		+ data->plane_x * data->move_speed)][(int)data->pos_y] == 0)
		data->pos_x += data->plane_x * data->move_speed;
	if (data->world_map[(int)data->pos_x][(int)(data->pos_y \
		+ data->plane_y * data->move_speed)] == 0)
		data->pos_y += data->plane_y * data->move_speed;
}

int	key_update(t_data *data)
{	
	if (data->key.w)
		move_forward(data);
	if (data->key.s)
		move_backward(data);
	if (data->key.a)
		move_left(data);
	if (data->key.d)
		move_right(data);
	if (data->key.la)
		rotate_left(data);
	if (data->key.ra)
		rotate_right(data);
	if (data->key.esc)
		exit(0);
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)y;
	if (data->key.pause > 0)
	{
		mlx_mouse_move(data->mlx_win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		if (x > SCREEN_WIDTH / 2)
			rotate_right(data);
		else if (x < SCREEN_WIDTH / 2)
			rotate_left(data);
	}
	return (0);
}

int	ft_close(t_data *data)
{
	(void)	*data;
	exit(0);
}
