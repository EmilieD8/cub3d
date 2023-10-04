# Constants

NAME	:= cub3d
CFLAGS	:= -Ofast -g -Wextra -Wall -Werror
LIBMLX	:= ./MLX42
LIBFT	:= ./libft/libft.a

# Sources and Headers

HEADERS	:= -I ./inc -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
#-framework Cocoa -framework OpenGL -framework IOKit

SRCS	:=	./src/main.c \
			./src/ft_error.c \
			./src/ft_init.c \
			./src/ft_init_2.c \
			./src/ft_utils.c \
			./src/ft_draw_not_ray.c \
			./src/ft_menu.c \
			./src/map_parsing/ft_check_colors_1.c \
			./src/map_parsing/ft_check_colors_2.c \
			./src/map_parsing/ft_check_input_file.c \
			./src/map_parsing/ft_check_map.c \
			./src/map_parsing/ft_check_map_2.c \
			./src/map_parsing/ft_check_player.c \
			./src/map_parsing/ft_map_utils.c \
			./src/map_parsing/ft_textures_check.c \
			./src/raycasting/ft_raycast.c \
			./src/raycasting/ft_raycast_2.c \
			./src/raycasting/ft_render.c \
			./src/raycasting/ft_render_2.c \
			./src/raycasting/ft_render_3.c \
			./src/movement/ft_move.c \
			./src/movement/ft_set_keys.c \

OBJS	:= ${SRCS:.c=.o}

# Colors

GREEN = \e[92;5;118m
YELLOW = \e[1;93m

# Rules

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@cd libft && make

%.o: %.c $(SRCS) ./inc/*.h
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Compiling completed"

clean:
	@rm -f $(OBJS)
	@cd libft && make clean
	@echo "$(YELLOW)Deleting .o files"

fclean: clean
	@rm -f $(NAME)
	@cd libft && make fclean
	@echo "$(YELLOW)Deleting executable"

re: clean all

.PHONY: all, clean, fclean, re, libmlx
