/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:43:10 by mschaub           #+#    #+#             */
/*   Updated: 2023/10/02 12:03:33 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_helper(t_master *master, int i, int cols, mlx_image_t img)
{
	u_int32_t	color;
	int			width;
	int			h;

	width = master->ray[cols].tex_width;
	h = (i * master->ray[cols].tex_height / master->ray[cols].height)
		- (((HEIGHT / 2.0) - (master->ray[cols].height / 2))
			* master->ray[cols].tex_height / master->ray[cols].height);
	if (h < 0)
		h = 0;
	color = color_pixel(&master->ray[cols].ray_color[(int)master->pos_x_new
			+ h * width]);
	mlx_put_pixel(&img, cols, i, color);
}
