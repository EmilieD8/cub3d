/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:17:18 by edrouot           #+#    #+#             */
/*   Updated: 2023/09/12 15:01:49 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_extra_lines(char *string)
{
	int	i;

	i = ft_strlen(string) - 1;
	if (string[i] == '\n' && string[i - 1] == '\n')
		return (0);
	i = 0;
	while (string[i])
	{
		if (string[i] == '1' && string[i + 1] == '1')
			break ;
		i++;
	}
	while (string[i])
	{
		if (string[i] == '\n' && string[i + 1] == '\n')
			return (0);
		i++;
	}
	return (1);
}

void	find_biggest_line(t_map *map)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (i <= map->nb_rows)
	{
		if (ft_strlen(map->full_map[i]) > j)
			j = ft_strlen(map->full_map[i]);
		i++;
	}
	map->nb_columns = j;
}

void	free_two_strings(char *one, char *two)
{
	free(one);
	free(two);
}

size_t	find_biggest_line_bis(char **map, int index)
{
	int		i;
	size_t	j;

	i = index;
	j = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > j)
			j = ft_strlen(map[i]);
		i++;
	}
	return (j);
}
