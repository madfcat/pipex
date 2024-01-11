CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = pipex
HEADER = ft_pipex.h
LIBFT_DIR = libft/
LIBFT_NAME = libft.a

SRCS = error.c \
	main.c \
	path.c \
	split_command.c \
	utils.c

OBJ_DIR = obj/
OBJS = $(SRCS:.c=.o)
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJS))

LIBFT_MARKER = .libft

all: makelibft $(NAME)

# Make libft
makelibft:
	make -C $(LIBFT_DIR)

# Create marker if libft.a in libft directory changed (makelibft had run)
$(LIBFT_MARKER): $(LIBFT_DIR)$(LIBFT_NAME)
	touch $(LIBFT_MARKER)

# Copy libft only if marker changed (makelibft had run and changed the marker)
$(LIBFT_NAME): $(LIBFT_MARKER)
	cp $(LIBFT_DIR)$(LIBFT_NAME) .

$(NAME): $(SRCS) $(HEADER) $(LIBFT_NAME)
	$(CC) $(CFLAGS) -c $(SRCS) -I $(HEADER)
	mkdir -p $(OBJ_DIR)
	mv $(OBJS) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -L. -lft -o $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LIBFT_NAME)
	rm -f $(LIBFT_MARKER)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re