/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_fc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:10:02 by julian            #+#    #+#             */
/*   Updated: 2021/11/20 18:30:24 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	helper(char **s1, char **s2, char *s3)
{
	if (s1)
		ft_free_array(s1);
	if (s2)
		ft_free_array(s2);
	return (printf("%s", s3));
}

static int	helper2(t_data *data, char **input, char **rgb)
{
	if (rgb == NULL)
	{
		if (input == NULL)
			return (printf("Error\nInput couldn't be splitted correctly\n"));
		if (ft_array_len(input) != 2)
			return (helper(input, NULL, "Error\nInfo wrong formatted\n"));
		if ((!ft_strcmp(input[0], "F") && data->map.color_floor[3] == 1)
			|| (!ft_strcmp(input[0], "C") && data->map.color_ceiling[3] == 1))
			return (helper(input, NULL, "Error\nDuplication of identifier\n"));
	}
	else
	{
		if (rgb == NULL)
			return (helper(input, NULL, "Error\nWrong splitting\n"));
		if (ft_array_len(rgb) != 3)
			return (helper(input, rgb, "Error\nWrong number of arguments\n"));
		if (rgb[2][ft_strlen(rgb[2]) - 1] == '\n')
			rgb[2] = ft_strtrim(rgb[2], "\n");
	}
	return (SUCCESS);
}

static void	helper3(t_data *data, char **input, char **rgb, int i)
{
	if (!ft_strcmp(input[0], "F"))
		data->map.color_floor[i] = ft_atoi(rgb[i]);
	else
		data->map.color_ceiling[i] = ft_atoi(rgb[i]);
}

static int	helper4(t_data *data, char **input, char **rgb)
{
	if (!ft_strcmp(input[0], "F"))
		data->map.color_floor[3] = 1;
	else
		data->map.color_ceiling[3] = 1;
	ft_free_array(input);
	ft_free_array(rgb);
	data->map.info++;
	return (SUCCESS);
}

int	get_color_fc(t_data *data, char *str)
{
	t_color	c;

	c.input = ft_split(str, ' ');
	if (helper2(data, c.input, NULL) > 0)
		return (FAILURE);
	c.rgb = ft_split(c.input[1], ',');
	if (helper2(data, c.input, c.rgb) > 0)
		return (FAILURE);
	c.i = -1;
	while (++c.i < 3)
	{
		if (ft_strlen(c.rgb[0]) > 3)
			return (helper(c.input, c.rgb, "Error\nOne number for R,G and B\n"));
		c.j = -1;
		while (c.rgb[c.i][++c.j] != '\0')
		{
			if (!ft_isdigit(c.rgb[c.i][c.j]))
				return (helper(c.input, c.rgb, "Error\nColors must be digits\n"));
			if ((c.j == 0 && ft_id(c.rgb[c.i][c.j]) && c.rgb[c.i][c.j] > '2')
				|| (c.j > 0 && ft_id(c.rgb[c.i][c.j]) && c.rgb[c.i][c.j] > '5'))
				return (helper(c.input, c.rgb, "Error\nColor range [0,255]\n"));
		}
		helper3(data, c.input, c.rgb, c.i);
	}
	return (helper4(data, c.input, c.rgb));
}
