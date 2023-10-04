/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:22:50 by mschaub           #+#    #+#             */
/*   Updated: 2023/09/23 00:45:57 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	north_south(t_master *master, int cols, int step_x)
{
	if (step_x < 0)
	{
		master->ray[cols].tex_height
			= master->textures->north->height;
		master->ray[cols].tex_width
			= master->textures->north->width;
		master->ray[cols].ray_color = master->textures->c_north;
		master->ray[cols].color = NORTH;
	}
	else
	{
		master->ray[cols].tex_height
			= master->textures->south->height;
		master->ray[cols].tex_width
			= master->textures->south->width;
		master->ray[cols].ray_color = master->textures->c_south;
		master->ray[cols].color = SOUTH;
	}
}

static void	west_east(t_master *master, int cols, int step_y)
{
	if (step_y < 0)
	{
		master->ray[cols].tex_height
			= master->textures->west->height;
		master->ray[cols].tex_width
			= master->textures->west->width;
		master->ray[cols].ray_color = master->textures->c_west;
		master->ray[cols].color = WEST;
	}
	else
	{
		master->ray[cols].tex_height
			= master->textures->east->height;
		master->ray[cols].tex_width
			= master->textures->east->width;
		master->ray[cols].ray_color = master->textures->c_east;
		master->ray[cols].color = EAST;
	}
}

void	assign_values(t_master *master, int cols)
{
	if (master->ray[cols].side == 0)
	{
		master->ray[cols].distance = (master->ray[cols].side_dist_x
				- master->ray[cols].delta_x);
		master->ray[cols].pos_wall.x
			= master->peter->pos.y + master->ray[cols].distance
			* master->ray[cols].dir.y;
		master->ray[cols].pos_wall.y = master->peter->pos.x
			+ master->ray[cols].distance * master->ray[cols].dir.x;
	}
	else
	{
		master->ray[cols].distance = (master->ray[cols].side_dist_y
				- master->ray[cols].delta_y);
		master->ray[cols].pos_wall.x
			= master->peter->pos.x + master->ray[cols].distance
			* master->ray[cols].dir.x;
		master->ray[cols].pos_wall.y
			= master->peter->pos.y + master->ray[cols].distance
			* master->ray[cols].dir.y;
	}
}

void	assign_textures(t_master *master, int cols, int map_x, int map_y)
{
	if (master->map->full_map[map_x][map_y] == '1')
	{
		if (master->ray[cols].side == 0)
			north_south(master, cols, master->ray[cols].step_x);
		else
			west_east(master, cols, master->ray[cols].step_y);
	}
	else if (master->map->full_map[map_x][map_y] == '2')
	{
		master->ray[cols].tex_height = master->textures->door->height;
		master->ray[cols].tex_width = master->textures->door->width;
		master->ray[cols].ray_color = master->textures->c_door;
		master->ray[cols].color = DOOR;
	}
}
