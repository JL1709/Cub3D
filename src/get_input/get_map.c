/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:04:32 by julian            #+#    #+#             */
/*   Updated: 2021/11/20 14:31:56 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_map_for_invalid_char(t_data *data, char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] != '1' && s[i] != '0' && s[i] != 'N' && s[i] != 'S'
			&& s[i] != 'W' && s[i] != 'E' && s[i] != ' ' && s[i] != '\n')
		{
			printf("Error\n");
			printf("Map contains invalid character %c\n", s[i]);
			printf("Allowed characters are:\n");
			printf("0 for empty space\n");
			printf("1 for a wall\n");
			printf("N, S, W or E for player's starting position/orientation\n");
			return (FAILURE);
		}
		if (s[i] == 'N' || s[i] == 'E' || s[i] == 'S' || s[i] == 'W')
			data->map.player = s[i];
	}
	return (SUCCESS);
}

static int	check_first_last_row_column(char **map, t_data *data)
{
	int	x;
	int	y;
	int	error;

	x = 0;
	y = -1;
	error = 0;
	while (++y < data->map.height && error == 0)
	{
		if ((map[0][y] != '1' && map[0][y] != ' ') \
			|| (map[data->map.width - 1][y] != '1' \
			&& map[data->map.width - 1][y] != ' '))
			error = 1;
	}
	while (++x < data->map.width && error == 0)
	{
		if ((map[x][0] != '1' && map[x][0] != ' ') \
			|| (map[x][data->map.height - 1] != '1' \
			&& map[x][data->map.height - 1] != ' '))
			error = 1;
	}
	if (error == 1)
		return (printf("Error\nMap not surrounded\n"));
	return (SUCCESS);
}

static int	check_inbetween(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (++x < data->map.width - 1)
	{
		y = 0;
		while (++y < data->map.height - 1)
		{
			if (data->map.d2[x][y] == '0')
			{
				if (data->map.d2[x - 1][y] == ' ' \
					|| data->map.d2[x][y - 1] == ' ' \
					|| data->map.d2[x + 1][y] == ' ' \
					|| data->map.d2[x][y + 1] == ' ')
					return (printf("Error\nInvalid Map\n"));
			}
		}
	}
	return (SUCCESS);
}

static int	check_valid_player(t_data *data, int x, int y)
{
	int	found;

	x = 0;
	found = 0;
	while (++x < data->map.width - 1)
	{
		y = 0;
		while (++y < data->map.height - 1)
		{
			if (data->map.d2[x][y] == 'N' || data->map.d2[x][y] == 'E' \
				|| data->map.d2[x][y] == 'S' || data->map.d2[x][y] == 'W')
			{
				data->posX = x + 0.5;
				data->posY = y + 0.5;
				found++;
				if (found > 1)
					return (printf("Error\nPlayer duplicationn\n"));
				if (data->map.d2[x - 1][y] == ' ' \
					|| data->map.d2[x][y - 1] == ' ' \
					|| data->map.d2[x + 1][y] == ' ' \
					|| data->map.d2[x][y + 1] == ' ')
					return (printf("Error\nInvalid player position\n"));
			}
		}
	}
	return (SUCCESS);
}

int	is_map_valid(t_data *data)
{
	int	x;
	int	y;

	if (check_first_last_row_column(data->map.d2, data))
		return (FAILURE);
	if (check_inbetween(data))
		return (FAILURE);
	x = 0;
	y = 0;
	if (check_valid_player(data, x, y))
		return (FAILURE);
	return (SUCCESS);
}
