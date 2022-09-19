/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:33:50 by melkholy          #+#    #+#             */
/*   Updated: 2022/09/20 00:28:02 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "./ft_printf/ft_printf_bonus.h"
#include "./ft_printf/libft/libft.h"

typedef struct	s_graph
{
	char	**map;
	int		player[2];
	int		row;
	int		col;
	int		gems;
}				t_graph;

int	*ft_check_P_C_E(t_graph *graph)
{
	int	*valid;
	int	count;
	int	c_in;

	valid = (int *)ft_calloc(2, sizeof(int));
	count = -1;
	while (graph->map[++count])
	{
		c_in = -1;
		while (graph->map[count][++c_in])
		{
			if (graph->map[count][c_in] == 'P')
			{
				valid[0] ++;
				graph->player[0] = count;
				graph->player[1] = c_in;
			}
			else if (graph->map[count][c_in] == 'E')
				valid[1] ++;
			else if (graph->map[count][c_in] == 'C')
				graph->gems ++;
		}
	}
	return (valid);
}

bool	ft_check_wall(t_graph *graph)
{
	int		count;
	int		*ply_ex;
	bool	valid;

	count = -1;
	valid = true;
	while (graph->map[0][++count])
		if (graph->map[0][count] != '1')
			return (false);
	while (--count >= 0)
		if (graph->map[graph->row - 1][count] != '1')
			return (false);
	while (++count < graph->row - 1)
		if (graph->map[count][0] != '1' \
				|| graph->map[count][graph->col - 1] != '1')
			return (false);
	ply_ex = ft_check_P_C_E(graph);
	if (ply_ex[0] != 1 || ply_ex[1] < 1 || graph->gems < 1)
		valid = false;
	free(ply_ex);
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
	graph->row = count;
	graph->col = ft_strlen(graph->map[0]);
	while (--count >= 0)
		if (graph->col != ft_strlen(graph->map[count]))
			return (false);
	return (ft_check_wall(graph));
}

t_graph	*ft_check_map(char *file)
{
	t_graph	*graph;

	graph = (t_graph *)ft_calloc(1, sizeof(t_graph));
	if (!ft_strnstr(file, ".ber", ft_strlen(file)))
		return (NULL);
	if (!ft_get_map(file, graph))
	{
		ft_free_2d(graph->map);
		free(graph);
		return (NULL);
	}
	return (graph);
}

int	main(int argc, char *argv[])
{
	t_graph *graph;

	if (argc != 2)
		return (5 - write(2, "Error\n", 6));
	graph = ft_check_map(argv[1]);
}
