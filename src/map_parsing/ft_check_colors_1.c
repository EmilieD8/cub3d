/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:16:33 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/24 15:16:34 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	check_color_comma(t_master *master, char *string, int i)
{
	int		comma;

	comma = 0;
	if (string[i] == ',')
		return (ft_error(master, "Color input is invalid beg comma\n", 1));
	while (string[i] != '\0')
	{
		if (string[i] == ',' && string[i + 1] == ',')
			return (ft_error(master, "Color is invalid comma in a row\n", 1));
		else if (string[i] == ',' && string[i + 1] != ',')
			comma++;
		i++;
	}
	if (string[i] == ',')
		return (ft_error(master, "Color input is invalid last comma\n", 1));
	if (comma != 2)
		return (ft_error(master, "Color input is invalid\n", 1));
	return (EXIT_SUCCESS);
}

static int	check_color(t_master *master, char *string, int i, int type)
{
	char	*sub_string;
	char	**numbers;
	int		j;

	j = ft_strlen(string) - 1;
	i++;
	while (string[i] != '\0' && string[i] == ' ')
		i++;
	while (string[j] == ' ')
		j--;
	if (check_color_comma(master, string, i))
		return (EXIT_FAILURE);
	sub_string = ft_substr(string, i, j - i + 1);
	numbers = ft_split(sub_string, ',');
	free(sub_string);
	if (get_color_numbers(master, numbers, type))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_color(t_master *master, char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0' && string[i] == ' ')
		i++;
	if (string[i] == 'F')
		return (check_color(master, string, i, 1));
	else if (string[i] == 'C')
		return (check_color(master, string, i, 2));
	return (EXIT_FAILURE);
}
