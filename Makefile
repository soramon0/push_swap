CC = cc
CFLAGS = -Wall -Wextra -Werror
EXTRA_FLAGS = -g
NAME = push_swap
SRC = main.c $(shell find ./src -depth -maxdepth 1 -type f -name "*.c")
OBJ = $(SRC:.c=.o)
LIBFT_NAME = src/libft/libft.a
PROGRAM_ARG="4 67 3 87 23"

all: $(NAME)

libft: $(LIBFT_NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME)

$(LIBFT_NAME):
	$(MAKE) -C ./src/libft

clean:
	$(MAKE) -C src/libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C src/libft fclean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	@./push_swap
	@rm $(NAME) $(OBJ)

debug: $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(EXTRA_FLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME)

run_check:
	./push_swap $(PROGRAM_ARG) | ./checker_linux $(PROGRAM_ARG)

.PHONY: all clean fclean re run libft run_check debug
