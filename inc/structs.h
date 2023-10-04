/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:09:55 by mschaub           #+#    #+#             */
/*   Updated: 2023/09/25 12:39:30 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

/* ----- Structs ----- */

typedef struct s_image
{
	int		width;
	int		height;
}	t_image;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_image	img;
}	t_game;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

/* Struct with player info
 * pos: (x,y) of position
 * start: (x,y) of start
 * starting_dir: N, S, E or W for orientation
 */
typedef struct s_player
{
	t_pos	pos;
	t_pos	dir;
	t_pos	plane;
}	t_player;

/* Struct with map info
 * player_dir: starting orientation (N, S, W or E)
 * north: texture for north wall
 * south: texture for south wall
 * west: texture for west wall
 * east: texture for east wall
 * map: string array for map, each string for one line
 */
typedef struct s_map
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**input;
	char	**full_map;
	int		*floor;
	int		*ceiling;
	int		nb_rows;
	int		nb_columns;
	int		floor_alloc;
	int		ceiling_alloc;
	int		map_alloc;
	int		input_alloc;
	int		exit_x;
	int		exit_y;
}	t_map;

/*	Struct for a single ray */
typedef struct s_ray
{
	t_pos				pos_wall;
	t_pos				dir;
	double				delta_x;
	double				delta_y;
	double				side_dist_x;
	double				side_dist_y;
	double				distance;
	double				height;
	int					step_x;
	int					step_y;
	int					side;
	int					color;
	uint32_t			tex_width;
	uint32_t			tex_height;
	uint32_t			*ray_color;
}	t_ray;

typedef struct s_texture
{
	mlx_texture_t		*north;
	uint32_t			*c_north;
	mlx_texture_t		*south;
	u_int32_t			*c_south;
	mlx_texture_t		*west;
	u_int32_t			*c_west;
	mlx_texture_t		*east;
	u_int32_t			*c_east;
	mlx_texture_t		*bottle;
	u_int32_t			*c_bottle;
	mlx_texture_t		*door;
	u_int32_t			*c_door;
}	t_texture;

/* Struct to connect all other structs */
typedef struct s_master
{
	t_player	*peter;
	t_game		*game;
	t_map		*map;
	t_ray		*ray;
	int			texture_alloc;
	t_texture	*textures;
	mlx_image_t	*img;
	mlx_image_t	*menu_img;
	mlx_image_t	*floor_ceiling_img;
	int			img_alloc;
	int			menu_img_alloc;
	int			door_alloc;
	int			floor_ceiling_img_alloc;
	int			walk_dir;
	int			turn_dir;
	int			menu_check;
	char		*map_arg;
	int			exit;
	int			game_started;
	double		pos_x_new;
}	t_master;

#endif
