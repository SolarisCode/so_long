/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:56:56 by melkholy          #+#    #+#             */
/*   Updated: 2022/11/05 17:52:44 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf_bonus.h"
#include "so_long_bonus.h"

void	ft_free_graph(t_graph *graph)
{
	int	count;

	count = 0;
	if (graph->map)
	{
		while (graph->map[count])
		{
			free(graph->map[count]);
			count ++;
		}
		free(graph->map);
	}
	free(graph);
}

int	ft_check_p_c_e(t_graph *graph)
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
				graph->cats ++;
		}
	}
	return (player);
}

bool	ft_find_path(t_graph *graph, int **visited)
{
	int	count;
	int	c_in;
	int	gates;
	int	cats;

	count = -1;
	gates = 0;
	cats = 0;
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
					cats ++;
		}
	}
	if ((cats + gates) == (graph->gate + graph->cats))
		return (true);
	else
		return (ft_printf("Error\nThere is no valid path in the map\n"), false);
}

void	ft_mark_path(t_graph *graph, int row, int col, int **visited)
{
	if ((row < 0 || row >= graph->row) && (col < 0 || col >= graph->col))
		return ;
	if (graph->map[row][col] != '1' && graph->map[row][col] != 'G' \
			&& visited[row][col] != 1)
	{
		visited[row][col] = 1;
		ft_mark_path(graph, row, col + 1, visited);
		ft_mark_path(graph, row, col - 1, visited);
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
	visited = (int **)ft_calloc(graph->row, sizeof(int *));
	while (count < graph->row)
	{
		visited[count] = (int *)ft_calloc(graph->col, sizeof(int));
		count ++;
	}
	ft_mark_path(graph, graph->player[0], graph->player[1], visited);
	valid = ft_find_path(graph, visited);
	while (--count >= 0)
		free(visited[count]);
	free(visited);
	return (valid);
}
