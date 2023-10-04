/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:34:49 by mschaub           #+#    #+#             */
/*   Updated: 2023/09/16 12:34:49 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	check_char(t_master *master, int i, int j)
{
	if (master->map->full_map[i][j] == ' ')
		master->map->full_map[i][j] = '1';
	if (master->map->full_map[i][j] == '2')
	{
		master->map->exit_x = i;
		master->map->exit_y = j;
	}
}

int	check_valid_char_map(t_master *master)
{
	int	i;
	int	j;

	i = 0;
	while (i <= master->map->nb_rows)
	{
		j = 0;
		while ((size_t)j < ft_strlen(master->map->full_map[i]))
		{
			check_char(master, i, j);
			if (master->map->full_map[i][j] != '1'
				&& master->map->full_map[i][j] != '0'
				&& master->map->full_map[i][j] != ' '
				&& master->map->full_map[i][j] != '2'
				&& find_dir(master->map->full_map[i][j]))
				return (ft_error(master, "Map is invalid (invalid char)\n", 1));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
