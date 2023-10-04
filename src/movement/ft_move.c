/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:56:26 by edrouot           #+#    #+#             */
/*   Updated: 2023/09/24 20:03:20 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*static void	exit_game_door(t_master *master)
{
	mlx_texture_t	*exit_game;
	uint32_t		*c_exit_game;
	uint32_t		color;
	int				x;
	int				y;

	master->exit = 1;
	x = -1;
	master->exit_game_img = mlx_new_image(master->game->mlx, WIDTH, HEIGHT);
	master->exit_game_img_alloc = 1;
	exit_game = mlx_load_png("textures/exit_img.png");
	c_exit_game = get_color(exit_game, master);
	while (x++ < (int)exit_game->height)
	{
		y = 0;
		while (y++ < (int)exit_game->width)
			mlx_put_pixel(master->exit_game_img, y, x,
				color_pixel(&c_exit_game[y + x * exit_game->width]));
	}
	free(c_exit_game);
	mlx_delete_texture(exit_game);
	if (mlx_image_to_window(master->game->mlx, master->exit_game_img, 0, 0) < 0)
		ft_error(master, "Error loading the image to the window\n");
}*/

static void	change_pos_helper1(t_master *master, t_pos new, double steps)
{
	if (master->walk_dir == -2)
	{
		new.x = master->peter->pos.x + master->peter->dir.y * steps;
		new.y = master->peter->pos.y - master->peter->dir.x * steps;
		if (master->map->full_map[(int)new.x][(int)new.y] == '0')
		{
			master->peter->pos.x = new.x;
			master->peter->pos.y = new.y;
		}
		else if (master->map->full_map[(int)new.x][(int)new.y] == '2')
			exit(EXIT_SUCCESS);
	}
	else if (master->walk_dir == 2)
	{
		new.x = master->peter->pos.x - master->peter->dir.y * steps;
		new.y = master->peter->pos.y + master->peter->dir.x * steps;
		if (master->map->full_map[(int)new.x][(int)new.y] == '0')
		{
			master->peter->pos.x = new.x;
			master->peter->pos.y = new.y;
		}
		else if (master->map->full_map[(int)new.x][(int)new.y] == '2')
			exit(EXIT_SUCCESS);
	}
}

void	change_position(t_master *master, t_pos new, double steps)
{
	if (master->walk_dir == -1)
	{
		new.x = master->peter->pos.x - master->peter->dir.x * steps;
		new.y = master->peter->pos.y - master->peter->dir.y * steps;
		if (master->map->full_map[(int)new.x][(int)new.y] == '0')
		{
			master->peter->pos.x = new.x;
			master->peter->pos.y = new.y;
		}
		else if (master->map->full_map[(int)new.x][(int)new.y] == '2')
			exit(EXIT_SUCCESS);
	}
	else if (master->walk_dir == 1)
	{
		new.x = master->peter->pos.x + master->peter->dir.x * steps;
		new.y = master->peter->pos.y + master->peter->dir.y * steps;
		if (master->map->full_map[(int)new.x][(int)new.y] == '0')
		{
			master->peter->pos.x = new.x;
			master->peter->pos.y = new.y;
		}
		else if (master->map->full_map[(int)new.x][(int)new.y] == '2')
			exit(EXIT_SUCCESS);
	}
	change_pos_helper1(master, new, steps);
}

void	update_player_position(t_master *master)
{
	t_pos	new;
	double	steps;

	steps = 0.05;
	new = (t_pos){0, 0};
	change_angle(master);
	change_position(master, new, steps);
}

void	change_angle(t_master *master)
{
	double	rotationspeed;
	double	olddir_x;
	double	oldplane_x;

	rotationspeed = 0.03;
	if (master->turn_dir == 0)
		return ;
	if (master->turn_dir == -1)
		rotationspeed *= -1;
	olddir_x = master->peter->dir.x;
	master->peter->dir.x = master->peter->dir.x
		* cos(rotationspeed) - master->peter->dir.y
		* sin(rotationspeed);
	master->peter->dir.y = olddir_x
		* sin(rotationspeed) + master->peter->dir.y
		* cos(rotationspeed);
	oldplane_x = master->peter->plane.x;
	master->peter->plane.x = master->peter->plane.x
		* cos(rotationspeed) - master->peter->plane.y
		* sin(rotationspeed);
	master->peter->plane.y = oldplane_x
		* sin(rotationspeed) + master->peter->plane.y
		* cos(rotationspeed);
}
