/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:56:37 by edrouot           #+#    #+#             */
/*   Updated: 2023/10/02 14:15:35 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	set_keys_left_right(mlx_key_data_t keydata, t_master *master)
{
	if (keydata.key == MLX_KEY_LEFT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			master->turn_dir = 1;
		if (keydata.action == MLX_RELEASE)
			master->turn_dir = 0;
	}
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			master->turn_dir = -1;
		if (keydata.action == MLX_RELEASE)
			master->turn_dir = 0;
	}
}

static void	set_keys_a_d(mlx_key_data_t keydata, t_master *master)
{
	if (keydata.key == MLX_KEY_A)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			master->walk_dir = 2;
		if (keydata.action == MLX_RELEASE)
			master->walk_dir = 0;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			master->walk_dir = -2;
		if (keydata.action == MLX_RELEASE)
			master->walk_dir = 0;
	}
}

static void	set_keys_w_s(mlx_key_data_t keydata, t_master *master)
{
	if (keydata.key == MLX_KEY_W)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			master->walk_dir = 1;
		if (keydata.action == MLX_RELEASE)
			master->walk_dir = 0;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			master->walk_dir = -1;
		if (keydata.action == MLX_RELEASE)
			master->walk_dir = 0;
	}
}

void	set_keys(mlx_key_data_t keydata, void *param)
{
	t_master	*master;

	master = (t_master *)param;
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		set_keys_left_right(keydata, master);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
		set_keys_w_s(keydata, master);
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
		set_keys_a_d(keydata, master);
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		terminate_game(master);
		exit(1);
	}
}
