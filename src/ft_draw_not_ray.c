/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_not_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:51:41 by mschaub           #+#    #+#             */
/*   Updated: 2023/09/26 16:50:04 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_bottle(t_master *master)
{
	uint32_t		color;
	int				x;
	int				y;
	mlx_texture_t	*b;

	x = 4;
	y = 0;
	master->textures->bottle = mlx_load_png("textures/bottle_.png");
	if (!master->textures->bottle)
		ft_error(master, "Error loading the texture file\n", 0);
	b = master->textures->bottle;
	master->textures->c_bottle = get_color(master->textures->bottle, master);
	while (x++ < (int)master->textures->bottle->height - 8)
	{
		y = 0;
		while (y++ < (int)master->textures->bottle->width)
		{
			color = color_pixel(&master->textures->c_bottle[y + x * b->width]);
			if (color != 0)
				mlx_put_pixel(master->img, (WIDTH / 2 - (int)b->width / 2) + y,
					(HEIGHT - (int)b->height + 10) + x, color);
		}
	}
	free(master->textures->c_bottle);
	mlx_delete_texture(master->textures->bottle);
}

static mlx_image_t	*floor_ceil_2(int x, int y, t_master *master)
{
	mlx_image_t	*top;
	int			floor;
	int			ceiling;

	floor = get_rgba(master->map->floor[0], master->map->floor[1],
			master->map->floor[2]);
	ceiling = get_rgba(master->map->ceiling[0], master->map->ceiling[1],
			master->map->ceiling[2]);
	top = mlx_new_image(master->game->mlx, WIDTH, HEIGHT);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(top, x, y, ceiling);
			else
				mlx_put_pixel(top, x, y, floor);
			y++;
		}
		x++;
	}
	return (top);
}

void	floor_ceil(t_master *master)
{
	mlx_image_t	*top;

	top = floor_ceil_2(0, 0, master);
	if (mlx_image_to_window(master->game->mlx, top, 0, 0) < 0)
		ft_error(master, WIN_ERR, 0);
}
