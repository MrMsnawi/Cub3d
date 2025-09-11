prs = mandatory/parsing
tls = mandatory/tools

parsing = $(prs)/parse.c $(prs)/parse_element.c $(prs)/textures.c $(prs)/txtr_tools.c

tools = $(tls)/error.c  $(tls)/ft_free.c  $(tls)/ft_malloc.c  $(tls)/ft_split.c  \
		$(tls)/ft_strdup.c  $(tls)/ft_strlen.c  $(tls)/ft_substr.c $(tls)/ft_strncmp.c

SRC = mandatory/main.c $(parsing) $(tools)

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
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(MLX_LINK) -o $(NAME)

clean :
	make -C mlx clean
	rm -f $(OBJ)

fclean : clean
	make -C mlx clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean