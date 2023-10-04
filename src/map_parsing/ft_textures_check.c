/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:17:26 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/24 15:17:27 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	get_element_info(t_master *master, char *string, int i, int type)
{
	int		j;
	char	*sub_string;

	j = ft_strlen(string) - 1;
	i += 2;
	while (string[i] == ' ')
		i++;
	while (string[j] == ' ')
		j--;
	if (j < i)
		return (ft_error(master, "Invalid element info\n", 1));
	sub_string = ft_substr(string, i, j - i + 1);
	if (type == 1)
		master->map->north = ft_strdup(sub_string);
	else if (type == 2)
		master->map->south = ft_strdup(sub_string);
	else if (type == 3)
		master->map->west = ft_strdup(sub_string);
	else if (type == 4)
		master->map->east = ft_strdup(sub_string);
	free(sub_string);
	return (EXIT_SUCCESS);
}

int	is_elements(t_master *master, char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == 'N' && s[i + 1] == 'O' && master->map->north == NULL)
		return (get_element_info(master, s, i, 1));
	else if (s[i] == 'N' && s[i + 1] == 'O' && master->map->north != NULL)
		return (ft_error(master, "Double elements (N)\n", 1));
	else if (s[i] == 'S' && s[i + 1] == 'O' && master->map->south == NULL)
		return (get_element_info(master, s, i, 2));
	else if (s[i] == 'S' && s[i + 1] == 'O' && master->map->south != NULL)
		return (ft_error(master, "Double elements (S)\n", 1));
	else if (s[i] == 'W' && s[i + 1] == 'E' && master->map->west == NULL)
		return (get_element_info(master, s, i, 3));
	else if (s[i] == 'W' && s[i + 1] == 'E' && master->map->west != NULL)
		return (ft_error(master, "Double elements (WE)\n", 1));
	else if (s[i] == 'E' && s[i + 1] == 'A' && master->map->east == NULL)
		return (get_element_info(master, s, i, 4));
	else if (s[i] == 'E' && s[i + 1] == 'A' && master->map->east != NULL)
		return (ft_error(master, "Double elements (EA)\n", 1));
	return (EXIT_FAILURE);
}
