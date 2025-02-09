CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = push_swap
SRC = push_swap.c swapable.c parser.c
OBJ = $(SRC:.c=.o)
LIBFT_NAME = ./libft/libft.a
PROGRAM_ARG="4 67 3 87 23"

all: $(NAME)

libft: $(LIBFT_NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME)

$(LIBFT_NAME):
	$(MAKE) -C libft

run: $(NAME)
	@./push_swap
	@rm $(NAME) $(OBJ)

run_check:
	./push_swap $(PROGRAM_ARG) | ./checker_linux $(PROGRAM_ARG)

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run libft run_check
