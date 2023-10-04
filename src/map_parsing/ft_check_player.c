/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:17:09 by edrouot           #+#    #+#             */
/*   Updated: 2023/09/23 01:09:50 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	set_start_angle_w_e(t_master *master, char c)
{
	if (c == 'E')
	{
		master->peter->dir.x = 0;
		master->peter->dir.y = 1;
		master->peter->plane.x = -0.66;
		master->peter->plane.y = 0;
	}
	else if (c == 'W')
	{
		master->peter->dir.x = 0;
		master->peter->dir.y = -1;
		master->peter->plane.x = 0.66;
		master->peter->plane.y = 0;
	}
}

static void	set_start_angle(t_master *master, char c)
{
	if (c == 'S')
	{
		master->peter->dir.x = 1;
		master->peter->dir.y = 0;
		master->peter->plane.x = 0;
		master->peter->plane.y = 0.66;
	}
	else if (c == 'N')
	{
		master->peter->dir.x = -1;
		master->peter->dir.y = 0;
		master->peter->plane.x = 0;
		master->peter->plane.y = -0.66;
	}
	else if (c == 'E' || c == 'W')
		set_start_angle_w_e(master, c);
}

int	find_dir(char c)
{
	if (c == 'N')
		return (EXIT_SUCCESS);
	else if (c == 'W')
		return (EXIT_SUCCESS);
	else if (c == 'S')
		return (EXIT_SUCCESS);
	else if (c == 'E')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	find_player_position(t_master *master)
{
	int	i;
	int	j;
	int	check;

	check = 0;
	i = 0;
	while (i <= master->map->nb_rows)
	{
		j = 0;
		while ((size_t)j++ < ft_strlen(master->map->full_map[i]))
		{
			if (!find_dir(master->map->full_map[i][j]))
			{
				if (check == 1)
					return (ft_error(master, "Map is invalid\n", 1));
				master->peter->pos.y = j + 0.5;
				master->peter->pos.x = i + 0.5;
				set_start_angle(master, master->map->full_map[i][j]);
				master->map->full_map[i][j] = '0';
				check++;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
