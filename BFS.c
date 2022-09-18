/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 00:06:21 by melkholy          #+#    #+#             */
/*   Updated: 2022/09/18 18:54:06 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool	ft_issafe(int r, int c)
{
	if (r >= 0 && r < 10 && c >= 0 && c < 20)
		return (true);
	return (false);
}

bool	ft_find_path(char **map, int row, int col, int **visited)
{
	bool	up;
	bool	down;
	bool	right;
	bool	left;

	if (ft_issafe(row, col) && map[row][col] != '1' \
			&& !visited[row][col])
	{
		visited[row][col] = 1;
		if (map[row][col] == 'E')
			return (true);
		right = ft_find_path(map, row, col + 1, visited);
		if (right)
			return (true);
		left = ft_find_path(map, row, col - 1, visited);
		if (left)
			return (true);
		up = ft_find_path(map, row - 1, col, visited);
		if (up)
			return (true);
		down = ft_find_path(map, row + 1, col, visited);
		if(down)
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
	str[6] = "10000000000100000001";
	str[7] = "10000111101E10000001";
	str[8] = "10000000000100000001";
	str[9] = "11111111111111111111";
	str[10] = NULL;
	found = ft_ispath(str);
	if (found)
		printf("there is a path\n");
	else
		printf("sorry didn't find one\n");
}
