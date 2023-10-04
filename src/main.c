/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:02:30 by mschaub           #+#    #+#             */
/*   Updated: 2023/10/02 14:25:45 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:35:45 by mschaub           #+#    #+#             */
/*   Updated: 2023/09/26 14:37:08 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	start_game(char *file, t_master *master)
{
	(void)file;
	master->textures = ft_textures(master);
	return (1);
}

static void	my_closehook(void *param)
{
	t_master	*master;

	master = (t_master *)param;
	if (master->menu_img_alloc == 1)
		mlx_delete_image(master->game->mlx, master->menu_img);
	master->menu_img_alloc = 0;
	mlx_terminate(master->game->mlx);
	if (master->game_started == 1)
		terminate_game(master);
	exit(1);
}

void	start_whole_game(t_master *master)
{
	mlx_delete_image(master->game->mlx, master->menu_img);
	start_game(master->map_arg, master);
	floor_ceil(master);
	mlx_key_hook(master->game->mlx, &set_keys, master);
	mlx_loop_hook(master->game->mlx, &ft_raycast, master);
}

void	main_helper(t_master *master, char **argv)
{
	master = ft_init(master);
	master->map_arg = ft_strdup(argv[1]);
	mlx_close_hook(master->game->mlx, &my_closehook, master);
	mlx_key_hook(master->game->mlx, &keys_menu, master);
	draw_menu(master);
	mlx_loop(master->game->mlx);
	terminate_game(master);
}

int	main(int argc, char **argv)
{
	t_master	*master;
	int			fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_error(NULL, "File not found\n", 0));
	master = NULL;
	if (argc != 2)
		return (ft_error(master, ARGS_ERR, 0));
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	if (!ft_iscub(argv[1]))
		ft_error(NULL, CUB_ERR, 0);
	else
	{
		master = malloc(sizeof(t_master));
		if (!master)
			return (ft_error(NULL, "Error\n", 0));
		init_map(master);
		init_player(master);
		check_input_file(master, fd);
	}
	main_helper(master, argv);
}
