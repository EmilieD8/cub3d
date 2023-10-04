/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:07:26 by mschaub           #+#    #+#             */
/*   Updated: 2023/09/23 00:09:41 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_master	*init_ray(t_master *master)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		master->ray[i].pos_wall.x = 0;
		master->ray[i].pos_wall.y = 0;
		master->ray[i].distance = 0;
		master->ray[i].height = 0;
		master->ray[i].dir.x = 0;
		master->ray[i].dir.y = 0;
		master->ray[i].tex_height = 0;
		master->ray[i].tex_width = 0;
		master->ray[i].ray_color = NULL;
		master->ray[i].color = 0;
		i++;
	}
	return (master);
}
