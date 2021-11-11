/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:28:29 by julian            #+#    #+#             */
/*   Updated: 2021/11/10 15:30:14 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	interactive(int key, t_data	*data)
{	
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