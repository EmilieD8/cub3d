/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:22:50 by mschaub           #+#    #+#             */
/*   Updated: 2023/09/24 21:37:19 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	wall_loop(t_master *master, int cols, int map_x, int map_y)
{
	while (42)
	{
		if (master->ray[cols].side_dist_x < master->ray[cols].side_dist_y)
		{
			master->ray[cols].side_dist_x += master->ray[cols].delta_x;
			map_x += master->ray[cols].step_x;
			master->ray[cols].side = 0;
		}
		else
		{
			master->ray[cols].side_dist_y += master->ray[cols].delta_y;
			map_y += master->ray[cols].step_y;
			master->ray[cols].side = 1;
		}
		assign_textures(master, cols, map_x, map_y);
		assign_values(master, cols);
		master->ray[cols].height = HEIGHT / master->ray[cols].distance;
		if (master->map->full_map[map_x][map_y] != '0')
			break ;
	}
}

static void	set_camera_and_delta(t_master *master, int cols)
{
	double	camera_x;

	camera_x = 2 * cols / (double)WIDTH - 1;
	camera_x = -camera_x;
	master->ray[cols].dir.x = master->peter->dir.x
		+ master->peter->plane.x * camera_x;
	master->ray[cols].dir.y = master->peter->dir.y
		+ master->peter->plane.y * camera_x;
	if (master->ray[cols].dir.x == 0)
		master->ray[cols].delta_x = 1e30;
	else
		master->ray[cols].delta_x = fabs(1 / master->ray[cols].dir.x);
	if (master->ray[cols].dir.y == 0)
		master->ray[cols].delta_y = 1e30;
	else
		master->ray[cols].delta_y = fabs(1 / master->ray[cols].dir.y);
}

static void	set_side_dist(t_master *master, int cols, int map_x, int map_y)
{
	if (master->ray[cols].dir.x < 0)
	{
		master->ray[cols].step_x = -1;
		master->ray[cols].side_dist_x = (master->peter->pos.x - map_x)
			* master->ray[cols].delta_x;
	}
	else
	{
		master->ray[cols].step_x = 1;
		master->ray[cols].side_dist_x = (map_x + 1 - master->peter->pos.x)
			* master->ray[cols].delta_x;
	}
	if (master->ray[cols].dir.y < 0)
	{
		master->ray[cols].step_y = -1;
		master->ray[cols].side_dist_y = (master->peter->pos.y - map_y)
			* master->ray[cols].delta_y;
	}
	else
	{
		master->ray[cols].step_y = 1;
		master->ray[cols].side_dist_y = (map_y + 1 - master->peter->pos.y)
			* master->ray[cols].delta_y;
	}
}

static void	ray_loop(t_master *master)
{
	int		cols;
	int		map_x;
	int		map_y;

	cols = 0;
	map_y = (int)master->peter->pos.y;
	map_x = (int)master->peter->pos.x;
	while (cols < WIDTH)
	{
		set_camera_and_delta(master, cols);
		set_side_dist(master, cols, map_x, map_y);
		wall_loop(master, cols, map_x, map_y);
		cols++;
	}
}

void	ft_raycast(void *param)
{
	t_master	*master;

	master = (t_master *)param;
	update_player_position(master);
	if (master->exit == 0)
	{
		ray_loop(master);
		ft_render(master);
	}
}
