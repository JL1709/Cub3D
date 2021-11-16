/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:45:22 by jludt             #+#    #+#             */
/*   Updated: 2021/11/16 15:44:18 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	test_general(int argc, char *argv[])
{
	int	in;

	if (argc != 2)
	{
		printf(RED"Error\n"RESET);
		printf("Program needs scene description file with .cub extension\n");
		printf(YELLOW"Usage: "RESET);
		return(printf("./cub3D .cub_file\n"));
	}
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4))
	{
		printf(RED"Error\n"RESET);
		printf("Scene description file must have .cub extension\n");
		printf(YELLOW"Usage: "RESET);
		return(printf("./cub3D .cub_file\n"));
	}
	in = open(argv[1], O_RDONLY);
	if (in < 0)
	{
		printf(RED"Error\n"RESET);
		return(printf("%s: %s\n", strerror(errno), argv[1]));
	}
	close(in);
	return (SUCCESS);
}



int	get_map_look(t_data *data, char *input)
{
	int		in;
	int		i;
	// int		j;
	char	*gnl;
	char	**src;

	(void)	*data;
	in = open(input, O_RDONLY);
	gnl = get_next_line(in);
	if (!gnl)
	{
		printf(RED"Error\n"RESET);
		return (printf("Empty .cub-file\n"));
	}
	i = 0;
	while ((gnl = get_next_line(in)))
	{
		printf("%s", gnl);
		free(gnl);
		gnl = NULL;
		i++;
	}
	printf("i = %d\n", i);
	src = (char **)malloc(sizeof(char *) * i + 1);
	if (src == NULL)
	{
		printf(RED"Error\n"RESET);
		return (printf("Memory allocation failed\n"));
	}
	// j = 0;
	// while (j < i)
	// {
	// 	src[j] = get_next_line(in);
	// 	printf("%s", src[j]);
	// 	j++;
	// }
	// src[j] = NULL;
	// i = -1;
	// while (src[++i] != NULL)
	// 	printf("%s", src[i]);
	
	return (SUCCESS);
}


int	get_input(t_data *data, int argc, char *argv[])
{
	if (test_general(argc, argv))
		return (FAILURE);
	if (get_map_look(data, argv[1]))
		return (FAILURE);
	
	
	return (SUCCESS);
}