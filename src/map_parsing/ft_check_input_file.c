/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:16:50 by edrouot           #+#    #+#             */
/*   Updated: 2023/09/12 15:04:36 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	copy_map_bis(t_master *m, char **input, int index, int size);

static int	copy_map(t_master *master, char **input, int index)
{
	int		i;
	size_t	size_max;

	size_max = find_biggest_line_bis(input, index);
	i = index;
	while (input[i] != 0)
		i++;
	if (i == index)
		return (ft_error(master, "No map in the file", 1));
	master->map->full_map = (char **)malloc(sizeof(char *) * (i + 1));
	if (!master->map->full_map)
		return (ft_error(master, "Error allocating the map", 0));
	copy_map_bis(master, input, index, size_max);
	master->map->map_alloc = 1;
	return (EXIT_SUCCESS);
}

static void	copy_map_bis(t_master *m, char **input, int index, int size)
{
	int	i;
	int	j;

	i = 0;
	while (input[index] != 0)
	{
		m->map->full_map[i] = (char *)malloc(sizeof(char) * size + 1);
		j = 0;
		while (input[index][j] != '\0')
		{
			m->map->full_map[i][j] = input[index][j];
			j++;
		}
		while (j < (int)size)
		{
			m->map->full_map[i][j] = '1';
			j++;
		}
		m->map->full_map[i][j] = '\0';
		i++;
		index++;
	}
	m->map->full_map[i] = 0;
}

static int	get_elements(t_master *master, char **input)
{
	int	i;

	i = 0;
	while (input[i] != 0)
	{
		if (!ft_strncmp(input[i], "\n", ft_strlen(input[i])))
			i++;
		else if (!is_elements(master, input[i]))
			i++;
		else if (!is_color(master, input[i]))
			i++;
		else
			break ;
	}
	return (i);
}

static char	**get_input_file(t_master *master, int fd)
{
	char	*final_line;
	char	*line;
	char	**input;
	char	*temp;

	temp = NULL;
	final_line = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		temp = ft_strjoin(final_line, line);
		free(final_line);
		final_line = ft_strdup(temp);
		free_two_strings(temp, line);
		line = get_next_line(fd);
	}
	free(line);
	if (check_extra_lines(final_line) == 0)
	{
		free(final_line);
		ft_error(master, "New lines in map\n", 1);
	}
	input = ft_split(final_line, '\n');
	free(final_line);
	return (input);
}

int	check_input_file(t_master *master, int fd)
{
	int		index;

	master->map->input = get_input_file(master, fd);
	if (master->map->input == NULL)
		return (EXIT_FAILURE);
	master->map->input_alloc = 1;
	index = get_elements(master, master->map->input);
	if (!master->map->north || !master->map->south
		|| !master->map->west || !master->map->east)
		return (ft_error(master, "Texture file(s) missing\n", 1));
	if (master->map->floor_alloc != 1 || master->map->ceiling_alloc != 1)
		return (ft_error(master, "Color input invalid too many\n", 1));
	if (copy_map(master, master->map->input, index))
		return (1);
	if (check_map(master))
		return (1);
	if (master->peter->pos.x == -1 || master->peter->pos.y == -1)
		return (ft_error(master, "No player in the map\n", 1));
	return (EXIT_SUCCESS);
}
