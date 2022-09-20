/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:33:50 by melkholy          #+#    #+#             */
/*   Updated: 2022/09/20 22:16:03 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/fcntl.h>
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
	int		gate;
}				t_graph;

void	ft_free_2d(char **map)
{
	int	count;

	count = 0;
	while (map[count])
	{
		free(map[count]);
		count ++;
	}
	free(map);
}

int	ft_check_P_C_E(t_graph *graph)
{
	int	player;
	int	count;
	int	c_in;

	count = -1;
	player = 0;
	while (graph->map[++count])
	{
		c_in = -1;
		while (graph->map[count][++c_in])
		{
			if (graph->map[count][c_in] == 'P')
			{
				player ++;
				graph->player[0] = count;
				graph->player[1] = c_in;
			}
			else if (graph->map[count][c_in] == 'E')
				graph->gate ++;
			else if (graph->map[count][c_in] == 'C')
				graph->gems ++;
		}
	}
	return (player);
}

bool	ft_check_wall(t_graph *graph)
{
	int		count;
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
	if (ft_check_P_C_E(graph) != 1 || graph->gate < 1 || graph->gems < 1)
		valid = false;
	return (valid);
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
		if (graph->col != (int)ft_strlen(graph->map[count]))
			return (false);
	close(fd);
	return (ft_check_wall(graph));
}

bool	ft_maplen(char *file, t_graph *graph)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (line)
		graph->col = ft_strlen(line) - 1;
	else
		return (false);
	while (line)
	{
		graph->row ++;
		free(line);
		line = get_next_line(fd);
	}
	graph->map = (char **)ft_calloc(graph->row + 1, sizeof(char *));
	graph->map[graph->row] = NULL;
	if (!graph->map)
		return (false);
	else
		return (true);
}

bool	ft_find_path(t_graph *graph, int **visited)
{
	int	count;
	int c_in;
	int gates;
	int	gems;

	count = -1;
	gates = 0;
	gems = 0;
	while (graph->map[++count])
	{
		c_in = -1;
		while (graph->map[count][++c_in])
		{
			if (graph->map[count][c_in] == 'E')
				if (visited[count][c_in])
					gates ++;
			if (graph->map[count][c_in] == 'C')
				if (visited[count][c_in])
					gems ++;
		}
	}
	if ((gems + gates) == (graph->gate + graph->gems))
		return (true);
	else
		return (false);
}

void	ft_mark_path(t_graph *graph, int row, int col, int **visited)
{
	if ((row < 0 || row >= graph->row) && (col < 0 || col >= graph->col))
		return ;
	if (graph->map[row][col] != '1' && !visited[row][col])
	{
		visited[row][col] = 1;
		ft_mark_path(graph, row, col +  1, visited);
		ft_mark_path(graph, row, col -  1, visited);
		ft_mark_path(graph, row - 1, col, visited);
		ft_mark_path(graph, row + 1, col, visited);
	}
}

bool	ft_ispath(t_graph *graph)
{
	int		**visited;
	int		count;
	bool	valid;

	count = 0;
	valid = true;
	visited = (int **)calloc(graph->row + 1, sizeof(int *));
	visited[graph->row] = NULL;
	while (count < graph->row)
	{
		visited[count] = (int *)calloc(graph->col + 1, sizeof(int));
		count ++;
	}
	ft_mark_path(graph, graph->player[0], graph->player[1], visited);
	valid = ft_find_path(graph, visited);
	while (--count >= 0)
		free(visited[count]);
	free(visited);
	return (valid);
}

t_graph	*ft_check_map(char *file)
{
	t_graph	*graph;

	graph = (t_graph *)ft_calloc(1, sizeof(t_graph));
	if (!graph)
		return (NULL);
	if (!ft_strnstr(file, ".ber", ft_strlen(file)))
		return (NULL);
	if (!ft_maplen(file, graph))
	{
		free(graph);
		return (NULL);
	}
	if (!ft_get_map(file, graph))
	{
		ft_free_2d(graph->map);
		free(graph);
		return (NULL);
	}
	if (!ft_ispath(graph))
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
	bool	valid;

	valid = true;
	if (argc != 2)
		exit(5 - write(2, "Error\n", 6));
	graph = ft_check_map(argv[1]);
	if (!graph)
		valid = false;
	else
	{
		ft_free_2d(graph->map);
		free(graph);
	}
	if(!valid)
		exit(5 - write(2, "Error\n", 6));
	else
		ft_printf("Valid map\n");
}
