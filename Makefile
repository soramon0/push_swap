CC = cc
CFLAGS = -Wall -Wextra -Werror
EXTRA_FLAGS = -g
NAME = push_swap
SRC = main.c $(shell find ./src -depth -maxdepth 1 -type f -name "*.c")
OBJ = $(SRC:.c=.o)
LIBFT_NAME = src/libft/libft.a
PROGRAM_ARG=$(shell seq -500 500 | shuf -n 1000)

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

run: debug
	./push_swap "$(PROGRAM_ARG)"
	@rm $(NAME) $(OBJ)

debug: $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(EXTRA_FLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME)

profile_clean:
	rm -f callgrind.out*

# --inclusive=yes: Instead of using exclusive cost of functions as sorting order, use and show inclusive cost.
# --tree=both: Interleave into the top level list of functions, information on the callers and the callees of each function. In these lines, which represents executed calls, the cost gives the number of events spent in the call. Indented, above each function, there is the list of callers, and below, the list of callees. The sum of events in calls to a given function (caller lines), as well as the sum of events in calls from the function (callee lines) together with the self cost, gives the total inclusive cost of the function.
profile: profile_clean debug
	valgrind --tool=callgrind ./push_swap "$(PROGRAM_ARG)"
	callgrind_annotate $(shell find . -type f -name "callgrind.out*") --inclusive=yes --tree=both > profile.txt

run_checker:
	./push_swap "$(PROGRAM_ARG)" | ./checker_linux "$(PROGRAM_ARG)"

.PHONY: all clean fclean re run libft run_checker debug profile profile_clean
