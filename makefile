SRC = mandatory/main.c

OBJ = $(SRC:.c=.o)

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

MLX = mlx/libmlx_Linux.a

MLX_LINK = -Lmlx -lXext -lX11 -lm

all : $(NAME)

$(MLX):
	make -C mlx

%.o : %.c include/cub.h
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