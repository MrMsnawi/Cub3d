parsing = parsing/elements.c  parsing/map.c  parsing/parse.c \
			parsing/rgb.c  parsing/textures.c \
			parsing/utils/elmnts.c  parsing/utils/map_u_1.c  parsing/utils/map_u_2.c  \
			parsing/utils/rgb_u_1.c  parsing/utils/rgb_u_2.c \
			parsing/utils/txtr_tools.c  parsing/utils/parse_helper.c

lib = cub_lib/error.c cub_lib/ft_free.c cub_lib/ft_malloc.c cub_lib/ft_split.c \
			cub_lib/ft_strlen.c cub_lib/ft_substr.c cub_lib/is_valid_char_name.c \
			cub_lib/ft_exit.c cub_lib/ft_isspace.c cub_lib/ft_realloc.c \
			cub_lib/ft_strdup.c  cub_lib/ft_strncmp.c  cub_lib/is_in.c \
			cub_lib/ft_memset.c

raycasting = raycasting/raycasting.c raycasting/init_data.c

SRC = main.c $(parsing) $(lib) $(raycasting)

OBJ = $(SRC:.c=.o)

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

MLX = mlx/libmlx_Linux.a

MLX_LINK = -Lmlx -lXext -lX11

all : $(NAME)

$(MLX):
	make -C mlx

%.o : %.c include/cub.h
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

.PHONY : all clean fclean re