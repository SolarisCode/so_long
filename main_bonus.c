/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:35:52 by melkholy          #+#    #+#             */
/*   Updated: 2022/10/07 16:56:30 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

bool	ft_validate_map(t_graph *graph)
{
	int	count;
	int	c_in;

	count = -1;
	c_in = -1;
	while (graph->map[++count])
	{
		c_in = -1;
		while (graph->map[count][++c_in])
			if (!ft_strchr("01PGCE", graph->map[count][c_in]))
				return (ft_printf("Error\nInvalid map character\n"), false);
	}
	while (--c_in >= 0)
		if (graph->map[0][c_in] != '1')
			return (ft_printf("Error\nInvalid map structure\n"), false);
	while (graph->map[0][++c_in])
		if (graph->map[graph->row - 1][c_in] != '1')
			return (ft_printf("Error\nInvalid map structure\n"), false);
	while (++c_in - graph->col < graph->row - 1)
		if (graph->map[c_in - graph->col][0] != '1' \
				|| graph->map[c_in - graph->col][graph->col - 1] != '1')
			return (ft_printf("Error\nInvalid map structure\n"), false);
	if (ft_check_p_c_e(graph) != 1 || graph->gate < 1 || graph->cats < 1)
		return (ft_printf("Error\nYou can have P==1, E>0, C>0 only\n"), false);
	return (true);
}

bool	ft_get_map(char *file, t_graph *graph)
{
	char	*line;
	int		count;
	int		fd;

	count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	graph->map[count] = ft_strtrim(line, "\n");
	free(line);
	while (graph->map[count])
	{
		count ++;
		line = get_next_line(fd);
		graph->map[count] = ft_strtrim(line, "\n");
		free(line);
	}
	close(fd);
	graph->row = count;
	graph->col = ft_strlen(graph->map[0]);
	while (--count >= 0)
		if (graph->col != (int)ft_strlen(graph->map[count]))
			return (ft_printf("Error\nInvalid map structure\n"), false);
	return (ft_validate_map(graph));
}

bool	ft_maplen(char *file, t_graph *graph)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nFile doesn't exsit.\n"), false);
	line = get_next_line(fd);
	if (line)
		graph->col = ft_strlen(line) - 1;
	else
		return (ft_printf("Error\nThis is an empty map.\n"), false);
	while (line)
	{
		graph->row ++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	graph->map = (char **)ft_calloc(graph->row + 1, sizeof(char *));
	if (!graph->map)
		return (false);
	graph->map[graph->row] = NULL;
	return (true);
}

t_graph	*ft_check_map(char *file)
{
	t_graph	*graph;

	if (!ft_strnstr(file, ".ber", ft_strlen(file)))
	{
		ft_printf("Error\nPlease pass the correct Map format\n");
		return (NULL);
	}
	graph = (t_graph *)ft_calloc(1, sizeof(t_graph));
	if (!graph)
		return (NULL);
	if (!(ft_maplen(file, graph) && ft_get_map(file, graph) \
				&& ft_ispath(graph)))
	{
		ft_free_graph(graph);
		return (NULL);
	}
	return (graph);
}

int	main(int argc, char *argv[])
{
	t_graph	*graph;

	if (argc != 2)
		exit(40 - write(2, "Error\nYou need one argument (Map file)\n", 39));
	graph = ft_check_map(argv[1]);
	if (graph)
		ft_start_graphics(graph);
	return (0);
}
