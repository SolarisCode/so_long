/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:58:22 by melkholy          #+#    #+#             */
/*   Updated: 2022/09/19 20:35:54 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct	s_queue
{
	int				row;
	int				col;
	struct s_queue	*next;
}				t_queue;

typedef struct	s_graph
{
	char	**map;
	int		**visit;
	int		in_layer;
	int		nx_layer;
	t_queue	*queue;
}				t_graph;

t_queue	*ft_queue_new(int row, int col)
{
	t_queue	*new;

	new = (t_queue *)calloc(1, sizeof(t_queue));
	if (!new)
		return (NULL);
	new->row = row;
	new->col = col;
	new->next = NULL;
	return (new);
}

t_queue	*ft_queuelast(t_queue *queue)
{
	if (!queue || !queue->next)
		return (queue);
	return (ft_queuelast(queue->next));
}

void	ft_queueadd(t_queue **queue, t_queue *new)
{
	t_queue	*tmp;

	if (!new)
		return ;
	if (!*queue)
	{
		*queue = new;
		return ;
	}
	tmp = ft_queuelast(*queue);
	tmp->next = new;
}

int	ft_queuecount(t_queue *queue)
{
	int	count;

	count = 0;
	while (queue)
	{
		queue = queue->next;
		count ++;
	}
	return (count);
}

void	ft_explore(int row, int col, t_graph *graph)
{
	t_queue	*tmp;
	int		d_row[4] = {-1, 1, 0, 0};
	int		d_col[4] = {0, 0, -1, 1};
	int		count;
	int		rd;
	int		cd;

	count = 0;
	while (count < 4)
	{
		rd = row + d_row[count];
		cd = col + d_col[count];
		count ++;
		if ((rd < 0 || rd >= 10) && (cd > 0 || cd >= 20))
			continue ;
		if (graph->visit[rd][cd])
			continue ;
		if (graph->map[rd][cd] == '1')
			continue ;
		tmp = ft_queue_new(rd, cd);
		ft_queueadd(&graph->queue, tmp);
		graph->visit[rd][cd] = 1;
		graph->nx_layer ++;
	}

}

int	ft_use_queue(char **map, int row, int col, int **visited)
{
	t_graph	*graph;
	t_queue	*tmp;
	int		move_count;
	int		r;
	int		c;
	int		found;

	move_count = 0;
	found = 0;
	graph = (t_graph *)calloc(1, sizeof(t_graph));
	graph->queue = ft_queue_new(row, col);
	graph->in_layer = 1;
	visited[row][col] = 1;
	graph->visit = visited;
	graph->map = map;
	while (graph->queue)
	{
		r = graph->queue->row;
		c = graph->queue->col;
		tmp = graph->queue->next;
		free(graph->queue);
		graph->queue = tmp;
		if (map[r][c] == 'E')
		{
			found ++;
			break ;
		}
		ft_explore(r, c, graph);
		graph->in_layer --;
		if (!graph->in_layer)
		{
			graph->in_layer = graph->nx_layer;
			graph->nx_layer = 0;
			move_count ++;
		}
	}
	if (found)
	{
		tmp = graph->queue->next;
		while (tmp)
		{
			free(graph->queue);
			graph->queue = tmp;
			tmp = graph->queue->next;
		}
		free(graph->queue);
	}
	free(graph);
	if (found)
		return (move_count);
	else
		return (-1);
}

int	ft_ispath(char **map)
{
	int		**visited;
	int		count;
	int		found;
	int		col;
	int		row;

	count = 0;
	row = 0;
	col = 0;
	visited = (int **)calloc(10, sizeof(int *));
	while (count < 10)
	{
		visited[count] = (int *)calloc(20, sizeof(int));
		count ++;
	}
	while (row < 10)
	{
		col = 0;
		while (col < 20)
		{
			if (map[row][col] == 'P' && !visited[row][col])
			{
				found = ft_use_queue(map, row, col, visited);
				break;
			}
			col ++;
		}
		row ++;
	}
	while (--count >= 0)
		free(visited[count]);
	free(visited);
	return (found);
}

int	main(void)
{
	
	char	**str;
	int		found;


	str = (char **)malloc(11 * sizeof(char *));
	str[0] = "11111111111111111111";
	str[1] = "10000000000000000001";
	str[2] = "10000001111100000001";
	str[3] = "10000000000100000001";
	str[4] = "1000000P000100000001";
	str[5] = "10000000000111000001";
	str[6] = "10000000011100000001";
	str[7] = "10000111100E00000001";
	str[8] = "10000000011100000001";
	str[9] = "11111111111111111111";
	str[10] = NULL;
	found = ft_ispath(str);
	if (found >= 0)
		printf("there is a path with %d moves\n", found);
	else
		printf("sorry can't find a path\n");
	free(str);
}
