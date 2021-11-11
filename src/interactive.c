/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:28:29 by julian            #+#    #+#             */
/*   Updated: 2021/11/11 17:43:06 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}


int	interactive(int key, t_data	*data)
{	
	// data->frame1 = data->frame2;
	// data->frame2 = get_time();
	// data->fps = data->frame2 - data->frame1;
	
	if (key == KEY_ESCAPE) 				//free data befor exiting still to be done
		exit(0);
	else if (key == KEY_ANSI_A)			//move to the left
	{
		data->pa -= 0.1;
		if (data->pa < 0)
			data->pa += 2 * M_PI;
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
		// px += 10;
	}
	else if (key == KEY_ANSI_D)			//move to the right
	{
		data->pa += 0.1;
		if (data->pa > 2 * M_PI)
			data->pa -= 2 * M_PI;
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
		// px += 10;
	}
	else if (key == KEY_ANSI_W)			//move forward
	{
		data->px += data->pdx;
		data->py += data->pdy;
		//py -= 10;
	}	
	else if (key == KEY_ANSI_S)			//move backwards
	{
		data->px -= data->pdx;
		data->py -= data->pdy;
		// py += 10;
	}
	// else if (key == KEY_LEFTARROW)		//look/turn to the left
	// {
	// 	pa -= 0.1;
	// 	if (pa < 0)
	// 		pa += 2 * M_PI;
	// 	pdx = cos(pa) * 5;
	// 	pdy = sin(pa) * 5;
	// }
	// else if (key == KEY_RIGHTARROW)		//look/turn to the right
	// {
	// 	pa += 0.1;
	// 	if (pa > 2 * M_PI)
	// 		pa -= 2 * M_PI;
	// 	pdx = cos(pa) * 5;
	// 	pdy = sin(pa) * 5;
	// }
	return (0);
}