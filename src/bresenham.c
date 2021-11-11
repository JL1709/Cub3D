/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:48:06 by julian            #+#    #+#             */
/*   Updated: 2021/11/10 15:55:31 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void line(int x0, int y0, int x1, int y1)
{
	int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2;

	while (1)
	{
		setPixel(x0,y0);
		if (x0==x1 && y0==y1) 
			break;
		e2 = 2 * err;
		if (e2 > dy) 
		{ 
			err += dy;
			x0 += sx; 
		}
		if (e2 < dx)
		{ 
			err += dx;
			y0 += sy; 
		}
	}
}