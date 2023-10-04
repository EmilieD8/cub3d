/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:16:41 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/24 15:17:45 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	get_color_floor(t_master *master, char **numbers)
{
	if (master->map->floor_alloc != 0)
	{
		free_array(numbers);
		master->map->floor_alloc++;
		return (EXIT_FAILURE);
	}
	master->map->floor = (int *)malloc(sizeof(int) * 3);
	master->map->floor[0] = ft_atoi(numbers[0]);
	master->map->floor[1] = ft_atoi(numbers[1]);
	master->map->floor[2] = ft_atoi(numbers[2]);
	free_array(numbers);
	master->map->floor_alloc++;
	if (master->map->floor[0] < 0 || master->map->floor[0] > 255)
		return (ft_error(master, "Color input is invalid\n", 1));
	else if (master->map->floor[1] < 0 || master->map->floor[1] > 255)
		return (ft_error(master, "Color input is invalid\n", 1));
	else if (master->map->floor[2] < 0 || master->map->floor[2] > 255)
		return (ft_error(master, "Color input is invalid \n", 1));
	return (EXIT_SUCCESS);
}

static int	get_color_ceiling(t_master *master, char **numbers)
{
	if (master->map->ceiling_alloc != 0)
	{
		free_array(numbers);
		master->map->ceiling_alloc++;
		return (EXIT_FAILURE);
	}
	master->map->ceiling = (int *)malloc(sizeof(int) * 3);
	master->map->ceiling[0] = ft_atoi(numbers[0]);
	master->map->ceiling[1] = ft_atoi(numbers[1]);
	master->map->ceiling[2] = ft_atoi(numbers[2]);
	free_array(numbers);
	master->map->ceiling_alloc++;
	if (master->map->ceiling[0] < 0 || master->map->ceiling[0] > 255)
		return (ft_error(master, "Color input is invalid\n", 1));
	else if (master->map->ceiling[1] < 0 || master->map->ceiling[1] > 255)
		return (ft_error(master, "Color input is invalid\n", 1));
	else if (master->map->ceiling[2] < 0 || master->map->ceiling[2] > 255)
		return (ft_error(master, "Color input is invalid\n", 1));
	return (EXIT_SUCCESS);
}

int	get_color_numbers(t_master *master, char **numbers, int type)
{
	int	i;

	i = 0;
	while (numbers[i] != 0)
		i++;
	if (i != 3)
		return (EXIT_FAILURE);
	if (type == 1)
		return (get_color_floor(master, numbers));
	else if (type == 2)
		return (get_color_ceiling(master, numbers));
	return (EXIT_SUCCESS);
}
