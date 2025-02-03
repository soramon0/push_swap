CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = push_swap
SRC = push_swap.c
OBJ = $(SRC:.c=.o)
LIBFT_NAME = ./libft/libft.a

all: $(NAME)

libft: $(LIBFT_NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME)

$(LIBFT_NAME):
	make -C libft

run: $(NAME)
	@./push_swap
	@rm $(NAME) $(OBJ)

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run
