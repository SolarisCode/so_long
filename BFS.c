/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:58:22 by melkholy          #+#    #+#             */
/*   Updated: 2022/09/18 22:59:02 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool	ft_find_path(char **map, int row, int col, int **visited)
{
	bool	safe;

	safe = false;
	if (row >= 0 && row < 10 && col >= 0 && col < 20)
		safe = true;
	if (safe && map[row][col] != '1' && !visited[row][col])
	{
		visited[row][col] = 1;
		if (map[row][col] == 'E')
			return (true);
		if (ft_find_path(map, row, col + 1, visited))
			return (true);
		if (ft_find_path(map, row, col - 1, visited))
			return (true);
		if (ft_find_path(map, row - 1, col, visited))
			return (true);
		if(ft_find_path(map, row + 1, col, visited))
			return (true);
	}
	return (false);
}

bool	ft_ispath(char **map)
{
	int		**visited;
	int		count;
	bool	found;
	int		col;
	int		row;

	count = 0;
	row = 0;
	col = 0;
	found = false;
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
				if (ft_find_path(map, row, col, visited))
				{
					found = true;
					break ;
				}
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
	bool	found;


	str = (char **)malloc(11 * sizeof(char *));
	str[0] = "11111111111111111111";
	str[1] = "10000000000000000001";
	str[2] = "10000001111100000001";
	str[3] = "10000000000100000001";
	str[4] = "1000000P000100000001";
	str[5] = "10000000000111000001";
	str[6] = "10000000011100000001";
	str[7] = "10000111100E10000001";
	str[8] = "10000000011100000001";
	str[9] = "11111111111111111111";
	str[10] = NULL;
	found = ft_ispath(str);
	if (found)
		printf("there is a path\n");
	else
		printf("sorry can't find a path\n");
	free(str);
}
