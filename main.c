/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:27:02 by melkholy          #+#    #+#             */
/*   Updated: 2022/09/14 23:31:34 by melkholy         ###   ########.fr       */
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
	t_data	img;
	int		count;

	count = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hey it's me");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bites_per_pixel, \
									&img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// while (count < 100)
	// {
	mlx_put_image_to_window(mlx, mlx_win, img.img, count + 1, count + 1);
	mlx_put_image_to_window(mlx, mlx_win, img.img, count + 2, count + 2);
	mlx_put_image_to_window(mlx, mlx_win, img.img, count + 3, count + 3);
	mlx_put_image_to_window(mlx, mlx_win, img.img, count + 4, count + 4);
		// count ++;
	// }
	mlx_loop(mlx);
	return (0);
}
