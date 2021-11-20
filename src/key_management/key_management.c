/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:48:00 by jludt             #+#    #+#             */
/*   Updated: 2021/11/20 16:16:50 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	rotate_left(t_data *data)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = data->dirX;
	data->dirX = data->dirX * cos(data->rotSpeed) - data->dirY * sin(data->rotSpeed);
	data->dirY = oldDirX * sin(data->rotSpeed) + data->dirY * cos(data->rotSpeed);
	oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(data->rotSpeed) - data->planeY * sin(data->rotSpeed);
	data->planeY = oldPlaneX * sin(data->rotSpeed) + data->planeY * cos(data->rotSpeed);
}

static void	rotate_right(t_data *data)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = data->dirX;
	data->dirX = data->dirX * cos(-data->rotSpeed) - data->dirY * sin(-data->rotSpeed);
	data->dirY = oldDirX * sin(-data->rotSpeed) + data->dirY * cos(-data->rotSpeed);
	oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(-data->rotSpeed) - data->planeY * sin(-data->rotSpeed);
	data->planeY = oldPlaneX * sin(-data->rotSpeed) + data->planeY * cos(-data->rotSpeed);
}

static void	move_forward(t_data *data)
{
	if (data->worldMap[(int)(data->posX + data->dirX * data->moveSpeed)][(int)data->posY] == 0)
		data->posX += data->dirX * data->moveSpeed;
	if (data->worldMap[(int)data->posX][(int)(data->posY + data->dirY * data->moveSpeed)] == 0) 
		data->posY += data->dirY * data->moveSpeed;
}

static void	move_backward(t_data *data)
{
	if (data->worldMap[(int)(data->posX - data->dirX * data->moveSpeed)][(int)data->posY] == 0)
		data->posX -= data->dirX * data->moveSpeed;
	if (data->worldMap[(int)data->posX][(int)(data->posY - data->dirY * data->moveSpeed)] == 0) 
		data->posY -= data->dirY * data->moveSpeed;
}

static void	move_left(t_data *data)
{
	if (data->worldMap[(int)(data->posX - data->planeX * data->moveSpeed)][(int)data->posY] == 0)
		data->posX -= data->planeX * data->moveSpeed;
	if (data->worldMap[(int)data->posX][(int)(data->posY - data->planeY * data->moveSpeed)] == 0) 
		data->posY -= data->planeY * data->moveSpeed;
}

static void	move_right(t_data *data)
{
	if (data->worldMap[(int)(data->posX + data->planeX * data->moveSpeed)][(int)data->posY] == 0)
		data->posX += data->planeX * data->moveSpeed;
	if (data->worldMap[(int)data->posX][(int)(data->posY + data->planeY * data->moveSpeed)] == 0) 
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

	(void)y;
	
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