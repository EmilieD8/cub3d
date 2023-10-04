/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:16:56 by edrouot           #+#    #+#             */
/*   Updated: 2023/09/13 16:18:57 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	check_line(t_master *master, int j, int i)
{
	while (master->map->full_map[j][i] != '\0')
	{
		if (master->map->full_map[j][i] != '1'
			&& master->map->full_map[j][i] != ' '
			&& master->map->full_map[j][i] != '2')
			return (ft_error(master, "Map contains a wrong character\n", 1));
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	check_first_and_last_line(t_master *master)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (check_line(master, j, i))
		return (EXIT_FAILURE);
	while (master->map->full_map[j] != 0)
		j++;
	i = 0;
	master->map->nb_rows = j;
	j--;
	if (check_line(master, j, i))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_full_map(t_master *master)
{
	int		i;
	size_t	j;

	i = 0;
	while (i <= master->map->nb_rows)
	{
		j = 0;
		while (j < ft_strlen(master->map->full_map[i]))
		{
			if (master->map->full_map[i][j] == ' '
				&& master->map->full_map[i][j + 1] == '0')
				return (ft_error(master, "Map is invalid\n", 1));
			else if (master->map->full_map[i][j] == '0'
				&& (master->map->full_map[i][j + 1] == ' '
				|| master->map->full_map[i][j + 1] == '\0'))
				return (ft_error(master, "Map is invalid\n", 1));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_map(t_master *master)
{
	if (check_first_and_last_line(master))
		return (EXIT_FAILURE);
	find_biggest_line(master->map);
	find_player_position(master);
	if (check_valid_char_map(master))
		return (EXIT_FAILURE);
	if (check_full_map(master))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
