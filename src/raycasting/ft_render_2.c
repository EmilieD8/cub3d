/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:59:51 by mschaub           #+#    #+#             */
/*   Updated: 2023/09/26 16:49:41 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_ray_minimap(t_master *master)
{
	int		l_x;
	int		l_y;
	int		i;
	int		px;
	int		py;

	l_x = -5 + (master->peter->pos.y * 10) + 10 / 2;
	l_y = -5 + (master->peter->pos.x * 10) + 10 / 2;
	i = 0;
	while (i <= 10)
	{
		px = l_x + i * cos((-M_PI / 2.0) 
				+ atan2(master->peter->dir.y, master->peter->dir.x));
		py = l_y - i * sin((-M_PI / 2.0)
				+ atan2(master->peter->dir.y, master->peter->dir.x));
		mlx_put_pixel(master->img, px, py, 1770457343);
		i++;
	}
}

static void	minimap_loop(t_master *master, int first, int x, int y)
{
	int	nb;

	nb = 0;
	while (nb <= 10)
	{
		if (master->map->full_map[x][y] != '0' )
			mlx_put_pixel(master->img, y * 10 + nb,
				x * 10 + first, 1770457343);
		else
			mlx_put_pixel(master->img, y * 10 + nb,
				x * 10 + first, -1344205057);
		nb++;
	}
}

void	draw_minimap(t_master *master)
{
	int	x;
	int	y;
	int	first_nb;

	x = 0;
	while (x < master->map->nb_rows)
	{
		y = 0;
		while (y < master->map->nb_columns)
		{
			first_nb = 0;
			while (first_nb <= 10)
			{
				minimap_loop(master, first_nb, x, y);
				first_nb++;
			}
			y++;
		}
		x++;
	}
	draw_player(master);
	draw_ray_minimap(master);
}

void	draw_player(t_master *master)
{
	int	player_x;
	int	player_y;
	int	nb;
	int	first_nb;

	first_nb = 0;
	player_x = master->peter->pos.y * 10 - 2;
	player_y = master->peter->pos.x * 10 - 2 ;
	while (first_nb < 4)
	{
		nb = 0;
		while (nb < 4)
		{
			mlx_put_pixel(master->img, player_x + first_nb,
				player_y + nb, 1770457343);
			nb++;
		}
		first_nb++;
	}
}

void	textures_helper(t_master *master, t_texture *textures)
{
	textures->south = mlx_load_png(master->map->south);
	if (!textures->south)
		ft_error(master, "Error loading the texture file\n", 0);
	textures->c_south = get_color(textures->south, master);
	textures->west = mlx_load_png(master->map->west);
	if (!textures->west)
		ft_error(master, "Error loading the texture file\n", 0);
}
