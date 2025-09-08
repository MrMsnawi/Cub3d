SRC = mandatory/main.c

OBJ = $(SRC:.c=.o)

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

%.o : %.c include/cub.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean