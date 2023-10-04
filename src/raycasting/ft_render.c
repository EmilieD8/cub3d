/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:04:54 by edrouot           #+#    #+#             */
/*   Updated: 2023/10/02 13:56:15 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

uint32_t	*get_color(mlx_texture_t *texture, t_master *master)
{
	int				i;
	unsigned int	pos;
	uint8_t			rgb[4];
	uint32_t		*colors;

	i = 0;
	colors = malloc(sizeof(uint32_t) * (texture->width)
			* (texture->height));
	if (colors == NULL)
		ft_error(master, "Allocation error!\n", 0);
	pos = 0;
	while (pos < texture->width * texture->height * texture->bytes_per_pixel)
	{
		rgb[0] = texture->pixels[pos];
		rgb[1] = texture->pixels[pos + 1];
		rgb[2] = texture->pixels[pos + 2];
		rgb[3] = texture->pixels[pos + 3];
		colors[i] = (rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + rgb[3];
		pos += texture->bytes_per_pixel;
		i++;
	}
	return (colors);
}

u_int32_t	color_pixel(u_int32_t *pixel)
{
	u_int8_t	red;
	u_int8_t	green;
	u_int8_t	blue;
	u_int8_t	alpha;

	if (pixel == NULL)
		return (0);
	red = (pixel[0] >> 24) & 0xFF;
	green = (pixel[0] >> 16) & 0xFF;
	blue = (pixel[0] >> 8) & 0xFF;
	alpha = (pixel[0]) & 0xFF;
	return (((u_int32_t)red << 24) | ((u_int32_t)green << 16)
		| ((u_int32_t)blue << 8) | (u_int32_t)alpha);
}

void	draw_ray(int cols, t_master *master, mlx_image_t img)
{
	double		end;
	u_int32_t	i;

	master->pos_x_new = master->ray[cols].pos_wall.x
		- floor(master->ray[cols].pos_wall.x);
	master->pos_x_new = master->pos_x_new * master->ray[cols].tex_width;
	if (master->ray[cols].height > HEIGHT)
	{
		i = (HEIGHT / 2.0) - (HEIGHT / 2);
		end = ((HEIGHT / 2.0) - (HEIGHT / 2)) + HEIGHT;
	}
	else
	{
		i = (HEIGHT / 2.0) - (master->ray[cols].height / 2);
		end = ((HEIGHT / 2.0) - (master->ray[cols].height / 2))
			+ master->ray[cols].height;
	}
	while (i < end)
	{
		draw_helper(master, i, cols, img);
		i++;
	}
}

t_texture	*ft_textures(t_master *master)
{
	t_texture	*textures;

	textures = malloc(sizeof(t_texture));
	textures->north = mlx_load_png(master->map->north);
	if (!textures->north)
		ft_error(master, "Error loading the texture file\n", 0);
	textures->c_north = get_color(textures->north, master);
	textures_helper(master, textures);
	textures->c_west = get_color(textures->west, master);
	textures->east = mlx_load_png(master->map->east);
	if (!textures->east)
		ft_error(master, "Error loading the texture file\n", 0);
	textures->c_east = get_color(textures->east, master);
	master->texture_alloc = 1;
	if (master->map->exit_x != -1)
	{
		textures->door = mlx_load_png("textures/door.png");
		if (!textures->door)
			ft_error(master, "Error loading the texture file\n", 0);
		textures->c_door = get_color(textures->door, master);
		master->door_alloc = 1;
	}
	return (textures);
}

void	ft_render(t_master *master)
{
	int				cols;

	cols = 0;
	if (master->img_alloc == 1)
	{
		mlx_delete_image(master->game->mlx, master->img);
		master->img_alloc = 0;
	}
	master->img = mlx_new_image(master->game->mlx, WIDTH, HEIGHT);
	master->img_alloc = 1;
	if (!master->img)
		ft_error(master, "Error loading the image", 0);
	while (cols < WIDTH)
	{
		draw_ray(cols, master, *master->img);
		cols++;
	}
	if (master->menu_check == 1)
		draw_minimap(master);
	draw_bottle(master);
	if (mlx_image_to_window(master->game->mlx, master->img, 0, 0) < 0)
		ft_error(master, "Error loading the image to the window\n", 0);
}
