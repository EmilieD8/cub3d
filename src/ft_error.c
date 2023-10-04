/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:57:37 by mschaub           #+#    #+#             */
/*   Updated: 2023/10/02 12:09:36 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:57:25 by edrouot           #+#    #+#             */
/*   Updated: 2023/09/23 00:06:34 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* TODO: check leaks after invalid map, causes segfault atm */
static int	free_map_player(t_master *master)
{
	free(master->peter);
	if (master->map->north != NULL)
		free(master->map->north);
	if (master->map->south != NULL)
		free(master->map->south);
	if (master->map->east != NULL)
		free(master->map->east);
	if (master->map->west != NULL)
		free(master->map->west);
	if (master->map->floor_alloc != 0)
		free(master->map->floor);
	if (master->map->ceiling_alloc != 0)
		free(master->map->ceiling);
	if (master->map->map_alloc != 0)
		free_array(master->map->full_map);
	if (master->map->input_alloc != 0)
		free_array(master->map->input);
	free(master->map);
	free(master);
	exit(1);
}

/* Error function, need to add function that quits game */
int	ft_error(t_master *master, char *str, int i)
{
	ft_putstr_fd("Error\n", 2);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	if (i == 1)
		(free_map_player(master));
	else if (master)
		terminate_game(master);
	exit(1);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
	{
		if (array[i] != NULL)
			free(array[i]);
		i++;
	}
	free(array);
}

/* Line 58 is causing a segfault when no door in map */
static void	free_2(t_master *master)
{
	free(master->map);
	free(master->game);
	free(master->ray);
	free(master->map_arg);
	if (master->menu_img_alloc == 1)
		mlx_delete_image(master->game->mlx, master->menu_img);
	if (master->floor_ceiling_img_alloc == 1)
		mlx_delete_image(master->game->mlx, master->floor_ceiling_img);
	if (master->texture_alloc && master->game_started)
	{
		mlx_delete_texture(master->textures->north);
		mlx_delete_texture(master->textures->south);
		mlx_delete_texture(master->textures->east);
		mlx_delete_texture(master->textures->west);
		if (master->door_alloc == 1)
			mlx_delete_texture(master->textures->door);
		free(master->textures->c_north);
		free(master->textures->c_south);
		free(master->textures->c_east);
		free(master->textures->c_west);
		if (master->door_alloc == 1)
			free(master->textures->c_door);
		free(master->textures);
	}
}

void	terminate_game(t_master *master)
{
	if (master->map->north != NULL)
		free(master->map->north);
	if (master->map->south != NULL)
		free(master->map->south);
	if (master->map->east != NULL)
		free(master->map->east);
	if (master->map->west != NULL)
		free(master->map->west);
	if (master->map->floor_alloc != 0)
		free(master->map->floor);
	if (master->map->ceiling_alloc != 0)
		free(master->map->ceiling);
	if (master->map->map_alloc != 0)
		free_array(master->map->full_map);
	if (master->map->input_alloc != 0)
		free_array(master->map->input);
	free(master->peter);
	free_2(master);
	free(master);
}
