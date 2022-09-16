/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:27:02 by melkholy          #+#    #+#             */
/*   Updated: 2022/09/17 00:29:46 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <stdlib.h>

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bites_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * \
						(data->bites_per_pixel / 8));
	*(unsigned int*)dst = color; 
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	// t_data	im g;
	int		count;
	int		height;
	int		width;
	char	*skull;
	void	*im_sk;
	char	**str;


	str = (char **)malloc(11 * sizeof(char *));
	str[0] = "11111111111111111111";
	str[1] = "10000000000000000001";
	str[2] = "10000000000000000001";
	str[3] = "10000000000000000001";
	str[4] = "10000000000000000001";
	str[5] = "10000000000000000001";
	str[6] = "10000000000000000001";
	str[7] = "10000000000000000001";
	str[8] = "10000000000000000001";
	str[9] = "11111111111111111111";
	str[10] = NULL;
	count = 0;
	int i = 0;
	skull = "./wall.xpm";
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 20 * 64, 10 * 64, "Hey it's me");
	while (i < 10 * 64)
	{
		count = 0;
		while (count < 20 * 64)
		{
			if (str[i / 64][count / 64] == '1')
				skull = "./wall.xpm";
			else if (str[i / 64][count / 64] == '0')
				skull = "./space.xpm";
			im_sk = mlx_xpm_file_to_image(mlx, skull, &width, &height);
			mlx_put_image_to_window(mlx, mlx_win, im_sk, count, i);
			count += 64;
		}
		i += 64;
	}
	mlx_loop(mlx);
	return (0);
}
