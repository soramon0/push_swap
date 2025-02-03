CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = push_swap
SRC = push_swap.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

run: $(NAME)
	@./push_swap
	@rm $(NAME) $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run
