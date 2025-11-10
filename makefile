prs = mandatory/parsing
cub = mandatory/cub_lib

parsing = $(prs)/elements.c  $(prs)/map.c  $(prs)/parse.c \
			$(prs)/rgb.c  $(prs)/textures.c \
			$(prs)/utils/elmnts.c  $(prs)/utils/map_u_1.c  $(prs)/utils/map_u_2.c  \
			$(prs)/utils/rgb_u_1.c  $(prs)/utils/rgb_u_2.c \
			$(prs)/utils/txtr_tools.c

lib = $(cub)/error.c $(cub)/ft_free.c $(cub)/ft_malloc.c $(cub)/ft_split.c \
			$(cub)/ft_strlen.c $(cub)/ft_substr.c $(cub)/is_valid_char_name.c \
			$(cub)/ft_exit.c $(cub)/ft_isspace.c $(cub)/ft_realloc.c \
			$(cub)/ft_strdup.c  $(cub)/ft_strncmp.c  $(cub)/is_in.c

raycasting = raycasting/raycasting.c raycasting/init_data.c

SRC = mandatory/main.c $(parsing) $(lib) $(raycasting)

OBJ = $(SRC:.c=.o)

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

MLX = mlx/libmlx_Linux.a

MLX_LINK = -Lmlx -lXext -lX11

all : $(NAME)

$(MLX):
	make -C mlx

%.o : %.c mandatory/include/cub.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(MLX_LINK)  -lm -o $(NAME)

clean :
	make -C mlx clean
	rm -f $(OBJ)

fclean : clean
	make -C mlx clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean 