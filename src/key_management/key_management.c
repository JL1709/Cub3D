/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:48:00 by jludt             #+#    #+#             */
/*   Updated: 2021/11/20 18:39:34 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	move_left(t_data *data)
{
	if (data->worldMap[(int)(data->posX \
		- data->planeX * data->moveSpeed)][(int)data->posY] == 0)
		data->posX -= data->planeX * data->moveSpeed;
	if (data->worldMap[(int)data->posX][(int)(data->posY \
		- data->planeY * data->moveSpeed)] == 0)
		data->posY -= data->planeY * data->moveSpeed;
}

static void	move_right(t_data *data)
{
	if (data->worldMap[(int)(data->posX \
		+ data->planeX * data->moveSpeed)][(int)data->posY] == 0)
		data->posX += data->planeX * data->moveSpeed;
	if (data->worldMap[(int)data->posX][(int)(data->posY \
		+ data->planeY * data->moveSpeed)] == 0)
		data->posY += data->planeY * data->moveSpeed;
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
	static int	old_x;

	(void) y;
	if (x > old_x)
		rotate_right(data);
	else if (x < old_x)
		rotate_left(data);
	old_x = x;
	return (0);
}

int	ft_close(t_data *data)
{
	(void)	*data;
	exit(0);
}
