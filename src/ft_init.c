/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:07:21 by mschaub           #+#    #+#             */
/*   Updated: 2023/10/02 14:22:50 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map(t_master *master)
{
	master->map = (t_map *)malloc(sizeof(t_map));
	if (!master->map)
		ft_error(NULL, "Memory allocation failure for map struct", 0);
	master->map->north = NULL;
	master->map->south = NULL;
	master->map->east = NULL;
	master->map->west = NULL;
	master->map->full_map = NULL;
	master->map->floor = NULL;
	master->map->ceiling = NULL;
	master->map->nb_rows = 0;
	master->map->nb_columns = 0;
	master->map->map_alloc = 0;
	master->map->floor_alloc = 0;
	master->map->ceiling_alloc = 0;
	master->map->input_alloc = 0;
	master->map->exit_x = -1;
}

static t_master	*init_game(t_master *master)
{
	master->game->mlx = mlx_init(WIDTH, HEIGHT, "Alice 3D", true);
	if (!master->game->mlx)
		ft_error(master, MLX_ERR, 0);
	return (master);
}

void	init_player(t_master *master)
{
	master->peter = (t_player *)malloc(sizeof(t_player));
	if (!master->peter)
		ft_error(NULL, "Memory allocation failure for player struct", 0);
	master->peter->pos.x = -1;
	master->peter->pos.y = -1;
	master->peter->dir.x = 0;
	master->peter->dir.y = 0;
	master->peter->plane.x = 0;
	master->peter->plane.y = 0;
}

/* Function to initialize the game */
t_master	*ft_init(t_master *master)
{
	master->game = (t_game *)malloc(sizeof(t_game));
	master->ray = (t_ray *)malloc(sizeof(t_ray) * WIDTH);
	if (!master || !master->map || !master->game
		|| !master->peter || !master->ray)
		ft_error(master, "Memory allocation failure for map struct", 0);
	master = init_game(master);
	master = init_ray(master);
	master->texture_alloc = 1;
	master->door_alloc = 0;
	master->menu_img_alloc = 0;
	master->img_alloc = 0;
	master->turn_dir = 0;
	master->walk_dir = 0;
	master->menu_check = 0;
	master->map_arg = NULL;
	master->exit = 0;
	master->floor_ceiling_img_alloc = 0;
	master->game_started = 0;
	return (master);
}
