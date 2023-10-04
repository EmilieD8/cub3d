/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:58:18 by mschaub           #+#    #+#             */
/*   Updated: 2023/10/02 14:22:33 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	keys_helper(t_master *master)
{
	mlx_delete_image(master->game->mlx, master->menu_img);
	master->menu_img_alloc = 0;
	mlx_terminate(master->game->mlx);
	if (master->game_started == 1)
		terminate_game(master);
	exit(1);
}

void	keys_menu(mlx_key_data_t keydata, void *param)
{
	t_master	*master;

	master = (t_master *)param;
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		master->menu_check = 1;
		mlx_delete_image(master->game->mlx, master->menu_img);
		master->menu_img_alloc = 0;
		start_whole_game(master);
		master->game_started = 1;
	}
	else if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
	{
		master->menu_check = 2;
		mlx_delete_image(master->game->mlx, master->menu_img);
		master->menu_img_alloc = 0;
		start_whole_game(master);
		master->game_started = 1;
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
		keys_helper(master);
}

static void	menu_helper(t_master *master, uint32_t *c_menu, mlx_texture_t *menu)
{
	free(c_menu);
	mlx_delete_texture(menu);
	if (mlx_image_to_window(master->game->mlx, master->menu_img, 0, 0) < 0)
		ft_error(master, "Error loading the image to the window\n", 0);
}

void	draw_menu(t_master *master)
{
	mlx_texture_t	*menu;
	uint32_t		*c_menu;
	uint32_t		color;
	int				x;
	int				y;

	x = 0;
	master->menu_img = mlx_new_image(master->game->mlx, WIDTH, HEIGHT);
	master->menu_img_alloc = 1;
	menu = mlx_load_png("textures/menu_game.png");
	c_menu = get_color(menu, master);
	while (x < (int)menu->height - 4)
	{
		y = 0;
		while (y < (int)menu->width)
		{
			color = color_pixel(&c_menu[y + x * menu->width]);
			if (color != 0)
				mlx_put_pixel(master->menu_img, y, x, color);
			y++;
		}
		x++;
	}
	menu_helper(master, c_menu, menu);
}
