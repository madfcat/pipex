CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = pipex
HEADER = ft_pipex.h
LIBFT_DIR = libft/
LIBFT_NAME = libft.a

SRCS = main.c

OBJ_DIR = obj/
OBJS = $(SRCS:.c=.o)
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJS))

all: $(NAME)

$(NAME): $(SRCS) $(HEADER)
	make -C $(LIBFT_DIR)
	mv $(LIBFT_DIR)$(LIBFT_NAME) .
	$(CC) $(CFLAGS) -c $(SRCS) -I $(HEADER)
	mkdir -p $(OBJ_DIR)
	mv $(OBJS) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -L. -lft -o $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LIBFT_NAME)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re