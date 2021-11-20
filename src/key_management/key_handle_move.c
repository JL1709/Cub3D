/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 18:37:00 by julian            #+#    #+#             */
/*   Updated: 2021/11/20 18:39:25 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	rotate_left(t_data *data)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = data->dirX;
	data->dirX = data->dirX * cos(data->rotSpeed) \
		- data->dirY * sin(data->rotSpeed);
	data->dirY = oldDirX * sin(data->rotSpeed) \
		+ data->dirY * cos(data->rotSpeed);
	oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(data->rotSpeed) \
		- data->planeY * sin(data->rotSpeed);
	data->planeY = oldPlaneX * sin(data->rotSpeed) \
		+ data->planeY * cos(data->rotSpeed);
}

void	rotate_right(t_data *data)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = data->dirX;
	data->dirX = data->dirX * cos(-data->rotSpeed) \
		- data->dirY * sin(-data->rotSpeed);
	data->dirY = oldDirX * sin(-data->rotSpeed) \
		+ data->dirY * cos(-data->rotSpeed);
	oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(-data->rotSpeed) \
		- data->planeY * sin(-data->rotSpeed);
	data->planeY = oldPlaneX * sin(-data->rotSpeed) \
		+ data->planeY * cos(-data->rotSpeed);
}

void	move_forward(t_data *data)
{
	if (data->worldMap[(int)(data->posX \
		+ data->dirX * data->moveSpeed)][(int)data->posY] == 0)
		data->posX += data->dirX * data->moveSpeed;
	if (data->worldMap[(int)data->posX][(int)(data->posY \
		+ data->dirY * data->moveSpeed)] == 0)
		data->posY += data->dirY * data->moveSpeed;
}

void	move_backward(t_data *data)
{
	if (data->worldMap[(int)(data->posX \
		- data->dirX * data->moveSpeed)][(int)data->posY] == 0)
		data->posX -= data->dirX * data->moveSpeed;
	if (data->worldMap[(int)data->posX][(int)(data->posY \
		- data->dirY * data->moveSpeed)] == 0)
		data->posY -= data->dirY * data->moveSpeed;
}
